#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <functional>
#include <typeinfo>

using namespace std;

// 现代C++语言核心特性解析
void test_auto1()
{
//1.当用一个auto关键字声明多个变量的时候，编译器遵循从左到右的推导规则，以最左边的表达式判断auto的具体类型
    int n = 5;
    auto *pn = &n, m = 10;   // compile success auto被推到为int.
//在上面的代码中，因为&n的类型为int*,所以pn的类型被推导为int*,auto被推导为int,于是m被声明为int类型,可以编译成功。
// 但是如果写成下面的代码，将无法通过编译。
// auto pn = &n, m =10;   // compile success auto被推导为int* 和m的类型(int)不兼容。

//2.当使用条件表达式初始化auto声明的变量时，编译器总是使用表达能力更强的类型。
    auto i = true ? 5 : 8.0;    // i被推导为double
    cout << sizeof(int) << sizeof(i) << i << endl;  // 4 8 5
//在上面的代码中，虽然能够确定表达式返回的是int类型，但是i的类型依旧会被推导为表达能力更强的类型double.

// 3.虽然c++11标准已经支持在声明成员变量时初始化，但是auto却无法在这种情况下声明非静态成员变量。
    // struct sometype{
        // auto i = 5;  // error: non-static data member declared with placeholder ‘auto’
    // };
// 在c++11中静态成员变量是可以用auto声明并且初始化的，不过前提是auto必须使用const限定符。
    // 我在wsl中也不能编译通过。
    struct sometype
    {
        // static const auto i = 5;  // error: non-static data member declared with placeholder ‘auto’
    };
//遗憾的是，const限定符会导致常量化，显然这不是我们想要的结果。
//幸运的是，在c++17标准中，对于静态成员变量,auto可以在没有const的情况下使用：
    // struct sometype{    // 未测试
        // static inline auto i = 5;
    // };

//4.按照C++20之前的标准，无法在函数形参列表中使用auto声明形参(注意，在c++14中，auto可以为lambda表达式声明形参)：
    // void echo(auto str) { str; }  // c++20之前编译失败，c++20编译成功
//另外，auto也可以和new关键字结合。当然，我们通常不会这么用，例如：
    // auto i = new auto(5);   // c++11编译不过，c++17能编译过
    auto* j = new auto(5);  // c++11编译通过
    //这种用法比较有趣，编译器实际上进行了两次推导，第一次是auto(5),auto被推导为int类型，于是new int 的类型为int*,再通过int*推导i和j的类型。
    //我不建议像上面这样使用auto,因为它会破会代码的可读性。在后面的内容中，我们将讨论应该在什么时候避免使用auto关键字。
}

class Base
{
public:
    virtual void f()
    {
        cout << "Base::f()" << endl;
    }
};

class Derived : public Base
{
public:
    virtual void f()
    {
        cout << "Drived::f()" << endl;
    }
};

void test_auto_virtual()
{
    Base* d = new Derived();
    auto b = *d; // Base::f()
    // auto &b = *d;   // Drived::f() b是d类型的引用， 等同auto *b = d;
    cout << typeid(b).name() << endl;
    b.f();
}

// 不同的返回类型会导致auto推导失败
// auto sum(long a1, long a2)
// {
//     if(a1 < 0)
//     {
//         return 0;
//     }
//     else
//     {
//         return a1 + a2; // 返回long类型
//     }
// }

/*
typeid 会忽略 `引用` 和 `const` 限定符，所以：
    typeid(t).name() 通常会显示 i (表示 int)
    typeid(x).name() 通常也会显示 i (表示 int)

decltype(t) 返回 t 的 声明类型 + 引用和 const 信息。
decltype(t) 会 完整保留引用和 const 信息，如：返回 const int&。
由于 t 是一个具名变量（左值），decltype(t) 会返回 const int&（包括 const 和 &）。

1. 为什么需要 std::remove_reference_t？
std::is_const 检查的是 类型本身 是否包含 const 限定符，但它不会自动去除引用。
如果 decltype(t) 是 const int&，那么：
    std::is_const<const int&>::value 是 false（因为引用 & 本身不是 const，即使它指向 const 类型）。
    std::is_const<const int>::value 才是 true（正确检测 const）。
所以，必须先用 std::remove_reference_t 去掉引用部分，再检查 const；否则当 t 是引用时，结果 永远是 false（因为引用本身不是 const）。
*/

template<typename T>
void wrapper(T&& t)
{
    // 这里的t是万能引用，可以接受左值和右值
    cout << "wrapper called with type: " << (std::is_lvalue_reference<decltype(t)>::value ? "lvalue " : "rvalue ")
         << (std::is_const<std::remove_reference_t<decltype(t)>>::value ? "const " : "") << typeid(t).name() << endl;
    auto&& x = std::forward<T>(t); // 使用std::forward保持引用类型
    cout << "x type: " << (std::is_lvalue_reference<decltype(t)>::value ? "lvalue " : "rvalue ")
         << (std::is_const<std::remove_reference_t<decltype(t)>>::value ? "const " : "") << typeid(x).name() << endl;
}

void test_auto_autoref_autorefref()
{
    // 1. auto推导的类型是值类型
    int a = 10;
    const int b = 20;
    auto a1 = a; // a1是int类型
    auto b1 = b; // b1是int类型

    auto p2 = &a; // p2是int*类型
    auto p3 = &b; // p3是const int*类型
    const int* p1 = &a; // p1是const int*类型
    auto p1_copy = p1; // p1_copy是const int*类型 // p1_copy是p1的值拷贝

    int* const p4 = &a; // p4是int* const类型
    auto p5 = p4; // p5是int* 类型 // p5是p4的值拷贝，p5不是const类型

    const int* const p6 = &b; // p6是const int* const类型
    auto p7 = p6; // p7是const int*类型 // p7是p6的值拷贝，p7不是const类型

    const char name[] = "hello";
    auto name1 = name; // name1是const char*类型

    // 2.auto& 左值引用推导的类型是引用类型
    auto& m1 = a; // int&
    const auto& m2 = a; // a2是const int&类型
    auto& m3 = b; // m3是const int&类型
    const auto& m4 = b; // m4是const int&类型

    auto& m5 = p1; // m5是const int*&类型
    const auto& m6 = p1; // m6是const int*&类型
    auto& m7 = p4; // m7是int* const&类型
    const auto& m8 = p4; // m8是int* const&类型
    auto& m9 = p6; // m9是const int* const&类型
    const auto& m10 = p6; // m10是const int* const&

    auto& m11 = name; // m11是const char (&)[6]类型
    const auto& m12 = name; // m12是const char (&)[6]类型

    // 3.auto&& 通常是万能引用(Forwarding Reference)
    auto&& n = 1; // n是int&&类型
    auto&& n1 = a; // n1是int&&类型
    auto&& n2 = b; // n2是const int&类型
    auto&& n3 = p1; // n3是const int*&类型
    auto&& n4 = p4; // n4是int* const&类型
    auto&& n5 = p6; // n5是const int* const&类型
    auto&& n6 = name; // n6是const char (&)[6]类型
    const auto&& n7 = 1; // n7是const int&&类型

    // T&&
    wrapper(1); // 传递右值 rvalue i
    wrapper(a); // 传递左值 lvalue i
    wrapper(b); // 传递左值 lvalue const i
    wrapper(p1); // 传递左值 lvalue const PKi
    wrapper(p4); // 传递左值 lvalue const Pi
    wrapper(p6); // 传递左值 lvalue const PKi
    wrapper(name); // 传递左值 lvalue const A6_c
    wrapper(n); // 传递左值  lvalue i 已命名的变量为左值
    wrapper(n1); // 传递左值 lvalue i
    wrapper(n2); // 传递左值 lvalue const i
}

int main()
{
    // test_auto1();
    // test_auto_virtual();
    test_auto_autoref_autorefref();

    return 0;
}
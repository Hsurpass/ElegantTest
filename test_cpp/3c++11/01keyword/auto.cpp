#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <typeinfo>

using namespace std;


// 现代C++语言核心特性解析
void test_auto1()
{
//1.当用一个auto关键字声明多个变量的时候，编译器遵循从左到右的推导规则，以最左边的表达式判断auto的具体类型
    int n = 5;
    auto *pn = &n, m =10;   // compile success auto被推到为int.
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
    struct sometype{
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
    auto *j = new auto(5);  // c++11编译通过
//这种用法比较有趣，编译器实际上进行了两次推导，第一次是auto(5),auto被推导为int类型，于是new int 的类型为int*,再通过int*推导i和j的类型。
//我不建议像上面这样使用auto,因为它会破会代码的可读性。在后面的内容中，我们将讨论应该在什么时候避免使用auto关键字。

}

class Base{
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


int main()
{
    // test_auto1();
    test_auto_virtual();

    return 0;
}
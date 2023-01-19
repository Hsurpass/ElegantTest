#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

class Copy
{
public:
    Copy(int i = 10) : _i(new int(i))
    {
        cout << "Copy(int i)" << this << endl;
    }
    // 若拷贝自实现，移动默认即无
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << "Copy(const Copy & another), copy " << &another << " to " << this << endl;
    }
    // 若移动自实现，拷贝默认即无
    Copy(Copy &&another) : _i(nullptr)
    {
        cout << "MOVE Copy(Copy&& another), move " << &another << " to " << this << endl;
        _i = another._i;
        another._i = nullptr;
    }

    Copy &operator=(Copy &&another)
    {
        if (this != &another)
        {

            cout << "MOVE operator=(Copy&& another), move assign " << &another << " to " << this << endl;
            delete _i;
            _i = another._i;
            another._i = nullptr;
        }

        return *this;
    }
    Copy &operator=(const Copy &another)
    {
        cout << "Copy& operator=(const Copy& another), copy assign " << &another << " to " << this << endl;

        if (&another != this)
        {
            delete _i;
            _i = new int(*(another._i));
        }

        return *this;
    }

    ~Copy()
    {
        cout << "~Copy()" << this << endl;
        delete _i;
    }

    void dis() const
    {
        cout << *_i << endl;
    }

    int *_i;
};

Copy getObject()
{
    return Copy();
}

const Copy getConstObject()
{
    return Copy();
}

Copy&& getRvalueReferenceObject()
{
    Copy c;
    return std::move(c);
}

/*********************引用折叠****************************/
// from https://docs.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170
template <typename T>
void print(T &v)
{
    cout << "print(T &v), lvalue, &v: " << &v << ", v:" << *v._i << endl;
}

template <typename T>
void print(const T &v)
{
    cout << "print(const T &v), lvalue, &v: " << &v << ", v:" << *v._i << endl;
}

template <typename T>
void print(T &&v)
{
    cout << "print(T &&v), rvalue, &v:" << &v << ", v:" << *v._i << endl;
}

template <typename T>
void print(const T &&v)
{
    cout << "print(const T &&v), rvalue, &v:" << &v << ", v:" << *v._i << endl;
}

// 折叠规则：遇左则左
// 推导规则：
// 针对万能引用T&&, 如果传递进来的是左值，则T推导为左值引用
// 针对万能引用T&&, 如果传递进来的是右值，则T推导为类型本身
// 针对万能引用T&&, 如果传递进来的是左值引用，则T推导为左值引用
// 针对万能引用T&&, 如果传递进来的是右值引用，则T推导为类型本身 (右值引用?)
template <typename T>
void print_type_and_value(T &&t)
{
    std::cout << std::boolalpha;
    std::cout << "T: " << std::is_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_rvalue_reference<T>::value << std::endl;

    std::cout << "t: " << std::is_reference<T &&>::value << std::endl;
    std::cout << "t: " << std::is_lvalue_reference<T &&>::value << std::endl;
    std::cout << "t: " << std::is_rvalue_reference<T &&>::value << std::endl;

    print(std::forward<T>(t));
}

void test_referenceCollapsing_and_prefectForward()
{
    // The following call resolves to:
    // print_type_and_value<string&>(string& && t)
    // Which collapses to:
    // print_type_and_value<string&>(string& t)
    cout << "-----------lvalue:-----------" << endl;
    Copy s1(1);
    print_type_and_value(s1); // print(T &v), lvalue

    // The following call resolves to:
    // print_type_and_value<const string&>(const string& && t)
    // Which collapses to:
    // print_type_and_value<const string&>(const string& t)
    cout << "---------const lvalue-------------" << endl;
    const Copy s2(2);
    print_type_and_value(s2); // print(const T &v), lvalue,

    // The following call resolves to:
    // print_type_and_value<string&&>(string&& t)
    cout << "---------pure rvalue-------------" << endl;
    print_type_and_value(Copy(3)); // print(T &&v), rvalue,

    // The following call resolves to:
    // print_type_and_value<const string&&>(const string&& t)
    cout << "--------const rvalue--------------" << endl;
    print_type_and_value(getConstObject()); // print(const T &&v), rvalue,

    // The following call resolves to:
    // print_type_and_value<string&&>(string&& t)
    cout << "----------rvalue------------" << endl;
    print_type_and_value(getObject()); // print(T &&v), rvalue,

    // std::move 会把左值转换为右值
    // The following call resolves to:
    // print_type_and_value<string&&>(string&& t)
    cout << "------------std::move----------" << endl;
    print_type_and_value(std::move(s1)); // print(T &&v), rvalue
}

/*********************引用折叠****************************/


// from 现代c++语言核心特性解析 6.8
//T会推导两次
template<typename T>
void bar(T &&t, T v)    // 可以利用这个方法让编译器报错来告诉你推导的类型是什么。
{
    // t = v;  
}


// 如果传递进来的是左值，则推导为左值引用
// 如果传递进来的是右值，则推导为类型本身
// 如果传递进来的是左值引用，则推导为左值引用
// 如果传递进来的是右值引用，则推导为类型本身 (右值引用?)
template<typename T>
void bar__(T &&t) //t是左值， 采用rvalue引用作为参数的函数将参数视为函数正文中的 lvalue。
{
    // T a;
    // T& a;
    // decltype(t) a = 3;

    std::cout << std::boolalpha;
    std::cout << "T: " << std::is_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_rvalue_reference<T>::value << std::endl;

    std::cout << "t: " << std::is_reference<T &&>::value << std::endl;
    std::cout << "t: " << std::is_lvalue_reference<T &&>::value << std::endl;
    std::cout << "t: " << std::is_rvalue_reference<T &&>::value << std::endl;

    // cout << typeid(T).name() << endl;
    // cout << typeid(a).name() << endl;

}

template<typename T>
void bar_(T t)
{
    // t = 2;
    // T a;
    // T& a;
    // T a = 1;

    std::cout << std::boolalpha;
    std::cout << "T: " << std::is_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_rvalue_reference<T>::value << std::endl;

    std::cout << "t: " << std::is_reference<T &&>::value << std::endl;
    std::cout << "t: " << std::is_lvalue_reference<T &&>::value << std::endl;
    std::cout << "t: " << std::is_rvalue_reference<T &&>::value << std::endl;

    // cout << typeid(T).name() << endl;
    // cout << typeid(a).name() << endl;

}

int getval()
{
    return 5;
}

void test_universal_reference_Rreference()
{
    int i = 0;
    const int j = 1;
    int& ri = i;
    // int&& rri = std::move(i);
    int &&rri = 2;
    cout << "&rri:" << &rri << endl;
#if 0
    bar_(i);    // T=int
    bar_(j);    // T=int
    bar_(ri);   // T=int
    bar_(rri);  // T=int
#endif

    cout << "****************************" << endl;
#if 0
    // bar__(i);  //左值 T=int&
    // bar__(j);  //常量左值 T=const int&
    // bar__(1);              //右值 T=int
    // bar__(getval());       //右值 T=int
    // bar__(std::move(i));   //右值 T=int
    // bar__(ri);    //左值引用 T=int&

    // https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170
    // 编译器将已命名的右值引用视为左值，而将未命名的右值引用视为右值。
    // bar__(rri);   // T=int& 为啥推导出来是个左值引用？
    bar__(getRvalueReferenceObject());    // T=Copy
#endif
    cout << "****************************" << endl;
#if 1
    // bar(i, i);  // t的T推导为int&, 折叠后T&&推导为int&, v的T推导为int, 一个T两种类型会冲突
    // bar(j, j);  // t的T推导为const int&, 折叠后T&&推导为const int&, v的T推导为int, 一个T两种类型会冲突
    bar(getval(), 1);   // getval()返回的是右值，t的T推导为int, 折叠后T&&推导为int&&， v的T推导为int, t和v的类型相同不会冲突。
    // bar(ri, 1); // ri是左值引用，t的T推导为int&, 折叠后T&&推导为int&, v的T推导为int, 一个T两种类型会冲突。
    // bar(getRvalueReferenceObject(), 1);    // T=Copy, int
#endif
}

int main()
{
    // test_referenceCollapsing_and_prefectForward();
    test_universal_reference_Rreference();

    return 0;
}
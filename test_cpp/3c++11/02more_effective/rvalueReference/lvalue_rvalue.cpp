#include <iostream>
#include <vector>

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
        cout << " Copy(const Copy & another)" << endl;
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

            cout << "MOVE operator=(Copy&& another)" << endl;
            delete _i;
            _i = another._i;
            another._i = nullptr;
        }

        return *this;
    }
    Copy &operator=(const Copy &another)
    {
        cout << "Copy& operator=(const Copy& another)" << endl;

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

// 将亡值
Copy&& getXvalueObject()
{
    return Copy();
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

// 如果传递进来的是左值，则推导为左值引用
// 如果传递进来的是右值，则推导为类型本身
// 如果传递进来的是左值引用，则推导为左值引用
// 如果传递进来的是右值引用，则推导为右值引用

template <typename T>
void print_type_and_value(T &&t)
{
    std::cout << std::boolalpha;
    std::cout << "T: " << std::is_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_rvalue_reference<T>::value << std::endl;

    std::cout << "t: " << std::is_reference<T&&>::value << std::endl;
    std::cout << "t: " << std::is_lvalue_reference<T&&>::value << std::endl;
    std::cout << "t: " << std::is_rvalue_reference<T&&>::value << std::endl;

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
    print_type_and_value(s1);   // print(T &v), lvalue

    // The following call resolves to:
    // print_type_and_value<const string&>(const string& && t)
    // Which collapses to:
    // print_type_and_value<const string&>(const string& t)
    cout << "---------const lvalue-------------" << endl;
    const Copy s2(2);
    print_type_and_value(s2);   // print(const T &v), lvalue,

    // The following call resolves to:
    // print_type_and_value<string&&>(string&& t)
    cout << "---------pure rvalue-------------" << endl;
    print_type_and_value(Copy(3));  // print(T &&v), rvalue,

    // The following call resolves to:
    // print_type_and_value<const string&&>(const string&& t)
    cout << "--------const rvalue--------------" << endl;
    print_type_and_value(getConstObject()); // print(const T &&v), rvalue,

    // The following call resolves to:
    // print_type_and_value<string&&>(string&& t)
    cout << "----------rvalue------------" << endl;
    print_type_and_value(getObject());  // print(T &&v), rvalue,

    // std::move 会把左值转换为右值
    // The following call resolves to:
    // print_type_and_value<string&&>(string&& t)
    cout << "------------std::move----------" << endl;
    print_type_and_value(std::move(s1) );   // print(T &&v), rvalue

}

/*********************引用折叠****************************/

/************************从 const T& 到 &&*****************************/
void acceptValue(Copy o)
{
    cout << "acceptValue: " << &o << endl;
}
void acceptRef(const Copy &o)
{
    cout << "acceptRef: " << &o << endl;
}
void accetpRRef(Copy &&o)
{
    cout << "accetpRRef: " << &o << endl;
}

void fromConstTRefToRefref()
{
    {
        acceptValue(getObject());
    }
    cout << "------------------------" << endl;
    {
        acceptRef(getObject());
    }
    cout << "------------------------" << endl;
    {
        accetpRRef(getObject());
    }
}

/************************从 const T& 到 &&*****************************/

void test_lvalue()
{
    cout << "&\"abc\":" << &"abc" << endl; // 字符串常量是一个左值， 可以取地址&
    int a = 5;
    int &a1 = a;
    cout << "&a1: " << &a1 << endl;
    cout << "&(a = 1)" << &(a=1) << endl;   // lvalue
    cout << "&(++a)" << &(++a) << endl;   // lvalue
    // cout << "&(a++)" << &(a++) << endl; // rvalue
    cout << "&(cout<<'')" << &(cout << ' ') << endl;    // lvalue operator<<

    const int &a2 = 5;
    cout << "&a2: " << &a2 << endl;

    vector<int> v = {1,2,3};
    auto&& v1 = v[0];   // v1 is lvalue
    cout << &v1 << endl;
}

void test_rvalue()
{
    int a = 10;
    int b = 100;
    int &&a1 = std::move(a);
    // int& b1 = std::move(b);  // error

    cout << "a1:" << a1 << endl;
    cout << "a:" << a << endl;
    cout << "&a1:" << &a1 << endl;
    cout << "&a:" << &a << endl;

    Copy c = getObject();
    c.dis();
    const Copy &c1 = getObject();
    c1.dis();
    Copy &&c2 = getObject();
    c2.dis();
}

void test_xvalue()
{
    // getObject().dis();
    // cout << &(getXvalueObject()) << endl;   // xvalue不能&
    const Copy& c = getXvalueObject();    // xvalue
    c.dis();
}

int main()
{
    // test_lvalue();
    cout << "----------------------" << endl;
    // test_rvalue();
    cout << "----------------------" << endl;
    // test_xvalue();
    // fromConstTRefToRefref();
    test_referenceCollapsing_and_prefectForward();

    return 0;
}
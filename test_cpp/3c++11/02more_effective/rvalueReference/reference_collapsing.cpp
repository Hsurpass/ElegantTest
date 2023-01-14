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

// 遇左则左
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


int main()
{
    test_referenceCollapsing_and_prefectForward();

    return 0;
}
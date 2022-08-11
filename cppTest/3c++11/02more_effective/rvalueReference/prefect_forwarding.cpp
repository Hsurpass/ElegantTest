#include <iostream>

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

// from https://docs.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170
void g(const Copy &)
{
    cout << "In g(const Copy&)." << endl;
}

void g(Copy &&)
{
    cout << "In g(Copy&&)." << endl;
}

Copy &&f(Copy &&block)
{
    g(block);
    return move(block);
}

void test_lvalueArg_And_rvalueArg()
{
    // In g(const Copy&).
    // In g(Copy&&).
    g(f(Copy()));

    cout << "--------------------------" << endl;

    Copy block;
    g(block);  // In g(const Copy&). 
    g(static_cast<Copy&&>(block));  // 强制转换成右值 In g(Copy&&).
}

template <typename T>
void print(T &v)
{
    cout << "print(T &v), lvalue, &v: " << &v << ", v:" << v << endl;
}

template <typename T>
void print(const T &v)
{
    cout << "print(const T &v), lvalue, &v: " << &v << ", v:" << v << endl;
}

template <typename T>
void print(T &&v)
{
    cout << "print(T &&v), rvalue, &v:" << &v << ", v:" << v << endl;
}

template <typename T>
void print(const T &&v)
{
    cout << "print(const T &&v), rvalue, &v:" << &v << ", v:" << v << endl;
}

template <typename T>
void testForward(T &&v)
{
    // v作为参数永远是一个左值或左值引用
    std::cout << std::boolalpha;
    std::cout << "T: " << std::is_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T: " << std::is_rvalue_reference<T>::value << std::endl;

    std::cout << "t: " << std::is_reference<T&&>::value << std::endl;
    std::cout << "t: " << std::is_lvalue_reference<T&&>::value << std::endl;
    std::cout << "t: " << std::is_rvalue_reference<T&&>::value << std::endl;

    cout << "testForward, &v:" << &v << ", v:" << v << endl;
    // ++v;
    print(v);
    print(std::forward<T>(v));
    print(std::move(v));
}

void test_prefectForward()
{
    cout << "---------pure rvalue----------------" << endl;
    testForward(1); // lvalue rvalue rvalue

    cout << "---------lvalue----------------" << endl;
    int x = 1;
    testForward(x); // lvalue lvalue rvalue
    cout << "x: " << x << endl;

    cout << "---------std::forward<int>----------------" << endl;
    testForward(std::forward<int>(x)); // lvalue rvalue rvalue   return static_cast<int&&>(x) ---> testForward<int&&>(int&& && v)
    cout << "x: " << x << endl;

    cout << "---------std::forward<int&>----------------" << endl;
    testForward(std::forward<int &>(x)); // lvalue lvalue rvalue
    cout << "x: " << x << endl;

    cout << "---------std::forward<int&&>----------------" << endl;
    testForward(std::forward<int &&>(x)); // lvalue rvalue rvalue
    cout << "x: " << x << endl;
    cout << "x: " << x << endl;

    cout << "------std::move()-------------------" << endl;
    testForward(std::move(x)); // lvalue rvalue rvalue
    cout << "x: " << x << endl;

    cout << "---------const lvalue----------------" << endl;
    const int x1 = 1;
    testForward(x1); // lvalue lvalue rvalue
    cout << "x1: " << x1 << endl;
}

int main()
{
    test_prefectForward();
    // test_lvalueArg_And_rvalueArg();

    return 0;
}
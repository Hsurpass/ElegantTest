// g++ -fno-elide-constructors
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
        cout << "Copy(const Copy & another)" << endl;
    }
    // 若移动自实现，拷贝默认即无
    // Copy(Copy &&another) : _i(nullptr)
    // {
    //     cout << "MOVE Copy(Copy&& another), move " << &another << " to " << this << endl;
    //     _i = another._i;
    //     another._i = nullptr;
    // }
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
    Copy c;

    return c;
}

void test_return_expired_value()
{
    // Copy(int i)0x7fffcbfddc50
    // MOVE Copy(Copy&& another), move 0x7fffcbfddc50 to 0x7fffcbfddc88
    // ~Copy()0x7fffcbfddc50
    // ~Copy()0x7fffcbfddc88
    
    // 若没有移动构造则调用 copy constructor
    const Copy &cc = getObject();
}

int main()
{
    test_return_expired_value();

    return 0;
}
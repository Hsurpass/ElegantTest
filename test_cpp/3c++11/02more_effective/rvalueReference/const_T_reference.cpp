// g++ -fno-elide-constructors
#include <iostream>
#include <memory>

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

            cout << "MOVE operator=(Copy&& another) , move " << &another << " to " << this << endl;
            delete _i;
            _i = another._i;
            another._i = nullptr;
        }

        return *this;
    }
    Copy &operator=(const Copy &another)
    {
        cout << "Copy& operator=(const Copy& another), copy " << &another << " to " << this << endl;

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

/* 
    万能引用(既能引用左值又能引用右值)分为两种:
        一种是常量左值引用：const T& , const auto&
            缺点: 引用的常量性，不可更改对象的常量性，常见copy constructor ,copy assign
        一种是右值引用：T && , auto &&

*/
template<typename T>
void test_const_T_Lreference(const T& obj)
{
    // Copy(int i)0x7fffcbfddc50
    // MOVE Copy(Copy&& another), move 0x7fffcbfddc50 to 0x7fffcbfddc88
    // ~Copy()0x7fffcbfddc50
    // ~Copy()0x7fffcbfddc88
    
    // 若没有移动构造则调用 copy constructor
    obj.dis();
}

void test_const_auto_Lreference(const auto& obj)
{
    // Copy(int i)0x7fffcbfddc50
    // MOVE Copy(Copy&& another), move 0x7fffcbfddc50 to 0x7fffcbfddc88
    // ~Copy()0x7fffcbfddc50
    // ~Copy()0x7fffcbfddc88
    
    // 若没有移动构造则调用 copy constructor
    obj.dis();
}

template<typename T>
void test_T_rvalue_reference(T&& obj)
{
    // T& a;
    obj.dis();
}

void test_auto_rvalue_reference(auto&& obj)
{
    obj.dis();
}

int main()
{
    // Copy c;

    // test_const_T_Lreference(c);
    // test_const_T_Lreference(getObject());

    // {
    //     const auto &cc = getObject();
    //     cc.dis();
    // }
    // test_const_auto_Lreference(c);
    // test_const_auto_Lreference(getObject());

    // std::shared_ptr<Copy> spc(new Copy());
    // const weak_ptr<Copy>& wpc = spc;
    

    test_T_rvalue_reference(getObject());
    // test_auto_rvalue_reference(getObject());

    return 0;
}
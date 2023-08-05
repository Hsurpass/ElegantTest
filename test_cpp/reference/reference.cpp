#include <iostream>

using namespace std;

void test_reference01()
{
    int i = 10, &r1 = i;
    double d = 0, &r2 = d;
    // int &r3 = d; // error
    cout << "&i: " << &i << endl;   // &i: 0x7ffca6e8f838
    cout << "&r1: " << &r1 << endl; // &r1: 0x7ffca6e8f838
    int a = 100;
    r1 = a; // 引用一经声明不可变更。初始化时为谁的引用就是谁的引用，不可中间在更改引用的对象。
    cout << "r1:" << r1 << endl;

    int &tmp = r1;
    cout << "tmp:" << tmp << endl;
    cout << "i:" << i << ", r1:" << r1 << endl;

    const int &tmp1 = i;
    r1 = 100;
    cout << "tmp1:" << tmp1 << endl;
    cout << "tmp:" << tmp << endl;
    cout << "i:" << i << ", r1:" << r1 << endl;

    ////////////////////////////////////////////////////
    cout << "d:" << d << ", r2:" << r2 << endl;
    r2 = 3.14159;
    cout << "d:" << d << ", r2:" << r2 << endl;

    // r2 = r1; // type cast int to double
    // cout << "d:" << d << ", r2:" << r2 << endl;

    // i = r2; // type cast double to int
    // cout << "i:" << i << ", r1:" << r1 << endl;

    // r1 = d; // type cast double to int
    // cout << "i:" << i << ", r1:" << r1 << endl;

    int *p = &i;
    int &pr = *p;
    cout << "pr:" << pr << endl;
}

struct R
{
    char &r;
};
void test_sizeof_reference()
{
    cout << sizeof(void *) << endl; // 8
    cout << sizeof(R) << endl;      // 8
}

class B
{
public:
    B(double b = 20.1) { m_b = b; }
    double m_b;
};

class A
{
public:
    A(int &a, B& b):m_a(a), _b(b) {}
    A& operator=(const A& other) {
        if( this == &other)
            return *this;
        m_a = other.m_a;
        _b = other._b;

        return * this;
    }
    
    void setreference(int &a) { m_a = a; }

    int& m_a;
    B& _b;
};

void test_class_copy_reference()
{
    int aa = 10;
    B bb;

    A a(aa, bb);
    cout << a.m_a << endl;
    cout << a._b.m_b << endl;

    A a1 = a;
    cout << a1.m_a << endl;
    cout << a1._b.m_b << endl;
    
    int aa_ = 60;
    a1.setreference(aa_);   // 这个只是改变类内引用所指向对象的值，而不是改变引用的指向。
    cout << a1.m_a << endl;
    cout << a1._b.m_b << endl;
    a1.m_a = 500;
    cout << a1.m_a << endl;
    cout << a1._b.m_b << endl;
    cout << aa << endl;
    cout << "-----------------------" << endl;

    int aa1 = 20;
    B bb1(40.1);
    A a_(aa1, bb1);

    a1 = a_;
    cout << a1.m_a << endl;
    cout << a1._b.m_b << endl;
}

int main()
{
    // test_reference01();
    // test_sizeof_reference();
    test_class_copy_reference();

    return 0;
}

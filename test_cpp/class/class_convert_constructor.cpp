#include <iostream>

using namespace std;

class B
{
public:
    B(int b):m_b(b){}
    int m_b;
};

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }

    A(double a)
    {
        cout << "A(int a)" << endl;
        m_a = a;
    }

    A(const B& b)
    {
        cout << "convert constructor" << endl;
        m_a = b.m_b; 
    }

    A& operator=(const B& b)
    {
        cout << "A& operator=(const B& b)" << endl;
        m_a = b.m_b; 

        return *this;
    }

    void dis() const
    {
        cout << "m_a:" << m_a << endl;
    }

    double m_a;
};

void test_convert_constructor()
{
    B b(10);
    A a = b;
    a.dis();
    cout << "--------------------------------" << endl;

    B b1(100);
    a = b1;
    a.dis();
    cout << "--------------------------------" << endl;

    const A& a1 = b1;
    cout << "&a1:" << &a1 << endl;
    cout << "&b1:" << &b1 << endl;
    a1.dis();

    cout << "--------------------------------" << endl;
    A a2 = 2;    // A(int a) 隐式构造
}


// class D;
class C
{
public:
    C()
    {
        cout << "C()" << endl;
    }

    C(const C& c)
    {
        cout << "C(const B& b)" << endl;
        m_c = c.m_c; 
    }

    C& operator=(const C& c)
    {
        cout << "C& operator=(const C& c)" << endl;
        if (this == &c)
            return *this;
        m_c = c.m_c; 
        return * this;
    }

    // C(const D& d)
    // {
    //     cout << "convert constructor" << endl;
    //     m_c = d.m_c; 
    // }

    // C& operator=(const D& d)
    // {
    //     cout << "C& operator=(const D& d)" << endl;
    //     m_c = d.m_c; 

    //     return *this;
    // }

    void dis() const
    {
        cout << "m_c:" << m_c << endl;
    }

    double m_c;
};

class D : public C
{
public:
    D(){ cout << "D()" << endl; }

    int m_d;
};

void test()
{
    D d;
    const C& c = d;
}


int main()
{
    test_convert_constructor();

    return 0;
}


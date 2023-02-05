#include <iostream>

using namespace std;

class Base {
public:
    Base(int a_ = 10):a(a_) { cout << "Base(int a_ = 10)" << endl; }
    Base(const Base& another) { cout << "Base(const Base& another)" << endl; a = another.a; }
    Base& operator=(const Base& another) { cout << "Base& operator=()" << endl;  a = another.a; return *this; }
    virtual ~Base(){cout << "~Base()" << endl;}

    virtual void x() { cout << "Base::x()" << endl; }

    int a;
};

class A : public Base
{
public:
    A(int a_ = 10):Base(a_) { cout << "A(int a_ = 10)" << endl; }
    A(const A& another) { cout << "A(const A& another)" << endl; a = another.a; }
    A& operator=(const A& another) { cout << "A& operator=()" << endl;  a = another.a; return *this; }
    ~A(){cout << "~A()" << endl;}

    void x() { cout << "A::x()" << endl; }
    virtual void y() { cout << "A::y()" << endl; }

};

class B : public Base
{
public:
    B(int a_ = 20):Base(a_) { cout << "B(int a_ = 20)" << endl; }
    B(const B& another) { cout << "B(const B& another)" << endl; a = another.a; }
    B& operator=(const B& another) { cout << "B& operator=()" << endl;  a = another.a; return *this; }
    ~B(){cout << "~B()" << endl;}

    void x() { cout << "B::x()" << endl; }
    virtual void z() { cout << "B::z()" << endl; }

};

// 菱形问题 父类构造顺序：从左到右
class C : public A, public B
{
public:
    C(int a_ = 30):
    a(a_),
    A(a_*10),B(a_*100) { cout << "C(int a_ = 30)" << endl; }
    ~C(){cout << "~C()" << endl;}
    
    void x() { cout << "C::x()" << endl; }
    int a;
};

/*
构造、析构顺序：
Base(int a_ = 10)
A(int a_ = 10)
Base(int a_ = 10)
B(int a_ = 20)
C(int a_ = 30)
~C()
~B()
~Base()
~A()
~Base()
*/
// 同名隐藏，赋值兼容同样适用
void test_C_name_covered()
{
    cout << sizeof(Base) << endl; // 4+8=12 --> 16
    cout << sizeof(A) << endl;    // 4+8=12 --> 16
    cout << sizeof(B) << endl;    // 4+8=12 --> 16
    cout << sizeof(C) << endl;    // 12+8+8=28 --> 32 两张虚表
    
    C c;
    // cout << c.A::Base::a << endl; // error ambigous
    cout << c.A::a << endl; // 10
    cout << c.B::a << endl; // 20
    cout << c.a << endl;    // 30

    // 不定义C的虚函数会ambigous
    c.x();      // C::x()
    c.A::x();   // A::x()
    c.B::x();   // B::x()
}

void test_diamond_vtable()
{
    Base base;
    A a;
    B b;
    C c;

    // Base* pbase = &c;   // ambigous
    A* pa = &c;
    B* pb = &c;

    cout << "---------------------------" << endl;
    pa->x();    // C::x()
    pb->x();    // C::x()
    cout << "---------------------------" << endl;

}

int main()
{
    test_C_name_covered();
    // test_diamond_vtable();
}
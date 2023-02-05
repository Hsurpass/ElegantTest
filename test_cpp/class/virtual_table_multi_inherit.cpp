#include <iostream>

using namespace std;

class A
{
public:
    A(int a_ = 10):a(a_) { cout << "A(int a_ = 10)" << endl; }
    A(const A& another) { cout << "A(const A& another)" << endl; a = another.a; }
    A& operator=(const A& another) { cout << "A& operator=()" << endl;  a = another.a; return *this; }
    virtual ~A(){cout << "~A()" << endl;}

    void func() { cout << "A::func()" << endl; }
    virtual void x() { cout << "A::x()" << endl; }
    virtual void z() { cout << "A::z()" << endl; }

    int a;
};

class B{
public:
    B(int a_ = 20):a(a_) { cout << "B(int a_ = 20)" << endl; }
    B(const B& another) { cout << "B(const B& another)" << endl; a = another.a; }
    B& operator=(const B& another) { cout << "B& operator=()" << endl;  a = another.a; return *this; }
    ~B(){cout << "~B()" << endl;}

    void func() { cout << "B::func()" << endl; }
    virtual void y() { cout << "B::y()" << endl; }
    virtual void z() { cout << "B::z()" << endl; }

    int a;
};

// 三角问题 父类构造顺序：从左到右
class C : public A, public B
{
public:
    C(int a_ = 30):a(a_),A(a_*10),B(a_*100) { cout << "C(int a_ = 30)" << endl; }
    ~C(){cout << "~C()" << endl;}
    
    void func() { cout << "C::func()" << endl; }
    virtual void z() { cout << "C::z()" << endl; }

    int a;
};

// 同名隐藏，赋值兼容同样适用
void test_C_name_covered()
{
    cout << sizeof(C) << endl;  // 12+8+8=28 -->内存对齐：24 两张虚表
    C c;
    cout << c.A::a << endl; // 10
    cout << c.B::a << endl; // 20
    cout << c.a << endl;    // 30

    c.func();
    c.A::func();
    c.B::func();

    c.x();      // A::x()
    c.y();      // B::y()
    c.z();      // C::z()
    c.A::z();   // A::z()
    c.B::z();   // B::z()
}

void test_multiple_inherit_vtable()
{
    A a;
    B b;
    C c;
    A *pa = &c;
    B *pb = &c;

    pa->z();
    pb->z();
}

int main()
{
    test_C_name_covered();
    // test_multiple_inherit_vtable();

    return 0;
}
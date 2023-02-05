#include <iostream>

using namespace std;

class Base {
public:
    Base(int a_ = 10):a(a_) { cout << "Base(int a_ = 10)" << endl; }
    Base(const Base& another) { cout << "Base(const Base& another)" << endl; a = another.a; }
    Base& operator=(const Base& another) { cout << "Base& operator=()" << endl;  a = another.a; return *this; }
    ~Base(){cout << "~Base()" << endl;}

    void func() { cout << "Base::func()" << endl; }
    int a;
};

class A : public Base
{
public:
    A(int a_ = 10):Base(a_) { cout << "A(int a_ = 10)" << endl; }
    A(const A& another) { cout << "A(const A& another)" << endl; a = another.a; }
    A& operator=(const A& another) { cout << "A& operator=()" << endl;  a = another.a; return *this; }
    ~A(){cout << "~A()" << endl;}

    void func() { cout << "A::func()" << endl; }
};

class B : public Base
{
public:
    B(int a_ = 20):Base(a_) { cout << "B(int a_ = 20)" << endl; }
    B(const B& another) { cout << "B(const B& another)" << endl; a = another.a; }
    B& operator=(const B& another) { cout << "B& operator=()" << endl;  a = another.a; return *this; }
    ~B(){cout << "~B()" << endl;}

    void func() { cout << "B::func()" << endl; }

};

// 菱形问题 父类构造顺序：从左到右
class C : public A, public B
{
public:
    C(int a_ = 30):
    //a(a_),
    A(a_*10),B(a_*100) { cout << "C(int a_ = 30)" << endl; }
    ~C(){cout << "~C()" << endl;}
    
    void func() { cout << "C::func()" << endl; }
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
    cout << sizeof(Base) << endl; // 4
    cout << sizeof(A) << endl;    // 4
    cout << sizeof(B) << endl;    // 4
    cout << sizeof(C) << endl;    // 12
    
    C c;
    // cout << c.A::Base::a << endl; // error ambigous
    cout << c.A::a << endl; // 10
    cout << c.B::a << endl; // 20
    cout << c.a << endl;    // 30

    c.func();
    c.A::func();
    c.B::func();
}

void test_C_assign_compatibility()
{
    Base base;
    A a;
    B b;
    C c;
    
    // base = c;   // error ambigous

    a = c;
    cout << a.a << endl;
    b = c;
    cout << b.a << endl;

    // Base base_ = c; // error ambigous
    A a_ = c;
    B b_ = c;
    
    cout << "----------------------------" << endl;
    // Base& base1 = c; // error ambigous
    A& a1 = c;
    B& b1 = c;
    cout << a1.a << endl;
    cout << b1.a << endl;

    cout << "----------------------------" << endl;
    // Base* pbase = &c; // error ambigous
    A* pa = &c;
    B* pb = &c;
    cout << pa->a << endl;
    cout << pb->a << endl;
}

// 
int main()
{
    // test_C_name_covered();
    test_C_assign_compatibility();

    return 0;
}
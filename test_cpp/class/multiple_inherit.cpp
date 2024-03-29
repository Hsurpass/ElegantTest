#include <iostream>

using namespace std;

class A
{
public:
    A(int a_ = 10):a(a_) { cout << "A(int a_ = 10)" << endl; }
    A(const A& another) { cout << "A(const A& another)" << endl; a = another.a; }
    A& operator=(const A& another) { cout << "A& operator=()" << endl;  a = another.a; return *this; }
    ~A(){cout << "~A()" << endl;}

    void func() { cout << "A::func()" << endl; }
    int a;
};

class B{
public:
    B(int a_ = 20):a(a_) { cout << "B(int a_ = 20)" << endl; }
    B(const B& another) { cout << "B(const B& another)" << endl; a = another.a; }
    B& operator=(const B& another) { cout << "B& operator=()" << endl;  a = another.a; return *this; }
    ~B(){cout << "~B()" << endl;}

    void func() { cout << "B::func()" << endl; }

    int a;
};

// 三角问题 父类构造顺序：从左到右
class C : public A, public B
{
public:
    C(int a_ = 30):a(a_),A(a_),B(a_) { cout << "C(int a_ = 30)" << endl; }
    ~C(){cout << "~C()" << endl;}
    
    void func() { cout << "C::func()" << endl; }
    int a;
};

// 同名隐藏，赋值兼容同样适用
void test_C_name_covered()
{
    cout << sizeof(C) << endl;  // 12
    C c;
    cout << c.A::a << endl; // 10
    cout << c.B::a << endl; // 20
    cout << c.a << endl;    // 30

    c.func();
    c.A::func();
    c.B::func();

}

void test_C_assign_compatibility()
{
    A a;
    B b;
    C c;

    a = c;
    cout << a.a << endl;
    b= c;
    cout << c.a << endl;

    A a_ = c;
    B b_ = c;
    
    cout << "----------------------------" << endl;
    A& a1 = c;
    B& b1 = c;
    cout << a1.a << endl;
    cout << b1.a << endl;

    cout << "----------------------------" << endl;
    A* pa = &c;
    B* pb = &c;
    cout << pa->a << endl;
    cout << pb->a << endl;
}

// 
int main()
{
    test_C_name_covered();
    // test_C_assign_compatibility();

    return 0;
}
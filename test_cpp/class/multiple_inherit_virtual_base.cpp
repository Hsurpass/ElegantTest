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

// 使用虚析构
class A : virtual public Base
{
public:
    A(int a_ = 20):
    // a(a_), 
    Base(a_) { cout << "A(int a_ = 20)" << endl; }
    A(const A& another) { cout << "A(const A& another)" << endl; a = another.a; }
    A& operator=(const A& another) { cout << "A& operator=()" << endl;  a = another.a; return *this; }
    ~A(){cout << "~A()" << endl;}

    void func() { cout << "A::func()" << endl; }
    // int a; //既然继承了虚基类就不要有同名的变量出现了
};

class B : virtual public Base
{
public:
    B(int a_ = 30):
    // a(a_),
    Base(a_) { cout << "B(int a_ = 30)" << endl; }
    B(const B& another) { cout << "B(const B& another)" << endl; a = another.a; }
    B& operator=(const B& another) { cout << "B& operator=()" << endl;  a = another.a; return *this; }
    ~B(){cout << "~B()" << endl;}

    void func() { cout << "B::func()" << endl; }
    // int a; //既然继承了虚基类就不要有同名的变量出现了
};

// 菱形问题 父类构造顺序：从左到右且虚基类只构造一次
// 实现了在多继承中只保留了一份数据成员。A,B共享虚基类中的数据，且虚基类中初始化只能由C初始化(A，B中构造Base是无效的)。
class C : public A, public B
{
public:
    C(int a_ = 40):
    a(a_)
    ,A(a_)
    ,B(a_)
    ,Base(a_*3) 
    { cout << "C(int a_ = 40)" << endl; }
    ~C(){cout << "~C()" << endl;}
    
    void func() { cout << "C::func()" << endl; }
    int a;
};

/*
构造、析构顺序：
Base(int a_ = 10)
A(int a_ = 10)
B(int a_ = 20)
C(int a_ = 30)
~C()
~B()
~A()
~Base()
*/
// 同名隐藏，赋值兼容同样适用
void test_C_name_covered()
{
    cout << sizeof(Base) << endl; // 4
    cout << sizeof(A) << endl;    // 4+8(虚表?)=12 --> 16
    cout << sizeof(B) << endl;    // 4+8(虚表?)=12 --> 16
    cout << sizeof(C) << endl;    // 4+8(虚表?)+8(虚表?)=20 --> 24
    
    C c;
    cout << c.Base::a << endl;      // 120
    cout << c.A::Base::a << endl;   // 120 correct
    cout << c.B::Base::a << endl;   // 120 correct

    cout << c.A::a << endl; // 120
    cout << c.B::a << endl; // 120
    cout << c.a << endl;    // 40

    c.func();       // C::func()
    c.A::func();    // A::func()
    c.B::func();    // B::func()
}

void test_C_assign_compatibility()
{
    Base base;
    A a;
    B b;
    C c;
    
#if 1
    base = c; 
    cout << base.a << endl; // 拷贝赋值，120
    a = c;
    cout << a.a << endl;    // 拷贝赋值，20
    b = c;
    cout << b.a << endl;    // 拷贝赋值，30

    cout << "----------------------------" << endl;
    
    Base base_ = c;
    cout << base.a << endl; // 拷贝构造，120
    A a_ = c;
    cout << a.a << endl;    // 拷贝构造，20
    B b_ = c;
    cout << b.a << endl;    // 拷贝构造，30
#endif 
#if 0
    cout << "----------------------------" << endl;
    Base& base1 = c; // correct
    A& a1 = c;
    B& b1 = c;
    cout << base1.a << endl;    //120
    cout << a1.a << endl;       //120
    cout << b1.a << endl;       //120
#endif 
#if 0
    cout << "----------------------------" << endl;
    Base* pbase = &c; // correct
    A* pa = &c;
    B* pb = &c;
    cout << pbase->a << endl;   //120
    cout << pa->a << endl;      //120
    cout << pb->a << endl;      //120
#endif 
}

// 
int main()
{
    // test_C_name_covered();
    test_C_assign_compatibility();

    return 0;
}
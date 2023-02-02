#include <iostream>

using namespace std;

class A
{
public:
    void f1() { cout << "A::f1()" << endl; }
    
    virtual void f1(int a) { cout << "virtual A::f1(int)" << endl; }
    virtual void f2() { cout << "virtual A::f2()" << endl; }
    
    void f3() { cout << "A::f3()" << endl; }
    void f3(double d) { cout << "A::f3(double)" << endl; }
    void f5() { cout << "A::f5()" << endl; }
};

class B : public A
{
public:
    void f1() { cout << "B::f1()" << endl; }
    void f3() { cout << "B::f3()" << endl; }
    void f4() { cout << "B::f4()" << endl; }
};

class C : public A
{
public:
    using A::f1;
    using A::f3;

    void f1() { cout << "C::f1()" << endl; }
    void f3() { cout << "C::f3()" << endl; }
    void f4() { cout << "C::f4()" << endl; }

};

void name_coverd1()
{
    B b;
    b.f1(); // B::f1()
    // b.f1(10);   // error 只要子类中有同名的，则父类中所有同名的都被隐藏(不管是不是虚函数)
    b.f2(); // A::f2()
    b.f3(); // B::f3()
    // b.f3(2.1);  // error 只要子类中有同名的，则父类中所有同名的都被隐藏(不管是不是虚函数)
    b.f4(); // B::f4() 
}

void name_coverd2()
{
    C c;
    c.f1();     // C::f1()
    c.f1(10);   // A::f1(int)   
    c.f2();     // A::f2()
    c.f3();     // C::f3()
    c.f3(2.1);  // A::f3(double)
    c.f4();     // C::f4() 
}

void name_coverd3()
{
    B b;
    A* pa = &b; 
    pa->f5();   // A::f5()

    B* pb = &b;
    pb->f5();   // A::f5()
}

int main()
{
    // name_coverd1();
    // name_coverd2();
    name_coverd3();

    return 0;
}
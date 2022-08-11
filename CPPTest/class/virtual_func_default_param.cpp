#include <iostream>

using namespace std;

// effective c++ 条款37
// virtual函数是静态绑定，默认参数值是静态绑定
class A
{
public:
    virtual void f1(int m = 10) { cout << "A::f1(int m = 10), m = " << m << endl; } 
};

class B : public A
{
public:
    void f1(int m) { cout << "B::f1(int m), m = " << m << endl; }
};

class C : public A
{
public:
    void f1(int m = 100) { cout << "C::f1(int m), m = " << m << endl; }
};

void test_virtual_func_default_param01()
{
    A* pa = new B();
    pa->f1();   
    delete pa;
}

void test_virtual_func_default_param02()
{
    A* pa = new C();
    pa->f1();   
    delete pa;
}

int main()
{   
    // test_virtual_func_default_param01();
    test_virtual_func_default_param02();

    return 0;
}
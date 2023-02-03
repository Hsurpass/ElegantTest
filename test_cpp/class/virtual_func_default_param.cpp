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
    void f1(int m) override { cout << "B::f1(int m), m = " << m << endl; }
};

class C : public A
{
public:
    void f1(int m = 100) override { cout << "C::f1(int m), m = " << m << endl; }
};

// c++ primer 15.3 虚函数与默认实参。 对于虚函数如果某次函数调用使用了默认实参，则该实参值由本次调用的静态类型决定。
// 也就是说，如果我们通过基类的引用或指针调用函数，则使用基类中定义的默认实参。
void test_virtual_func_default_param01()
{
    A* pa = new B();
    pa->f1();    // B::f1(int m), m = 10
    delete pa;
}

void test_virtual_func_default_param02()
{
    A* pa = new C();
    pa->f1();   // C::f1(int m), m = 10
    delete pa;
}

int main()
{   
    // test_virtual_func_default_param01();
    test_virtual_func_default_param02();

    return 0;
}
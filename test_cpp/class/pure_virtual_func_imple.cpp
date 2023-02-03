#include <iostream>

using namespace std;

class A
{
public:
    A(){ cout << "A()" << endl; }
    virtual void f() = 0;

};

void A::f()
{
    cout << "A::f()" << endl;
}

class B : public A
{
public:
    B(){ cout << "B()" << endl; }
    virtual void f() 
    {
        cout << "B::f()" << endl;
        A::f();
    }
};

void test_pure_func01()
{
    // A* pa = new A();
    A* pa = new B();
    pa->f();
}

int main()
{
    test_pure_func01();

    return 0;
}
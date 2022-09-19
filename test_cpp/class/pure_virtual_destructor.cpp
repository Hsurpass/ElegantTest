#include <iostream>

using namespace std;

class A
{
public:
    A() { cout << "A()" << endl; }
    virtual ~A() = 0;
};

// effective C++ 条款07
A::~A() { cout << "~A()" << endl; }

class B : public A
{
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
};

void test_pure_virtual_destructor()
{
    // A a;

    A* pa = new B();

    delete pa;
}

int main()
{
    test_pure_virtual_destructor();

}
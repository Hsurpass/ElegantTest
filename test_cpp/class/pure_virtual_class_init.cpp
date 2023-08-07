#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }
    virtual void f() = 0;
    virtual void g() = 0;
};

void A::f()
{
    cout << "A::f()" << endl;
}

class B : public A
{
public:
    B()
    {
        cout << "B()" << endl;
    }
    virtual void f()
    {
        cout << "B::f()" << endl;
        A::f();
    }
};

int main()
{
    // A a;
    // B b;    // 只要父类的纯虚函数有一个没被覆写，那么子类就是抽象基类，不能被实例化。

    return 0;
}
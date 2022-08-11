#include <iostream>

using namespace std;

class A
{
public:
    virtual void func() const { cout << "A::func()" << endl; };
};

class B : public A
{
public:
    void func() const override final
    {
        cout << "B::func()" << endl;
    }
};

// 阻止了虚函数的覆写
// 阻止了类的无限扩展。
class C : public B
{
public:
    // void func() const override
    // {
    //     cout << "C::func()" << endl;
    // }
};

void test_final()
{
    B b;
}

int main()
{
    test_final();

    return 0;
}
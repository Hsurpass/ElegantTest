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
    // 阻止了虚函数的覆写
    void func() const override final
    {
        cout << "B::func()" << endl;
    }
};

// 阻止了类的无限扩展。
class C final : public B
{
public:
    // void func() const override  // 无法覆写虚函数，编译器报错
    // {
    //     cout << "C::func()" << endl;
    // }
};

// class D : public C  //阻止了类的继承
// {
// public:

// };

int main()
{

    return 0;
}
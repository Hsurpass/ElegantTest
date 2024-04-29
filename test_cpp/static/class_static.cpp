#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }
private:
};

class B
{
public:
    B()
    {
        cout << "B()" << endl;
    }
private:
    static A
        a; // 类内静态成员变量的初始化必须在类外部进行初始化，因为静态成员是类的所有对象所共享的，不仅仅是某个对象的属性。
};

A B::a; // 静态成员变量是在main函数之前初始化的.

int main()
{
    cout << "main" << endl;
    B b;

    return 0;
}
#include <iostream>

using namespace std;

class A
{
public:
    A() {}
    virtual ~A(){}
    static int s;

    void print_a() { cout << "A::a:" << a << endl; }
// private:
    int a = 10;
protected:
    float c;
};

class B : public A
{
public:
    static int t;
    void print_a() { cout << "B::a:" << a << endl; }    // 同名，隐藏父类

public:
    int a = 100;

private:
    float c;
};

class C : public B
{
public:
    int a;

};

class D : public A
{

};

// 不存在基类向派生类的隐式转换。c++ primer 15.2
void test01()
{
    // A a;
    // B* pb = &a; // ERROR 下转
    // B& b = a; // error

    // 即使一个基类指针或引用绑定在一个派生类对象上，我们也不能执行基类向派生类的转换。
    B b;
    D d;
    A* pa = &b;
    A* pa1 = &d;

    // 使用dynamic_cast可以从基类转向派生类,但必须有虚函数
    B* pb = dynamic_cast<B*>(pa);   // 如果基类确实指向派生类，则dynamic_cast会返回派生类指针
    if(pb != NULL)
    {
        cout << "pa point to derived class (B)" << endl;
    }

    B& refb = dynamic_cast<B&>(*pa);    // 如果基类确实指向派生类，则dynamic_cast会返回派生类对象

    B* pb1 = dynamic_cast<B*>(pa1); // 如果基类不指向派生类，则dynamic_cast会返回NULL
    if(pb1 == NULL)
    {
        cout << "pa1 point to derived class (D)" << endl;
    }

    // B& refb1 = dynamic_cast<B&>(*pa1);     // 如果基类不指向派生类，则 throw exception: std::bad_cast

}

int main()
{
    test01();
    return 0;
}
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

void test01()
{
    cout << sizeof(int) << sizeof(float) << sizeof(double) << sizeof(void*) << endl; // 4 4 8
    cout << "sizeof(A): " << sizeof(A) << endl; // 8  | 有虚函数：8+8=16 虚函数还要占一个void*这么多的字节
    cout << "sizeof(B): " << sizeof(B) << endl; // 16 |          8+8+8=24
    cout << "sizeof(C): " << sizeof(C) << endl; // 20 |          4+8+8+8=28 --> 内存对齐 28 + 4 = 32
}

void test02()
{
    A a;
    B b;

    cout << a.a << endl;    // 10
    cout << b.a << endl;    // 100
    cout << b.A::a << endl; // 10

}


void test03()
{
    A a;
    B b;

    A* pa = new B();
    pa->print_a();  // 10
    b.print_a();    // 100
}

int main()
{
    // test01();
    // test02();
    test03();
    

    return 0;
}
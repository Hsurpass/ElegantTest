#include <iostream>

using namespace std;

class A
{
public:
    int a = 10;
    float getc() { return c; }    // 父类是看不到子类成员的，所以即使同名也始终访问的是父类成员。
protected:
    float c = 12.1;
};

class B : public A
{
    friend void func(B& b);
public:
    int a = 100;
private:
    float c = 15.22;
};

class C : public A
{
public:
    C()
    {
        this->a = 1000;
    }
};

void func(B& b)
{
    cout << b.c << endl;    // 15.22
    cout << b.A::c << endl; // 12.1
}

void test01()
{
    A a;
    B b;

    func(b);
}

void test02()
{
    A a;
    B b;
    cout << "sizeof(A):" << sizeof(A) << "sizeof(B):" << sizeof(B) << endl; // 8 16

    a = b;  // B中的a的值并不会赋给A中的a的值，地址都不一样
    cout << a.a << endl;        // 10
    printf("a.getc:%f\n", a.getc());   // 12.1
    printf("b.getc:%f\n", b.getc());   // 12.1

}

void test03()
{
    A a;
    C c;

    a = c;  // 赋值兼容
    cout << a.a << endl;    // 1000
}

int main()
{
    // test01();
    // test02();
    test03();

    return 0;
}
#include <iostream>

using namespace std;

class A
{
public:

    int a = 10;
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
    cout << b.c << endl;
    cout << b.A::c << endl;

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

    a = b;  // B中的a的值并不会赋给A中的a的值，地址都不一样
    cout << a.a << endl;
}

void test03()
{
    A a;
    C c;

    a = c;
    cout << a.a << endl;
}

int main()
{
    // test01();
    // test02();
    test03();

    return 0;
}
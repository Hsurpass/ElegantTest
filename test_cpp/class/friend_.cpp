#include <iostream>

using namespace std;

class A {
    // friend 不具有传递性
    friend class C;
public:
    A() : m_a(10){}

    int m_x = 11;
private:
    int m_a;
};

class B : public A {
public:
    B() : m_b(100) {}

private:
    int m_b;
};

class C {
public:
    // 声明为谁的友元就可以通过谁的对象访问谁的私有成员。
    int f(const A& a) { return a.m_a; }
    // friend 不具有传递性
    // int f1(const B& b) { return b.m_b; }
    int f1(const B& b) { return b.m_a; }

};

class D : private A {
public:
    using  A::m_x;
    // using A::m_a;
};

void test01()
{
    A a;
    B b;
    C c;

    cout << c.f(a) << endl;
    cout << c.f1(b) << endl;
}

void test02()
{
    D d;
    cout << d.m_x << endl;
}

int main()
{
    // test01();
    test02();

    return 0;
}
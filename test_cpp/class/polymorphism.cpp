#include <iostream>

using namespace std;

class A
{
public:
    virtual void func()
    {
        cout << "A::func(), this:" << this << endl;
        func1();
    }
    virtual void func1() { cout << "A::func1(), this:" << this << endl; }
    void func2()
    {
        cout << "A::func2(), this:" << this << endl;
        func1();
    }
    void func3()
    {
        cout << "A::func3(), this:" << this << endl;
        func();
    }

    void func10() { cout << "A::func10(), this:" << this << endl; }
    void func4()
    {
        cout << "A::func4(), this:" << this << endl;
        func10();
    }
};

class B : public A
{
public:
    virtual void func()
    {
        cout << "B::func(), this:" << this << endl;
        func1();
    }
    virtual void func1() { cout << "B::func1(), this:" << this << endl; }
    void func10() { cout << "B::func10(), this:" << this << endl; }
};

class C : public B
{
public:
    virtual void func()
    {
        cout << "C::func(), this:" << this << endl;
        func1();
    }
    virtual void func1() { cout << "C::func1(), this:" << this << endl; }
};

// 虚表 虚表 虚表
void test01()
{
    A *pa = new A;
    cout << "pa:" << pa << endl;
    pa->func(); // "A::func(), this:"   "A::func1(), this:"
    delete pa;

    pa = new B;
    cout << "pa:" << pa << endl;
    pa->func(); // "B::func(), this:"   "B::func1(), this:"
    delete pa;

    pa = new C;
    cout << "pa:" << pa << endl;
    pa->func(); // "C::func(), this:"   "C::func1(), this:"
    delete pa;
}

void test02()
{
    A *pa = new A;
    cout << "pa:" << pa << endl;
    pa->func(); // "A::func(), this:"   "A::func1(), this:"
    delete pa;
    cout << "----------------------------" << endl;

    pa = new B;
    cout << "pa:" << pa << endl;
    pa->func(); // "B::func(), this:"   "B::func1(), this:"
    delete pa;
    cout << "----------------------------" << endl;

    pa = new C;
    cout << "pa:" << pa << endl;
    pa->func(); // "C::func(), this:"   "C::func1(), this:"
    delete pa;
}

void test03()
{
    A *pa = new A;
    cout << "pa:" << pa << endl;
    pa->func2(); // "A::func2(), this:"   "A::func1(), this:"
    delete pa;
    cout << "----------------------------" << endl;

    pa = new B;
    cout << "pa:" << pa << endl;
    pa->func2(); // "A::func2(), this:"    "B::func1(), this:"
    delete pa;
    cout << "----------------------------" << endl;

    pa = new C;
    cout << "pa:" << pa << endl;
    pa->func2(); // "A::func2(), this:"    "C::func1(), this:"
    delete pa;
}

void test04()
{
    A *pa = new A;
    cout << "pa:" << pa << endl;
    pa->func3(); // "A::func3(), this:" "A::func(), this:"   "A::func1(), this:"
    delete pa;
    cout << "----------------------------" << endl;

    pa = new B;
    cout << "pa:" << pa << endl;
    pa->func3(); // "A::func3(), this:" "B::func(), this:"   "B::func1(), this:"
    delete pa;
    cout << "----------------------------" << endl;

    pa = new C;
    cout << "pa:" << pa << endl;
    pa->func3(); // "A::func3(), this:" "C::func(), this:"   "C::func1(), this:"
    delete pa;
}

void test05()
{
    B b;

    b.func2(); // "A::func2(), this:" "B::func1(), this:"
    cout << "------------------------" << endl;
    b.func3(); // "A::func3(), this:" "B::func(), this:" "B::func1(), this:"
    cout << "------------------------" << endl;

    C *pc = new C();
    pc->func2(); // "A::func2(), this:" "C::func1(), this:"
    cout << "------------------------" << endl;
    pc->func3(); // "A::func3(), this:" "C::func(), this:" "C::func1(), this:"

    delete pc;
}

void test06()
{
    B b;
    b.func4(); // "A::func4(), this:"  "A::func10(), this:"
}

void test07()
{
    class Base
    {
    public:
        Base()
        {
            cout << "Base()" << endl;
        }

        ~Base()
        {
            cout << "~Base()" << endl;
        }
    };

    class Derived : public Base
    {
    public:
        Derived()
        {
            cout << "Derived()" << endl;
        }

        ~Derived()
        {
            cout << "~Derived()" << endl;
        }
    };

    // Base *b1 = new Derived;                   // Base() Derived()
    // delete b1;   // 没有虚析构，子类不会被析构  // ~Base()
    cout << "-------------------------" << endl;
    // Derived d;  // Base() Derived()
    // Base &b2 = d;   // 子类被释放了 ~Derived() ~Base() 栈上对象当当会释放

    Derived *b3 = new Derived; // Base() Derived()
    Base &b4 = *b3;   // 父子类都不会被释放，堆上对象要手动调delete
    delete b3;

}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    test07();

}
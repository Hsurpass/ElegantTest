#include <iostream>

using namespace std;

class A{
public:
    A()
    {
        cout << "A() this:" << this << endl;
    }

    virtual ~A()
    {
        cout << "~A() this:" << this << endl;
    }

    static A* alloc();

    void func() const
    {
        cout << "A::func() this" << this << endl;
    }

    void func1()
    {
        cout << "A::func1()" << endl;
        cout << this->a << endl;
    }

private:
    int a;
};

A* A_alloc();

class B : public A
{
public:
    B()
    {
        cout << "B() this:" << this << endl;
        pd = A_alloc();
    }

    virtual ~B()
    {
        cout << "~B() this:" << this << endl;
        delete pd;
    }

    void func() const
    {
        cout << "B::func() this:" << this << endl;
    }

    void func1()
    {
        cout << "B::func1()" << endl;
        cout << this->b << endl;
    }
    
    A* pd;
private:
    int b;
};

class C : public B
{
public:
    C()
    {
        // A();
        // B();
        cout << "C() this:" << this << endl;
    }

    virtual ~C()
    {
        cout << "~C() this:" << this << endl;
    }

    void func() const
    {
        cout << "C::func() this:" << this << endl;
    }

    void func1()
    {
        cout << "C::func1()" << endl;
        cout << this->c << endl;
    }

private:
    int c;
};

class D : public A
{
public:
    D()
    {
        m_pa = this;
        cout << "D() this:" << this << endl;
    }

    virtual ~D()
    {
        cout << "~D() this:" << this << endl;
    }

    static D* alloc();

    void func() const
    {
        cout << "D::func() this:" << this << endl;
    }

    void func1()
    {
        cout << "D::func1()" << endl;
        cout << this->d << endl;
    }

private:
    int d;
    A* m_pa = NULL;
};

D* D::alloc()
{
    D* pd = new D;
    cout << "static D* alloc(), pd:" << pd << endl;

    return pd;
}

A* A::alloc()
{
    A* pa = D::alloc();
    cout << "static A* alloc(), pa:" << pa << endl;

    return pa;
}

A* A_alloc()
{
    cout << "A* A_alloc()" << endl; 
    A* pa = A::alloc();

   return pa;
}

void test01()
{
    C* pc = new C();
    cout << "------------" << endl;
    cout << pc << endl; 

    delete pc;
}

void test02()
{
    C* pc = new C();
    

    delete pc;
}

int main()
{
    test01();
    // test02();

    return 0;
}

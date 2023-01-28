#include <iostream>
#include <memory>

using namespace std;

// 为什么有了shared_ptr.ptr还要有refcount.ptr?
// 1.即使没有虚析构函数也能释放子类内存
// 2.可以把任意shared_ptr对象赋值给shared_ptr<void>，并且不会造成内存泄漏
// 3.多继承情况下，可以把子类的shared_ptr赋值给给任意一个父类的shared_ptr，而不会造成内存泄漏。

class A {
public:
    A() { cout << "A()" << endl; }
    A(const A& other) { cout << "A(const A& other)" << endl; }
    A& operator=(const A& other)
    {
        cout << "A& operator=(const A& other)" << endl;
        if (this == &other)
            return *this;
    }

    ~A() { cout << "~A()" << endl; }

};

class B : public A
{
public:
    B() { cout << "B()" << endl; }
    B(const B& other) { cout << "B(const B& other)" << endl; }
    B& operator=(const B& other)
    {
        cout << "B& operator=(const B& other)" << endl;
        if (this == &other)
            return *this;
    }

    ~B() { cout << "~B()" << endl; }
};

class C {
public:
    C() { cout << "C()" << endl; }
    C(const C& other) { cout << "C(const C& other)" << endl; }
    C& operator=(const C& other)
    {
        cout << "C& operator=(const C& other)" << endl;
        if (this == &other)
            return *this;
    }

    ~C() { cout << "~C()" << endl; }

};

class D : public A, public C
{
public:
    D() { cout << "D()" << endl; }
    D(const D& other) { cout << "D(const D& other)" << endl; }
    D& operator=(const D& other)
    {
        cout << "D& operator=(const D& other)" << endl;
        if (this == &other)
            return *this;
    }

    ~D() { cout << "~D()" << endl; }

};

// 父类的指针指向子类的对象，无需虚析构也可以释放子类资源(没有内存泄漏)
// 原因是refcount.ptr和shared_ptr的指针类型不一样，refcount.ptr指向的是实际类型，且delete也是refcount.ptr.
void test_shared_ptr_without_virtual_destructor()
{
    shared_ptr<B> spb(new B);
    cout << spb.use_count() << endl;    // 1
    
    shared_ptr<A> spa = spb;    // 自动向上转型(up-cast)
    cout << spa.use_count() << endl;    // 2
    cout << spb.use_count() << endl;    // 2

    spb.reset();
    cout << spa.use_count() << endl;    // 1
    cout << spb.use_count() << endl;    // 0

}

void test_shared_ptr_void()
{
    shared_ptr<A> spa(new A);
    cout << spa.use_count() << endl;    // 1

    shared_ptr<void> spv = spa; //A*  向void* 自动转型
    cout << spa.use_count() << endl;    // 2
    cout << spv.use_count() << endl;    // 2

    spa.reset();
    cout << spa.use_count() << endl;    // 0
    cout << spv.use_count() << endl;    // 1
}

void test_shared_ptr_multi_inheritance()
{
    shared_ptr<D> spd(new D);
    cout << spd.use_count() << endl;    // 1

    shared_ptr<A> spa = spd;
    cout << spa.use_count() << endl;    // 2
    cout << spd.use_count() << endl;    // 2

    shared_ptr<C> spc = spd;
    cout << spa.use_count() << endl;    // 3
    cout << spc.use_count() << endl;    // 3
    cout << spd.use_count() << endl;    // 3

    spd.reset();
    cout << spa.use_count() << endl;    // 2
    cout << spc.use_count() << endl;    // 2
    cout << spd.use_count() << endl;    // 0    reset()引用计数减一同时放弃托管
}

int main()
{
    // test_shared_ptr_without_virtual_destructor();
    // test_shared_ptr_void();
    test_shared_ptr_multi_inheritance();

    return 0;
}

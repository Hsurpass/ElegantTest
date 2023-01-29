#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

class A;

class B
{
public:
    B() { cout << "B::B()" << endl; }
    // B(auto arg):m_function(arg) { cout << "B(auto arg):" << endl; }
    B(std::function<void ()> arg):m_function(arg) { cout << "B(std::function<void ()> arg)" << endl; }

    ~B() { cout << "B::~B()" << endl; }

// private:
    std::function<void ()> m_function;
};

class A
{
public:
    A() { cout << "A()" << endl; str = "A::str"; }
    ~A() { cout << "~A()" << endl; }

    void dis() { cout << "A::dis()," << str << endl; }

    shared_ptr<B> getB()
    {
        shared_ptr<B> spb;
        spb.reset(new B(), std::bind(&A::dis, this));

        return spb;
    }

    shared_ptr<B> getB_()
    {
        shared_ptr<B> spb;
        spb.reset(new B(std::bind(&A::dis, this)) );

        return spb;
    }

    string str;
};

class C : public enable_shared_from_this<C>
{
public:
    C() { cout << "C()" << endl; }
    ~C() { cout << "~C()" << endl; }

    void dis() { cout << "C::dis()" << endl; }

    shared_ptr<B> getB()
    {
        shared_ptr<B> spb;
        spb.reset(new B(), std::bind(&C::dis, shared_from_this()));
        cout << "shared_from_this().use_count:" << shared_from_this().use_count() << endl;

        return spb;
    }

    shared_ptr<B> getB_()
    {
        shared_ptr<B> spb;
        spb.reset(new B(std::bind(&C::dis, shared_from_this())) );
        cout << "shared_from_this().use_count:" << shared_from_this().use_count() << endl;

        return spb;
    }
};

void test_bind_this_expired()
{
    A* pa = new A();

    {
        shared_ptr<B> spb = pa->getB();
        delete pa;
        cout << "spb.use_count:" << spb.use_count() << endl;    //1
    }   //Segmentation fault

    // delete pa;

}

void test_bind_shared_from_this()
{
    shared_ptr<C> spc(new C());
    cout << "spc.use_count:" << spc.use_count() << endl;    // 1
    {
        shared_ptr<B> spb = spc->getB();
        cout << "spc.use_count:" << spc.use_count() << endl;    // 2
        cout << "spb.use_count:" << spb.use_count() << endl;    // 1
    }

}

void test_auto_arg()
{
    std::function<void ()> f;
    A* pa = new A();
    f = std::bind(&A::dis, pa);
    B* pb = new B(f);
    pb->m_function();

    delete pa;
    delete pb;
}

void test_bind_this_expired01()
{
    A* pa = new A();

    {
        shared_ptr<B> spb = pa->getB_();
        // delete pa;
        cout << "spb.use_count:" << spb.use_count() << endl;    // 1
        spb->m_function();
    }

    delete pa;
}

void test_bind_shared_from_this01()
{
    shared_ptr<C> spc(new C());
    cout << "spc.use_count:" << spc.use_count() << endl;    // 1
    {
        shared_ptr<B> spb = spc->getB_();
        cout << "spb.use_count:" << spb.use_count() << endl;    // 1
        cout << "spc.use_count:" << spc.use_count() << endl;    // 2
        spb->m_function();
    }
    cout << "spc.use_count:" << spc.use_count() << endl;    // 1
}

int main()
{
    // test_bind_this_expired();
    // test_bind_shared_from_this();

    // test_auto_arg();

    // test_bind_this_expired01();
    test_bind_shared_from_this01();


    return 0;
}
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

class A;

class B
{
public:
    B() { cout << "B::B()" << endl; }
    ~B() { cout << "B::~B()" << endl; }

private:
    std::function<void ()> m_function;
};

class A
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }

    void dis() { cout << "A::dis()" << endl; }

    shared_ptr<B> getB()
    {
        shared_ptr<B> spb;
        spb.reset(new B(), std::bind(&A::dis, this));

        return spb;
    }
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
};

void test_bind_this_expired()
{
    A* pa = new A();

    {
        shared_ptr<B> spb = pa->getB();
        delete pa;
        cout << "spb.use_count:" << spb.use_count() << endl;
    }

    // delete pa;

}

void test_bind_shared_from_this()
{
    shared_ptr<C> spc(new C());
    cout << "spa.use_count:" << spc.use_count() << endl;
    {
        shared_ptr<B> spb = spc->getB();
        cout << "spa.use_count:" << spc.use_count() << endl;
        cout << "spb.use_count:" << spb.use_count() << endl;
    }

}

int main()
{
    // test_bind_this_expired();
    test_bind_shared_from_this();

    return 0;
}
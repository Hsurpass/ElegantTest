#include <iostream>
#include <functional>
#include <list>
using namespace std;

class A
{
public:
    A() {}
    void operator()()
    {
        cout << "class A" << endl;
    }
};

class B
{
public:
    B() {}
    void operator()()
    {
        cout << "class B" << endl;
    }
};

class C
{
public:
    C() {}
    void operator()()
    {
        cout << "class C" << endl;
    }
};

class D
{
public:
    D() {}
    void subcribe(A &a, B &b, C &c)
    {
        functorobj.push_back(a);
        functorobj.push_back(b);
        functorobj.push_back(c);
    }
    void notify()
    {
        for (list<function<void(void)>>::iterator itr = functorobj.begin(); itr != functorobj.end(); ++itr)
        {
            (*itr)();
        }
    }

private:
    list<function<void(void)> > functorobj;
};

void test_listener_with_functional()
{
    A a;
    B b;
    C c;
    D d;
    d.subcribe(a, b, c);    // 订阅

    d.notify(); // 发布
}

int main()
{
    test_listener_with_functional();

    return 0;
}

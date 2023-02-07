#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

// effective c++ 条款43
class A
{
public:
    void func() { cout << "A::func()" << endl; }
};

class B
{
public:
    void func() { cout << "B::func()" << endl; }
};

template<typename T>
class model
{
public:
    void send()
    {
        T x;
        x.func();
    }
};

template<typename U>
class modelImple : public model<U> 
{
    // using model<U>::send;
public:
    void sendTo1()
    {
        // send();
        // this->send();
        model<U>::send();
    }

};

void test_template_base_class()
{
    modelImple<A> ma;
    ma.sendTo1();
    ma.send();

    modelImple<B> mb;
    mb.sendTo1();
    mb.send();
}

int main()
{
    test_template_base_class();

    return 0;
}
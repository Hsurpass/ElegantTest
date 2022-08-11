#include <iostream>

using namespace std;

class Base {
public:
    virtual void f() { cout << "Base::f" << endl; }
    virtual void g() { cout << "Base::g" << endl; }
    virtual void h() { cout << "Base::h" << endl; }
};
class Derive:public Base {
public:
virtual void f() { cout << "Derive::f1" << endl; }
virtual void g2() { cout << "Derive::g1" << endl; }
virtual void h2() { cout << "Derive::h1" << endl; }
};
typedef void(*PF)();
int main()
{
    Derive d;
    cout << "&d:" << &d << endl;
    cout << "vptr:" << (int**)*((int*)&d) << endl;
    cout << "vtable first func:" << *(void**)*((int*)&d) << endl;
    cout << "vtable second func:" << *((void**)*((int*)&d)+1) << endl;
    cout << "vtable third func:" << *((void**)*((int*)&d)+2) << endl;
    cout << "vtable fouth func:" << *((int**)*((int*)&d)+3) << endl;
    cout << "vtable fifth func:" << *((void**)*((int*)&d)+4) << endl;
    cout << "vtable sixth func:" << *((int**)*((int*)&d)+5) << endl;

    PF pf = (PF)(*(void**)*((int*)&d));
    pf();
    pf = (PF)*((void**)*((int*)&d)+1);
    pf();
    pf = (PF)*((void**)*((int*)&d)+2);
    pf();
    pf = (PF)*((void**)*((int*)&d)+3);
    pf();
    pf = (PF)*((void**)*((int*)&d)+4);
    pf();
//    pf = (PF)*((void**)*((int*)&d)+5);
//    pf();
    return 0;
}
int main01()
{
    Base b;
    cout << "&b:" << &b << endl;
    cout << "vptr:" << (int**)*((int*)&b) << endl;
    cout << "vtable first func:" << *(void**)*((int*)&b) << endl;
    cout << "vtable second func:" << *((void**)*((int*)&b)+1) << endl;
    cout << "vtable third func:" << *((void**)*((int*)&b)+2) << endl;
    cout << "vtable fouth func:" << *((int**)*((int*)&b)+3) << endl;

    PF pf = (PF)(*(void**)*((int*)&b));
    pf();
    pf = (PF)*((void**)*((int*)&b)+1);
    pf();
    pf = (PF)*((void**)*((int*)&b)+2);
    pf();
    pf = (PF)*((void**)*((int*)&b)+3);
    pf();
    return 0;
}

#if 0
class A{
public:
    A(){
        //        p = this;
        //        p->func();
    }
    virtual void func(){
        cout<<"aaaaaaaaaaaaaaaa"<<endl;
    }
    ~A(){
        //        p = this;
        //        p->func();
    }
    void foo()
    {
        //        p->func();
        this->func();
    }
private:
    A *p;
};
class B:public A{
public:
    void func(){
        cout<<"bbbbbbbbbbbbbbbbb"<<endl;
    }
};
int main(){
    B b;
    b.foo();
    return 0;
}
#endif

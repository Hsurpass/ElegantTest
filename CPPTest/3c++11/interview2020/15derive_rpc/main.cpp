#include <iostream>

using namespace std;
class A
{
public:
    A() {}
    void fun()
    {
        foo();
    }
    virtual void foo(){cout << "AAAAAAAAAAA" << endl;}
private:

};
class B:public A
{
public:
    B() {}
    void foo()
    {
        cout << "BBBBBBBBBB" << endl;
    }
private:
};
int main()
{
    A *pa = new A;
    pa->fun();
    B* pb = new B;
    pb->fun();
    A* pab = new B;
    pab->fun();

    return 0;
}

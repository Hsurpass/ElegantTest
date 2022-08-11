#include <iostream>

using namespace std;
class A
{
public:
    A() {}
    virtual ~A(){}
};
class B:public A
{
public:
    B() {}
    void dis()
    {
        cout << "B()" << endl;
    }
};
int main()
{
//    A* pa = new B;
//    B* pb = dynamic_cast<B*>(pa);

//    if(pb)
//    {
//        cout << "pb not null" << endl;
//        pb->dis();
//    }
//    else
//    {
//        cout << "pb is null" << endl;
//    }
    B bb;
    A aa;
    A &ya = aa;
    B &yb = dynamic_cast<B&>(ya);
//    B &yb = ya; //invalid
//    if(yb)
    {
        cout << "pb not null" << endl;
        yb.dis();
    }
//    else
    {
        cout << "pb is null" << endl;
    }
    return 0;
}

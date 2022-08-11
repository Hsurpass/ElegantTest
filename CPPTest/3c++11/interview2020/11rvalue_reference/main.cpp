#include <iostream>

using namespace std;
class A
{
public:
    A() {
        cout << "A()" << this << endl;
    }
    ~A()
    {
        cout << "~A()" << this << endl;
    }
    A(const A& another)
    {
        cout << "A(const A& another)" << this << " copy from " << &another<< endl;
    }
    void dis()
    {
        cout << "xxxxxxxxxxxx" << endl;
    }

};
A getObjectA()
{
    return A();
}
void func(A &&a)
{
    cout << "func(A &&a)" <<endl;
    a.dis();
}
void func(const A &a)
{
    cout << "func(const A &a)" <<endl;
//    a.dis();
}
int main01()
{
//    func(A());
    A &&a = getObjectA();
//    A a = getObjectA();
//    const A &a = getObjectA();
    a.dis();
    cout << "a this: " << &a << endl;
    return 0;
}

int main()
{
    /*
    int a = 10;
//    const int& ra = a;
    const double &ra = a;

    cout << "a:" << a << endl;
    cout << "ra:" << ra << endl;

    a = 20;
    cout << "a:" << a << endl;
    cout << "ra:" << ra << endl;
*/
    //r-value-reference
    int a = 100;
//    int && ra = 10;
    double &&ra = a;

    cout << "a:" << a << endl;
    cout << "ra:" << ra << endl;

    a = 20;
    cout << "a:" << a << endl;
    cout << "ra:" << ra << endl;

}

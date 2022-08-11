#include <iostream>
#include <vector>

using namespace std;
class A
{
public:
    A()
    {
        cout<<"A()"<<this<<endl;
    }
    A(int i):_data(i)
    {
        cout<<" A(int i):_data(i)"<<this<<endl;
    }
    A(const A & other)
    {
        cout<<"A(const A & other)"<<this<<" from "<<&other<<endl;
    }
    A& operator=(const A & other)
    {
        cout<<"A& operator=(const A & other)"<<this<<" from "<<&other<<endl;
    }
    ~A()
    {
        cout<<"~A()"<<this<<endl;
    }
private:
    int _data;
};
class B:public A
{
public:
    B() {cout << "B()" <<this << endl;}
    ~B() {cout << "~B()" << this << endl;}
};
int main()
{
    {
        B *pb1 = new B;
//        A *p1 = new A;
        vector<A*> va;
        va.push_back(pb1);
        delete pb1;
//        va.pop_back();
    }
//    vector<A> v;
//    v.push_back(A());
    return 0;
}

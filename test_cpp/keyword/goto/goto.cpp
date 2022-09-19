#include <iostream>

using namespace std;

class A{
public:
    // 注意：和B不同的是有构造和析构函数, 所以编译报错
    A(){}
    ~A(){}
    void testA()
    {
        cout << "A::test." << endl;
    }
};

class B{
public:
    void testB()
    {
        cout << "B::test." << endl;
    }
};

int main()
{
    int a = 10;

    goto err;

    // bool b = true;   // windows ok. linux failed. can not create variable after goto
    // A classA;        // error
    // char *d = "dd";

    B classB;   // ok
   
    {
        double c = 11.11;
    }
    int e;
    e = 200;

    cout << a << endl;
err:
    cout << "err" << endl;
    cout << "-a-:" << a << endl;
    // cout << "c:" << c << endl;
    // cout << "d:" << d << endl;
    cout << "e:" << e << endl;

    // classA.testA();
    classB.testB();

}
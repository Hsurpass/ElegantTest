#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A constructor" << endl;
    }
    ~A()
    {
        cout << "~A destructor" << endl;
    }
};

class B
{
public:
    B()
    {
        cout << "B constructor" << endl;
    }
    ~B()
    {
        cout << "~B destructor" << endl;
    }
};

int divide(int x, int y)
{
    A a;    // A constructor
    A *p = new A;   // A constructor    memory leak
    auto_ptr<A> pa(new A);  // A constructor
    if (y == 0)
        throw('a');
    return x / y;
}

int myDivide(int x, int y)
{
    B b;    // B constructor
    divide(x, y);
}

int main()
{
    try
    {
        myDivide(4, 0);
    }
    catch (int x)
    {
        cout << "x" << endl;
        cout << x << endl;
    }
    catch (double y)
    {
        cout << "y" << endl;
        cout << y << endl;
    }
    catch (...)
    {
        cout << "no x, no y" << endl;
    }
    return 0;
}

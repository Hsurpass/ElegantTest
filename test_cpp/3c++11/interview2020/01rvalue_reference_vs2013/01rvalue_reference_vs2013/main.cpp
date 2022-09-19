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
        cout << "A(const A& another)" << this << " copy from " << &another << endl;
        this->m_data = another.m_data;
    }
    void dis()
    {
        cout << "xxxxxxxxxxxx" << endl;
    }
private:
    int m_data;
};
A getObjectA()
{
    return A();
}

int main()
{
    A a;
    A ra(10);
}
int main01()
{
    A a = getObjectA();
    cout << "a this: " << &a << endl;
    return 0;
}

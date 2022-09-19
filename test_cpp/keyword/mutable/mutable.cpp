#include <iostream>

using namespace std;

class A
{
private:
    mutable int m_a;
    mutable int m_b;
public:
    A(int a, int b):m_a(a), m_b(b){}
    ~A() {}
    void test_mutable(const A& another) const
    {
        m_a = another.m_a;
        m_b = another.m_b;
    }

    void dis()
    {
        cout << m_a << "," << m_b << endl;
    }
};

void test_classMem_mutable()
{
    A a(1, 2);
    A a1(10, 20);
    a.test_mutable(a1);
    a.dis();

}

int main()
{
    test_classMem_mutable();

    return 0;
}
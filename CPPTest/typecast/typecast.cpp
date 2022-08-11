#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int test01()
{
    unsigned char c = -1;
    signed char c1 = 256;
    printf("c:%c\n", c);
    printf("c:%d\n", c);
    cout << "c:" << c << endl;
    cout << "c1:" << c1 << endl;    // undefined
    printf("c1:%c\n", c1);
    printf("c1:%d\n", c1);

    unsigned int u = 10;
    int i = -42;
    cout << i + i << endl;  // -84
    cout << u + i << endl;  // 4294967264

    unsigned int u1 = 42, u2 = 10;
    cout << u1 - u2 << endl;    // 32
    cout << u2 - u1 << endl;    // 4294967264 

    int a = -1;
    unsigned int b = 1;
    cout << "a * b:" << a * b << endl;   // 4294967295
    cout << "a / b:" << a / b << endl;   // 4294967295

    unsigned int u3 = 10;
    int u4 = 10;
    cout << u3 - u4 << endl;
    cout << u4 - u3 << endl;

    return 0;
}

class A

{
private:
    int m_a;
public:
    A(){}
    A(int a):m_a(a){}
    A(double d):m_a(d) {}
    A(char* c)
    {
        m_a = atoi(c);
    }

    ~A(){}

    void dis()
    {
        cout << m_a << endl;
    }
};

// c++ primer 7.5.4
void test02()
{
    A a = 10;
    a.dis();
    A a1 = 12.12;
    a1.dis();
    // A a2 = "a";
    // a2.dis();

}

int main()
{
    // test01();
    test02();

    return 0;
}
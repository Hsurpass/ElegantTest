#include <iostream>
#include <string>

using namespace std;

struct B {
    int b;
    float b1;
    double b2;
    bool b3;
};

class A {
public:
    int m_a;
    float m_b;
    double m_c;
    string m_d;
};

struct POD {
    int a;
    float b;
    double c;

    A a1;
    B bb;
};

void test01()
{
    POD pod;
    cout << pod.a << endl;
    cout << pod.b << endl;
    cout << pod.c << endl;

    cout << "class:" << endl;
    cout << pod.a1.m_a << endl;
    cout << pod.a1.m_b << endl;
    cout << pod.a1.m_c << endl;
    cout << pod.a1.m_d << endl;

    cout << "struct:" << endl;   
    cout << pod.bb.b << endl;
    cout << pod.bb.b1 << endl;
    cout << pod.bb.b2 << endl;
    cout << pod.bb.b3 << endl;

}

int main()
{
    test01();

    return 0;
}
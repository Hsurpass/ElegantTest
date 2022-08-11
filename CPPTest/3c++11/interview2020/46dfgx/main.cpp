#include <iostream>
#include <pthread.h>

using namespace std;
#if 0
class A
{
public:
    A() {
        cout << "A is created" << endl;
        print();
    }
    ~A() {
        cout << "A is deleted" << endl;
    }
    virtual void print()
    {
        cout << "A::print called" << endl;
    }
};
class B :public A
{
public:
    B()
    {
        cout << "B is created" << endl;
        print();
    }
    ~B() {cout << "B is deleted" << endl;}
    virtual void print()
    {
        cout << "B::print called" << endl;
    }
};
int main()
{
    A *pA = new B;
    delete pA;

    return 0;
}
#endif

#if 0
class A
{
public:
    A(int value) {
        m_value = value;
    }
    void print1()
    {
        printf("hello world,print1\n");
    }
    virtual void print2()
    {
        printf("hello world,print2\n");
    }
    void print3()
    {
        printf("%d",m_value);
    }
    ~A(){}
private:
    int m_value;
};
int main()
{
    A *pA = NULL;
    pA->print1();
    pA->print2();
    pA->print3();

    return 0;
}
#endif
#if 0
class A
{
public:
    A():n2(0),n1(n2+2) {}
    void print()
    {
        cout << "n1: " << n1 << "n2:" << n2 << endl;
    }
private:
    int n1;
    int n2;
};

int main()
{
    A a;
    a.print();
    return 0;
}
#endif

#if 0
struct Point3D
{
    int x;
    int y;
    int z;
};

int main()
{
    Point3D *p = NULL;
    cout << (&(p)->x) << endl;
    cout << (&(p)->y) << endl;
    cout << (&(p)->z) << endl;
//    int offset = (int)(&(p)->z);
//    cout << (int)p << endl;
//    cout << "offset: " << offset << endl;
}
#endif

#if 1
int g_variable = 0;
void *adder(void *param)
{
    int count  = 5000;
    int *val = reinterpret_cast<int*>(param);
    while (count--) {
        ++g_variable;
        ++(*val);
    }
}
void *suber(void *param)
{
    int count = 5000;
    int *val = reinterpret_cast<int *>(param);
    while (count--) {
        --g_variable;
        --(*val);
    }
}

int main()
{
    int localval = 0;
    g_variable = 0;

    pthread_t tidadder;
    pthread_t tidsuber;

    pthread_create(&tidadder,NULL,adder,&localval);
    pthread_create(&tidsuber,NULL,suber,&localval);

    pthread_join(tidadder,NULL);
    pthread_join(tidsuber,NULL);

    cout << "lcoal value: " << localval << endl;
    cout << "local value: " << g_variable << endl;
}
#endif



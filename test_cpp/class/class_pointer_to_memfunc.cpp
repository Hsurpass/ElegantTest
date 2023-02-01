#include <iostream>

using namespace std;

class A
{
public:
    int m_a;
    void dis() { cout << "A::dis()" << endl; }

    static int m_b;
    static void dis_static() { cout << "A::dis_static()" << endl; }
};
int A::m_b = 10;

void test_pointer_to_mem()
{
    int A::*pa = &A::m_a;
    void (A::*paf)() = &A::dis;
    int *pb = &A::m_b;
    void (*pbf)() = &A::dis_static;
    // void (A::*pbf_)() = &A::dis_static; // error

    A a;
    cout << a.*pa << endl;
    (a.*paf)();
    cout << *pb << endl;
    pbf();
}

class Widget
{
public:
    Widget()
    {
        pf[0] = &Widget::f;
        pf[1] = &Widget::g;
        pf[2] = &Widget::h;
        pf[3] = &Widget::i;
    }
    int getCount()
    {
        return cnt;
    }
    void select(int val, int sec)
    {
        if (sec < 0 && sec > 3)
            return;
        (this->*pf[sec])(val);
    }

private:
    void f(int val) { cout << "void f()" << val << endl; }
    void g(int val) { cout << "void g()" << val << endl; }
    void h(int val) { cout << "void h()" << val << endl; }
    void i(int val) { cout << "void i()" << val << endl; }
    enum
    {
        cnt = 4
    };
    void (Widget::*pf[4])(int); // 指向类成员函数的指针数组
};

void test_pointer_memfunc_arr()
{
    Widget w;
    w.select(100, 2);
}

int main()
{
    // test_pointer_to_mem();
    test_pointer_memfunc_arr();


    return 0;
}
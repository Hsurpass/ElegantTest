#include <iostream>

using namespace std;
//初始化列表和构造函数效率
//类隐式转换成int double
//map[a] = b;
//shared_ptr unique_ptr weak_ptr
//map迭代器失效
//右值引用
//hash冲突
//shared_ptr 多线程安全
//回文
//call_once
//gdb
//enable_share_from_this
//运行中的程序删除动态库会崩吗
//epoll水平触发和边缘触发的区别
class B
{
public:
    B()
    {cout << "B()" << endl;}
    B(const B& another)
    {cout << "B(const B& another)" << endl;}
    B& operator=(const B&another)
    {
        cout << "B& operator=(const B&another)" << endl;
    }
    ~B()
    {cout << "~B()" << endl;}
};
class A
{
public:
    A(B b):m_b(b)
    {
        cout << "A()" << endl;
//        m_b = b;
    }
    A(const A& another)
    {cout << "A(const A& another)" << endl;}
    A& operator=(const A&another)
    {
        cout << "A& operator=(const A&another)" << endl;
    }
    ~A()
    {cout << "~A()" << endl;}

    int m_a;
    B m_b;
};
int main()
{
//    int a = -1;
//    unsigned int b = a;
//    cout << b << endl;
    B b1;
    cout << "---------------"<< endl;
    A a(b1);

}
int main01()
{
//    unsigned int a = -1;
//    cout << a << endl;

//    void *p = new A();
//    void *p;
//    new(p)A;
//    delete (A*)p;
//    delete p;

//    void *a;
//    A* a = (A*)malloc(sizeof(A));
//    new(a)A;
//    delete a;

//    void *a = NULL;
//    new (a)A;
//    delete a;

//    A*p = new A;
//    p->m_a = 100;
//    void*t = p;
//    delete t;
//    delete (A*)t;
//    cout << p->m_a << endl;

    return 0;
}

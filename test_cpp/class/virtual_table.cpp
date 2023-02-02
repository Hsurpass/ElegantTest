#include <iostream>

using namespace std;

class A{
public:
    A(int x = 10):m_x(x) { cout << "A(int x = 10), this:" << this << endl; }
    virtual ~A() { cout << "~A()" << endl;}   // 虚函数表中有两个虚析构，啥原因？不知道。。。

    virtual int x() const { cout << "A::x(), m_x:" << m_x << endl; return m_x; }
    virtual int y() const { cout << "A::y()" << endl; return 11; }
    virtual int z() const { cout << "A::z()" << endl; return 12; }
    // virtual ~A() { cout << "~A()" << endl;}    

    int m_x;
};

class B : public A
{
public:
    B(int y = 100):m_y(y) { cout << "B(int y = 100), this:" << this << endl; }
    // virtual ~B() { cout << "~B()" << endl;}   // 虚函数表中有两个虚析构，啥原因？不知道。。。

    virtual int y() const { cout << "B::y()" << endl; return m_y; }
    // virtual ~B() { cout << "~B()" << endl;}    

    int m_y;
};

class C : public B
{
public:
    C(int z = 1000):m_z(z) { cout << "C(int z = 1000), this:" << this << endl; }
    // virtual ~C() { cout << "~C()" << endl;}   // 虚函数表中有两个虚析构，啥原因？不知道。。。

    virtual int z() const { cout << "C::z()" << endl; return 112; }
    // virtual ~C() { cout << "~C()" << endl;}    

    int m_z;
};

void test_vtbl(void* vptr)
{
    typedef int(*PF)();
    PF pf = NULL;
    pf = (PF)(*((long long*)vptr + 0));
    cout << "pf:" << pf << endl;
    cout << pf() << endl;

    pf= (PF)(*((long long*)vptr + 1));
    cout << "pf:" << pf << endl;
    cout << pf() << endl;

    pf= (PF)(*((long long*)vptr + 2));
    cout << "pf:" << pf << endl;
    cout << pf() << endl;   

    pf= (PF)(*((long long*)vptr + 3));
    cout << "pf:" << pf << endl;
    cout << pf() << endl;   

    // 虚函数表是个指针数组？想求虚函数个数，不是期望结果
    // long long* p = (long long*)vptr;
    // int count;
    // while (*p)
    // {
    //     ++count;
    //     ++p; 
    // }
    // cout << "count:" << count << endl;
    
}

void test_A_vtable()
{
    // 调用虚函数，编译器内部转换成：(*objPtr->vptr[0])(objPtr)
    A *pa = new A();
    cout << "pa:" << pa << endl;
    cout << "&m_x:" << &pa->m_x << endl;
    cout << "m_x:" << pa->m_x << endl;      // 10
    cout << "&m_x:" << (long long*)pa+1 << endl;
    cout << "m_x:" << *(int*)((long long*)pa+1) << endl;    // 10

    void* vptr = (void*)(*((long long*)pa+0));  // 64位是long long*，32位是int*
    cout << "vptr:" << vptr << endl;
    cout << "vptr:" << (int*)(*((long long*)pa+0)) << endl;

    test_vtbl(vptr);

    delete pa;
}

void test_B_vtable()
{
    B *pb = new B();
    cout << "pb:" << pb << endl;

    void* vptr = (void*)(*((long long*)pb+0));  // 64位是long long*，32位是int*
    cout << "vptr:" << vptr << endl;
    cout << "vptr:" << (int*)(*((long long*)pb+0)) << endl;
    cout << "-------------------------" << endl;
    test_vtbl(vptr);

    delete pb;
}

void test_C_vtable()
{
    C *pc = new C();
    cout << "pc:" << pc << endl;

    void* vptr = (void*)(*((long long*)pc+0));  // 64位是long long*，32位是int*
    cout << "vptr:" << vptr << endl;
    cout << "vptr:" << (int*)(*((long long*)pc+0)) << endl;
    cout << "-------------------------" << endl;
    test_vtbl(vptr);

    delete pc;
}

int main()
{
    // test_A_vtable(); // A::x() A::y() B::z()
    // test_B_vtable(); // A::x() B::y() A::z()
    test_C_vtable();    // A::x() B::y() C::z()

    return 0;
}
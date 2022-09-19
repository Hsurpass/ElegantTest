#include <iostream>

using namespace std;

class A
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }

    void func() const
    {
        cout << "A::func()" << endl;
    }

    void func1()
    {
        cout << "A::func1()" << endl;
        cout << this->a << endl;
    }

private:
    int a;
};

void test01()
{
    A a;
    a.func();
    a.func1();

    // 空指针调用成员函数，只要不访问数据成员就不会崩溃（崩溃原因：没有this指针啊）。
    A *pa = NULL;
    pa->func();
    // pa->func1();
}

void test02()
{
    // 非const对象既可以调用非const成员函数，又可以调用const成员函数。
    A a;
    a.func();
    a.func1();

    // const对象只能调用const成员函数。
    const A a1 = a;
    a1.func();
    // a1.func1();  // error

    // 同上
    const A& a2 = a;
    a2.func();
    // a2.func1();

}

void test_temporary_obj_destroy()
{
    A().func();
}

int main()
{
    // test01();
    // test02();
    test_temporary_obj_destroy();
    
    return 0;

}
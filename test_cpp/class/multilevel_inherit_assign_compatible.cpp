#include <iostream>

using namespace std;

class A
{
public:
    A(int a_=10, float c_=10.10):a(a_), c(c_) {}
    int a;
    float getc() { return c; }    // 父类是看不到子类成员的，所以即使同名也始终访问的是父类成员。
protected:
    float c;
};

class B : public A
{
public:
    B(int aa, float cc):a(aa),c(cc), A(aa, cc){}
    int a;
    float getc() { return c; }
private:
    float c;
};

class C : public A
{
public:
    C()
    {
        this->a = 1000;
    }
};

// 赋值完成后父类对象就可以直接访问子类对象的父类部分。
void test_assign_compatibility()
{
    A a;
    B b(20, 20.20);
    cout << "a.a:" << a.a << endl;          // 10
    cout << "a.getc():" << a.getc() << endl;// 10.10
    cout << "b.a:" << b.a << endl;          // 20
    cout << "b.getc():" << b.getc() << endl;// 20.20

    cout << "----------------" << endl;
    cout << "子类对象可以直接赋值给父类对象:" << endl;
    a = b;
    cout << "a.a:" << a.a << endl;          // 20
    cout << "a.getc():" << a.getc() << endl;// 20.20
    cout << "b.a:" << b.a << endl;          // 20
    cout << "b.getc():" << b.getc() << endl;// 20.20
    cout << "----------------" << endl;
    A a1 = b;
    cout << "a1.a:" << a.a << endl;          // 20
    cout << "a1.getc():" << a.getc() << endl;// 20.20
    cout << "b.a:" << b.a << endl;           // 20.20
    cout << "b.getc():" << b.getc() << endl; // 20.20

    cout << "子类对象可以直接赋值给父类对象的引用:" << endl;
    A &a2 = b;
    cout << "a2.a:" << a2.a << endl;          // 20
    cout << "a2.getc():" << a2.getc() << endl;// 20.20
    cout << "b.a:" << b.a << endl;            // 20
    cout << "b.getc():" << b.getc() << endl;  // 20.20
    cout << "----------------" << endl;
    A& a3 = a;
    a3 = b;
    cout << "a3.a:" << a3.a << endl;          // 20
    cout << "a3.getc():" << a3.getc() << endl;// 20.20
    cout << "b.a:" << b.a << endl;            // 20
    cout << "b.getc():" << b.getc() << endl;  // 20.20

    cout << "子类对象的地址可以直接赋值给父类对象的地址:" << endl;
    A* a4 = &b;
    cout << "a4.a:" << a4->a << endl;          // 20
    cout << "a4.getc():" << a4->getc() << endl;// 20.20
    cout << "b.a:" << b.a << endl;            // 20
    cout << "b.getc():" << b.getc() << endl;  // 20.20
    cout << "----------------" << endl;
    A* a5 = &a;
    B* b1 = &b;
    a5 = b1;
    cout << "a5.a:" << a5->a << endl;          // 20
    cout << "a5.getc():" << a5->getc() << endl;// 20.20
    cout << "b.a:" << b.a << endl;            // 20
    cout << "b.getc():" << b.getc() << endl;  // 20.20
}


int main()
{
    test_assign_compatibility();

    return 0;
}

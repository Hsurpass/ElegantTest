#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A(), this:" << this << endl;
        // effective c++ 条款09: 绝不要在构造和析构函数中调用虚函数. 在base class 构造期间，virtual函数不是virtual函数(vtable还没创建好)
        this->func1();  // A::func1(), this:
    }

    void name() { cout << "A::name()" << endl; }

    virtual void func1() { cout << "A::func1(), this:" << this << endl; };
    virtual A *func2()
    {
        cout << "A::func2() this: " << this << endl;
        return this;
    };
    virtual void func3(int a = 10) { cout << "A::func3() this: " << this << ", a:" << a << endl; func1(); };

    virtual void infiniteRecursion() { cout << "A::infiniteRecursion()" << endl; }

    virtual ~A()
    {
        cout << "~A()" << endl;
    }
};

class B : public A
{
public:
    B()
    {
        cout << "B(), this:" << this << endl;
        this->func1();  // B::func1(), this:
    }

    void func1() override { cout << "B::func1(), this:" << this << endl; }
    void func1(int a) { cout << a << endl; }

    // c++ primer 15.3 当类的虚函数返回类型是类本身的引用或指针时，函数返回类型不用严格匹配。
    virtual B *func2()
    {
        cout << "B::func2() this: " << this << endl;
        return this;
    };
    // c++ primer 15.3 虚函数与默认实参。 对于虚函数如果某次函数调用使用了默认实参，则该实参值由本次调用的静态类型决定。
    // 也就是说，如果我们通过基类的引用或指针调用函数，则使用基类中定义的默认实参。
    virtual void func3(int a = 20) override { cout << "B::func3() this: " << this << ", a:" << a << endl; A::func1(); };

    // 如果在派生类中的虚函数中需要调用它的基类版本，但是没有使用作用域运算符，则在运行时该调用将被解析为对派生类版本自身的调用。
    virtual void infiniteRecursion()
    {
        cout << "B::infiniteRecursion()" << endl;
        this->A::infiniteRecursion();

        // 如果在派生类中的虚函数中需要调用它的基类版本，但是没有使用作用域运算符，则在运行时该调用将被解析为对派生类版本自身的调用。
        // this->infiniteRecursion();
    }

    virtual void test() {}

    virtual ~B()
    // ~B()
    {
        cout << "~B()" << endl;
    }
};

// https://blog.csdn.net/F_cff/article/details/79690470
class C
{
public:
    C()
    {
        cout << "C()" << endl;
    }
    virtual ~C()
    {
        cout << "~C()" << endl;
    }
};


void test_virtual_function()
{
    A *pa = new B();
    pa->func3();

    delete pa;
}

void test_class_sizeof()
{
    C c;
    C c1;
    C c2;

    cout << sizeof(C) << endl;
}

// https://www.zhihu.com/question/432986565
// https://zhuanlan.zhihu.com/p/75553222
void test_smartPtr_with_virtualDestructor()
{
    {
        // A a;
        // B b;
        // cout << "---------------------" << endl;
    }
    {
        // A* p1 = new A();
        // B* p2 = new B();
        // p1 = p2;

        // A *pa = new B();
        // delete pa;
    }
    cout << "---------------------" << endl;
    {
        std::shared_ptr<A> upa = make_shared<B>(); // 析构时,会析构子类
        // std::unique_ptr<A> upa = make_unique<B>();  // 没有虚析构，析构时，并不会析构子类(memory leak)
    }
    cout << "---------------------" << endl;
    // upa->func1();
}

void test06()
{
    B b;

    A *pa = &b;
    pa->name();
}

// 如果在派生类中的虚函数中需要调用它的基类版本，但是没有使用作用域运算符，则在运行时该调用将被解析为对派生类版本自身的调用。从而造成无限递归。error!!!!!!!!
void test05()
{
    B b;

    b.infiniteRecursion(); // B::infiniteRecursion()
                           // A::infiniteRecursion()
    cout << "----------------------" << endl;
    A *pa = &b;
    cout << "pa:" << pa << endl;
    cout << "&b:" << &b << endl;
    pa->infiniteRecursion(); // B::infiniteRecursion()
                             // A::infiniteRecursion()
}

// c++ primer 15.3 回避虚函数的机制。 不进行动态绑定， 强制执行虚函数的某个特定版本
void test04()
{
    A a; // A::func1()
    B b; // A::func1()
         // B::func1()
    cout << "----------------------" << endl;
    A *pa = new B; // A::func1()
                   // B::func1()

    cout << "----------------------" << endl;
    pa->A::func1(); // A::func1()   不进行动态绑定， 强制执行虚函数的某个特定版本

    cout << "----------------------" << endl;

    b.A::func1(); // A::func1()  不进行动态绑定，强制执行虚函数的某个特定版本
}

// c++ primer 15.3 虚函数与默认实参。 对于虚函数如果某次函数调用使用了默认实参，则该实参值由本次调用的静态类型决定。
// 也就是说，如果我们通过基类的引用或指针调用函数，则使用基类中定义的默认实参。
void test03()
{
    A a;
    B b;
    A *pa = &b;

    pa->func3();    //B::func3() this: , a:10  A::func1(),
    a.func3();      //A::func3() this: , a:10  A::func1()
    b.func3();      //B::func3() this: , a:20  A::func1(),  //不是多态
}

// c++ primer 15.3 当类的虚函数返回类型是类本身的引用或指针时，函数返回类型不用严格匹配。
void test02()
{
    A a;
    B b;
    A *pa = &b;

    cout << pa->func2() << endl;    //B::func2() this:
    cout << a.func2() << endl;      //A::func2() this:
    cout << b.func2() << endl;      //B::func2() this:
}

void test01()
{
    A a; // A() A::func1()
    B b; // A() A::func1() B() B::func1()
    A *pa = &b; // 多态
    a = b;      // 上转

    pa->func1(); // B::func1()
    a.func1();   // A::func1()
    b.func1();   // B::func1()
    b.func1(1);  // 1

    cout << "&a" << &a << endl;
    cout << "&b" << &b << endl;
    cout << "pa" << pa << endl;

    return;
}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    // test_smartPtr_with_virtualDestructor();
    // test_class_sizeof();
    test_virtual_function();

    return 0;
}
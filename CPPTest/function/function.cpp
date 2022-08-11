#include <iostream>
#include <vector>
#include <string>

#include "../basicClass/A.h"

using namespace std;

// c++ primer6.4 函数重载
/*不能构成重载*/
// void func3(int, int)
// {
//     cout << "void func3(int, int)" << endl;
// }
// void func3(const int, const int)
// {
//     cout << "void func3(const int, const int)" << endl;
// }

// void func1(A a)
// {
//     cout << "void func1(A a)" << endl;
//     a.print();
// }
// void func1(const A a)
// {
//     cout << "void func2(const A a)" << endl;
//     a.print();
// }

// 只有const 引用或指针才能构成重载
void func2(A& a)
{
    cout << "void func1(A& a)" << endl;
    a.print();
}
void func2(const A& a)
{
    cout << "void func2(const A& a)" << endl;
    a.print();
}

void test01()
{
    A a1(100);
    // func1(a);
    func2(a1);
    // func3(10,11);
}

// c++ primer 6.7节练习
int add(int x, int y) { return x + y;}
int sub(int x, int y) { return x - y;}
int multi(int x, int y) { return x * y;}
int division(int x, int y) { return x / y;}

// typedef int _func(int, int);     //_func 是函数类型
// typedef decltype(add) _func;     //同上等价，_func 是函数类型

// typedef int (*p_func)(int, int); // p_func 是指向函数的指针
// typedef decltype(add) *p_func;       // 同上等价，p_func 是指向函数的指针

// using _func = int(int, int);   // _func 是函数类型，不是指针。
using p_func = int(*)(int, int);   // p_func 是指向函数类型的指针。

void test02()
{
    // vector<_func*> vpf;
    vector<p_func> vpf;

    vpf.push_back(add);
    vpf.push_back(sub);
    vpf.push_back(multi);
    vpf.push_back(division);

    for (size_t i = 0; i < vpf.size(); i++)
    {
        cout << vpf[i](10, 10) << endl;
    }
    
}

bool funcbool()
{}

void test03()
{
    bool val = funcbool();

    printf("val:%d, true:%d, false:%d\n", val, true, false);
    cout << boolalpha;
    cout << "val:" << val << endl;
    cout << true << "," << false << endl;
}

int main()
{
    // test01();
    // test02();
    test03();

    return 0;
}
#include <iostream>
#include "example.h"

using namespace std;

// c++ primer 7.6
class Account
{
private:
    std::string owner;
    double amount;
// public:
    static double interestRate;
    static double initRate();
public:
    // 静态成员既属于类也属于对象
    // 在类内，成员函数不用通过作用域运算符就能访问静态成员
    void calculate() { amount += amount * interestRate;}
    int rate1();

    static double rate();
    static void rate(double newRate);
};

// 在类外，成员函数可以(也可以不)通过作用域运算符访问静态成员，
// 但必须定义静态成员(与定义的先后顺序无关)
int Account::rate1()
{
    return interestRate;
}

// 在类外，成员函数可以(也可以不)通过作用域运算符访问静态成员，
// 但必须定义静态成员(与定义的先后顺序无关)
double Account::rate()
{
    return interestRate;
}

double Account::initRate()
{
    return 0;
}

// initRate()确实可以不加类名，但使用前必须定义,private也没关系。
// c++ primer:
// 从类名开始，这条`定义`语句的剩余部分就都位于`类的作用域`之内了。所以我们可以直接使用initRate函数。
// double Account::interestRate = initRate();
double Account::interestRate = 100;

// 在类外，成员函数可以(也可以不)通过作用域运算符访问静态成员，
// 但必须定义静态成员(与定义的先后顺序无关)
void Account::rate(double newRate)
{
    interestRate = newRate;
}

void test01()
{
    Account acc;
}

void test02()
{
    test01();

    cout << Account::rate() << endl;

}

// c++ primer 7.6 静态成员可以是不完全类型
class Bar
{
private:
    static Bar m1; //静态成员可以是不完全类型
    Bar* m2;       //指针成员可以是不完全类型
    // Bar m3;     // 数据成员必须是完全类型
    // Bar& m4 = m1;  // 引用成员必须是完全类型
    Bar& m4 = *m2;
    // Bar& m5; // 引用必须初始化

public:
    Bar() {};
    ~Bar() {};
};

void test03()
{
    Bar bar;
}

// c++ primer 练习7.58
void test04()
{
    cout << "test04" << endl;
    Example ex;

    static const int size = 10;
    vector<int> v(size);    
}

void loopCall()
{
    static int a = 0;
    cout << "a: " << a << endl;

    a++;

    cout << "a: " << a << endl;
}

void test05()
{
    loopCall();

    loopCall();

    loopCall();

}

int main()
{
    // test01();
    // test02();
    // cout << Account::rate() << endl;

    // test03();
    // test04();
    test05();

    return 0;
}
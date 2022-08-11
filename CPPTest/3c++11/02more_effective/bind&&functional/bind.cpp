#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

struct MyPair
{
public:
    double a;
// private:
    int b;
};

void test_bind_classMemVar()
{
    MyPair mp{10, 20};

    auto f1 = bind(&MyPair::a, &mp);
    cout << f1() << endl;   // 10

    // 不可bind私有成员变量
    auto f2 = bind(&MyPair::b, mp);
    cout << f2() << endl;   // 20
}

int add(int x)
{
    cout << "int add(int x)" << endl;
    return x;
}

int add(int x, int y)
{
    cout << "int add(int x, int y)" << endl;
    return x + y;
}
double add(double x, double y)
{
    cout << "double add(double x, double y)" << endl;
    return x + y;
}

class MyPair3
{
public:
    int add(int x, int y)
    {
        cout << "MyPair:: int add(int x, int y)" << endl;
        return x + y;
    }
    double add(double x, double y)
    {
        cout << "double add(double x, double y)" << endl;
        return x + y;
    }
};

void test_bind_placeholders()
{
    // bind normal-function 
    auto f1 = bind((int (*)(int))add, _1);
    cout << f1(1) << endl;
    auto f2 = bind((int (*)(int, int))add, _1, _2);
    cout << f2(2.0, 3.0) << endl;
    auto f3 = bind((double (*)(double, double))add, _1, _2);
    cout << f3(4.0, 5.0) << endl;

    // bind class-member-function
    MyPair3 mp3;
    auto f4 = bind( (int (MyPair3::*)(int, int))&MyPair3::add, _1, _2, _3);
    cout << f4(mp3, 10, 20) << endl;

    auto f5 = bind((double (MyPair3::*)(double, double))&MyPair3::add, _1, _2, _3);
    cout << f5(&mp3, 30, 20) << endl;
}

class MyPair2
{
public:
    int add(int x, int y)
    {
        return x + y;
    }

    double myDivide(double x, double y)
    {
        return x / y;
    }
};

void test_bind_classMemFun_placeholders()
{
    MyPair2 mp2;
    
    // 类成员函数必须要加&
    auto f2 = bind(&MyPair2::add, &mp2, _1, _2);
    cout << f2(3, 4) << endl;

    std::function<int(int, int)> f22 = std::bind(&MyPair2::add, &mp2, _1, _2);
    cout << f22(4, 5) << endl;
    
    std::function<double(double)> f222 = std::bind(&MyPair2::myDivide, &mp2, _1, 10);
    cout << f222(2) << endl;    // 0.2

    std::function<double(double)> f2222 = std::bind(&MyPair2::myDivide, &mp2, 10, _1);
    cout << f2222(2) << endl;    // 5

    auto f3 = bind(&MyPair2::add, _1, _2, _3);
    cout << f3(mp2, 4, 5) << endl;
}

double myDivide(double x, double y)
{
    return x / y;
}

void test_reverse_placeholders()
{
    // 两个参数 returns int x/y
    auto fn_rounding = std::bind<int>(myDivide, placeholders::_1, _2);
    cout << fn_rounding(10, 2) << endl; // 5
    
    // 反转参数 returns y/x
    auto fn_invert = std::bind(myDivide, _2, _1);
    cout << fn_invert(10, 2) << endl;   // 0.2 --> 2放到_2, 1放到_1
}

int main()
{
    // test_bind_placeholders();
    test_bind_classMemFun_placeholders();
    // test_reverse_placeholders();
    // test_bind_classMemVar();

    return 0;
}

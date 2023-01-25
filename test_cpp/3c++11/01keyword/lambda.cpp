#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void smallestLambda()
{
    auto foo = []
    { return 1 + 2; };
    cout << foo() << endl;
    cout << []
    { return 3 + 4; }()
         << endl;
}

void smallerLambda()
{
    auto func = [](int x = 1, int y = 2)
    { return x + y; };
    cout << func() << endl;
    cout << [](int x, int y)
    { return x + y; }(5, 6)
         << endl;
}

void smallLambda()
{
    auto f = [](int x = 1, int y = 2) -> int
    { return x + y; };
    cout << f() << endl;
    cout << [](int x, int y) -> int
    { return x + y; }(4, 6) << endl;
}

void lambdaMutable()
{
    int x = 22, y = 33;

    {
        int x = 10, y = 100;
        // x = 10, y = 100;
        cout << "main1:" << x << "," << y << endl; // 10 100
#if 0
        auto func = [=]() mutable {  // 值传递要有mutable
            x = 20;
            y = 200;

            cout << "lambda:" << x << "," << y << endl;
        };

        auto foo = [=]() mutable { // 值传递要有mutable
            x = 30;
            y = 300;

            cout << "lambda:" << x << "," << y << endl;
        };
        func(); // 20 200
        foo();  // 30 300

        cout << "main1:" << x << "," << y << endl; // 10 100
#endif
#if 1
        auto func = [&]() { // 引用传递可以没有mutable
            x = 20;
            y = 200;

            cout << "lambda:" << x << "," << y << endl;
        };

        auto foo = [&]() { // 引用传递可以没有mutable
            x = 30;
            y = 300;

            cout << "lambda:" << x << "," << y << endl;
        };
        func(); // 20 200
        foo();  // 30 300

        cout << "main1:" << x << "," << y << endl; // 30 300
#endif
    }
    cout << "main:" << x << "," << y << endl; // 22 33
}

/****************************** closure **********************************/
auto adder()
{
    auto sum = 0;
    return [=](int value) mutable {
        sum += value;
        return sum;
    };
}

void accumulate()
{
    auto f = adder();
    for (int i = 0; i < 5; i++)
    {
        cout << f(i) << " ";    // 0 1 3 6 10
    }
    cout << endl;
}

auto fibonacii()
{
    auto a = 0, b = 1, t = 0;
    return [=]() mutable {
        t = a;
        a = b;
        b = t + b;

        return a;
    };
}

void fibonacii_sequence()
{
    auto f = fibonacii();
    for (size_t i = 0; i < 5; i++)
    {
        cout << f() << " ";
    }
    cout << endl;
}

/****************************** closure **********************************/

void func(int i)
{
    cout << i << " ";
}

void test_foreach_with_lambda()
{
    list<int> li;
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        li.push_back(rand() % 100);
    }

    // for_each(li.begin(), li.end(), func);

    for_each(li.begin(), li.end(), [](int i)
             { cout << i << " "; });
    cout << endl;
}

void test_std_sort_with_lambda()
{
    vector<int> v;
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        v.push_back(rand() % 100);
    }
    for_each(v.begin(), v.end(), [](int i)
             { cout << i << " "; });
    cout << endl;
    cout << "----------------------------" << endl;

    std::sort(v.begin(), v.end(), [](int x, int y)
              { return x < y; });

    for_each(v.begin(), v.end(), [](int i)
             { cout << i << " "; });
    cout << endl;
}

template <typename FUNC>
void printUseFunc(FUNC func, int a, int b, int c)
{
    func(a, b, c);
}

void test_lambda_template()
{
    printUseFunc([](int a, int b, int c)
                 { cout << "a:" << a << ",b:" << b << ",c:" << c << endl; },
                 10, 20, 30);
}

int g_a = 1;
void test_lambda_capture()
{
    int a = 100;
    static int b = 2;
    // 全局变量和静态局部变量直接访问，不用捕获和传参
    auto f = []()
    {
        cout << "g_a:" << g_a << endl;
        cout << "b:" << b << endl;
        // cout << "a:" << a << endl;
    };

    f();
}

// from 现代c++核心特性解析7.2.2
// 值捕获的变量在lambda表达式定义的时候就已经固定下来了，无论在表达式定义之后如何修改外部变量的值，lambda捕获的值都不会变化。
void test_lambda_cpature_value()
{
    int x = 5, y = 8;

    auto f = [x, &y]() mutable
    {
        x += 1;
        y += 1;
        cout << "x:" << x << ",y:" << y << endl; // x:6, y=101
    };
    // f();
    x = 10;
    y = 100;
    f();
}

// from 现代c++核心特性解析7.2.3
// 捕获this指针，可以在lambda内部使用this类型的成员函数和变量
class A
{
public:
    A(int x = 10) {}

    void print() { cout << "A::print(), x:" << x << endl; }

    void test_capture_this()
    {
        auto f = [this]()
        {
            print();
        };
        x = 5;
        f();
    }

private:
    int x;
};

int main()
{
    // smallestLambda();
    // smallerLambda();
    // smallLambda();
    // lambdaMutable();

    // closure
    accumulate();
    // fibonacii_sequence();

    // test_foreach_with_lambda();
    // test_std_sort_with_lambda();
    // test_lambda_template();

    // test_lambda_capture();

    // A a;
    // a.test_capture_this();
    // test_lambda_cpature_value();
}
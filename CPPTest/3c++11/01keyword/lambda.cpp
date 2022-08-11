#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void smallestLambda()
{
    auto foo = [] { return 1 + 2; };
    cout << foo() << endl;
    cout << [] { return 3 + 4; }() << endl;
}

void smallerLambda()
{
    auto func = [](int x = 1, int y = 2) { return x + y; };
    cout << func() << endl;
    cout << [](int x, int y) { return x + y; }(5, 6) << endl;
}

void smallLambda()
{
    auto f = [](int x = 1, int y = 2) -> int { return x + y; };
    cout << f() << endl;
    cout << [](int x, int y) -> int { return x + y; }(4, 6) << endl;
}

/****************************** closure **********************************/
void lambdaMutable()
{
    int x = 22, y = 33;

    {
        int x = 10, y = 100;
        // x = 10, y = 100;
        cout << "main1:" << x << "," << y << endl;  // 10 100
#if 0
        auto func = [=]()mutable {  // 值传递要有mutable
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
        auto func = [&]() {  // 引用传递可以没有mutable
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

auto adder()
{
    auto sum = 0;
    return [=](int value)mutable{
        sum += value;
        return sum;
    };
}

void accumulate()
{
    auto f = adder();
    for (int i = 0; i < 5; i++)
    {
        cout << f(i) << " ";
    }
    cout << endl;
}

auto fibonacii(){
    auto a = 0, b = 1, t=0;
    return [=]()mutable{
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
    for(int i=0; i <10; i++)
    {
        li.push_back(rand()%100);
    }

    // for_each(li.begin(), li.end(), func);

    for_each(li.begin(), li.end(), [](int i){
        cout << i << " ";
    });
    cout << endl;
}

void test_std_sort_with_lambda()
{
    vector<int> v;
    srand(time(NULL));
    for(int i = 0;i < 10;i++)
    {
        v.push_back(rand() % 100);
    }
    for_each(v.begin(), v.end(), [](int i){
        cout << i << " ";
    });
    cout << endl;
    cout << "----------------------------" << endl;

    std::sort(v.begin(), v.end(), [](int x, int y){
        return x < y;
    });

    for_each(v.begin(), v.end(), [](int i){
        cout << i << " ";
    });
    cout << endl;
}

template<typename FUNC>
void printUseFunc(FUNC func, int a, int b, int c)
{
    func(a, b, c);
}

void test_lambda_template()
{
    printUseFunc([](int a, int b, int c){
        cout << "a:" << a << ",b:" << b << ",c:" << c << endl;
    }, 10, 20, 30);
}

int main()
{
    // smallestLambda();
    // smallerLambda();
    // smallLambda();
    // lambdaMutable();

    // closure
    // accumulate();
    // fibonacii_sequence();

    // test_foreach_with_lambda();
    // test_std_sort_with_lambda();
    test_lambda_template();
}
#include <iostream>
#include <vector>

using namespace std;

// const int Example::vecSize;

class Example
{
public:
    // static double rate = 6.5;   // 静态成员不能在类内初始化
    static double rate;
    static const int vecSize = 20;
    int arr[vecSize];   // true
    static vector<double> vec;
    // static vector<double> vec(Example::vecSize); // false 这种写法vec就变成函数了
};


// -Wall: 大部分警告
// -Wextra: 一些额外的警告
// -Werror: 当出现警告时转为错误，停止编译
//  -Wno-unused-parameter: 函数中出现未使用的参数，不给出警告

#include <iostream>

using namespace std;
// g++ -Wall -Wextra -Werror compiler_options.cpp
// void test_Wall()
// {
//     int a;
// }

// g++ -Wconversion compiler_options.cpp 一些可能改变值的隐式转换，给出警告
void test_Wconversion()
{
    double a = 2.3;
    int b;
    b = a;
    // cout << b << endl;
}

int main()
{
    // test_Wall();
    test_Wconversion();

    return 0;
}
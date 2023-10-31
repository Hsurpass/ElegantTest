#include <iostream>

using namespace std;

// constexpr关键字可以将运行的计算提前到编译时来做。
constexpr int get_value(int a, int b)
{
    return a + b;
}

void test_constexpr()
{
    int arr[get_value(1, 2)] = {0};
    cout << "arr size: " << sizeof(arr) / sizeof(int) << endl;
}

int main()
{
    test_constexpr();

    return 0;
}
#include <iostream>

#include "inline_test.h"

using namespace std;

inline void func(int a, int b)
{
    cout << (a + b) << endl;
}
constexpr int func_(int a, int b)
{
    return (a - b);
}

void test_inline()
{
    func(10, 10);
}


int main()
{
    test_inline();
    int a = func_(20, 10);
    cout << a << endl;

    return 0;
}
#include <iostream>

using namespace std;

void test_constexpr01(int n)
{
    // int a = 10;
    // int a = sizeof(int);
    int a = n > 10 ? 1 : 2;

    int arr[a] = { 0 };
    cout << sizeof(arr)/sizeof(arr[0]) << endl;
}

int main()
{
    test_constexpr01(2);

    return 0;
}
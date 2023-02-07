#include <vector>
#include <iostream>
using namespace std;

// 函数模板泛化
template <typename T, class U>
void compare(T num1, U num2)
{
    cout << "standard function template" << endl;
    if (num1 > num2)
        cout << "num1:" << num1 << " > num2:" << num2 << endl;
    else
        cout << "num1:" << num1 << " <= num2:" << num2 << endl;
}

// 对部分模板参数进行偏特化
template <class U>
void compare(int num1, U num2)
{
    cout << "compare(int num1, U num2)" << endl;
    if (num1 > num2)
        cout << "num1:" << num1 << " > num2:" << num2 << endl;
    else
        cout << "num1:" << num1 << " <= num2:" << num2 << endl;
}

// 将模板参数偏特化为指针
template <typename T, class U>
void compare(T *num1, U *num2)
{
    cout << "compare(T *num1, U *num2)" << endl;
    if (*num1 > *num2)
        cout << "num1:" << *num1 << " > num2:" << *num2 << endl;
    else
        cout << "num1:" << *num1 << " <= num2:" << *num2 << endl;
}

// 将模板参数偏特化为另一个模板类
template <typename T, class U>
void compare(std::vector<T> &vecLeft, std::vector<U> &vecRight)
{
    cout << "compare(std::vector<T> &vecLeft, std::vector<U> &vecRight)" << endl;
    if (vecLeft.size() > vecRight.size())
        cout << "vecLeft.size()" << vecLeft.size() << " > vecRight.size():" << vecRight.size() << endl;
    else
        cout << "vecLeft.size()" << vecLeft.size() << " <= vecRight.size():" << vecRight.size() << endl;
}

int main()
{
    compare<int, int>(30, 31); // 调用泛化版本compare<int,int>(int num1, int num2)

    compare(30, '1'); // 调用偏特化版本compare<char>(int num1, char num2)

    int a = 30;
    char c = '1';
    compare(&a, &c); // 调用偏特化版本compare<int,char>(int* num1, char* num2)

    vector<int> vecLeft{0};
    vector<int> vecRight{1, 2, 3};
    compare<int, int>(vecLeft, vecRight); // 调用偏特化版本compare<int,char>(int* num1, char* num2)
}
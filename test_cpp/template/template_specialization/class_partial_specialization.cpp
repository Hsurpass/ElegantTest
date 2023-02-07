#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

// 类模板泛化
template <typename T, class U>
class Compare
{
public:
    void compare(T num1, U num2)
    {
        cout << "standard function template" << endl;
        if (num1 > num2)
            cout << "num1:" << num1 << " > num2:" << num2 << endl;
        else
            cout << "num1:" << num1 << " <= num2:" << num2 << endl;
    }
};

// 类模板全特化
template <>
class Compare<const char*, const char*>
{
public:
    void compare(const char* num1, const char* num2)
    {
        cout << "全特化" << endl;
        if (strcmp(num1, num2) > 0)
            cout << "num1:" << num1 << " > num2:" << num2 << endl;
        else
            cout << "num1:" << num1 << " < num2:" << num2 << endl;
    }
};

// 对部分模板参数进行偏特化
template <class U>
class Compare<int, U>
{
public:
    void compare(int num1, U num2)
    {
        cout << "compare(int num1, U num2)" << endl;
        if (num1 > num2)
            cout << "num1:" << num1 << " > num2:" << num2 << endl;
        else
            cout << "num1:" << num1 << " <= num2:" << num2 << endl;
    }
};

// 将模板参数偏特化为指针
template <typename T, class U>
class Compare<T*, U*>
{
public:
    void compare(T *num1, U *num2)
    {
        cout << "compare(T *num1, U *num2)" << endl;
        if (*num1 > *num2)
            cout << "num1:" << *num1 << " > num2:" << *num2 << endl;
        else
            cout << "num1:" << *num1 << " <= num2:" << *num2 << endl;
    }
};

// 将模板参数偏特化为另一个模板类
template <typename T, class U>
class Compare<std::vector<T>, std::vector<U>>
{
public:
    void compare(std::vector<T> &vecLeft, std::vector<U> &vecRight)
    {
        cout << "compare(std::vector<T> &vecLeft, std::vector<U> &vecRight)" << endl;
        if (vecLeft.size() > vecRight.size())
            cout << "vecLeft.size()" << vecLeft.size() << " > vecRight.size():" << vecRight.size() << endl;
        else
            cout << "vecLeft.size()" << vecLeft.size() << " <= vecRight.size():" << vecRight.size() << endl;
    }
};

int main()
{
    Compare<int, int> c;
    c.compare(30, 31); // 调用泛化版本compare<int,int>(int num1, int num2)

    Compare<const char*, const char*> cc;
    cc.compare("china", "hello"); // 调用泛化版本compare<const char*,const char*>(int num1, int num2)

    Compare<int, char> c1;
    c1.compare(30, '1'); // 调用偏特化版本compare<char>(int num1, char num2)

    int a = 30;
    char ch = 'c';
    Compare<int*, char*> c2;
    c2.compare(&a, &ch); // 调用偏特化版本compare<int,char>(int* num1, char* num2)

    vector<int> vecLeft{0};
    vector<int> vecRight{1, 2, 3};
    Compare<vector<int>, vector<int>> c3;
    c3.compare(vecLeft, vecRight); // 调用偏特化版本compare<int,char>(int* num1, char* num2)
    return 0;
}
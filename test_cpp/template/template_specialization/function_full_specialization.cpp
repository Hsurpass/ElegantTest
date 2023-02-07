#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

// 函数泛化
template<typename T>
T Max(T _x, T _y)   // Max不能和系统重名
{
    cout << "T max(T _x, T _y)" << endl;
    return _x > _y ? _x : _y;
}

// 函数全特化
template<>
// const char* Max<const char*>(const char* _x, const char* _y)
const char* Max(const char* _x, const char* _y)
{
    cout << "const char* max(const char* _x, const char* _y)" << endl;
    return (strcmp(_x, _y) > 0) ?  _x : _y;
}

void test_function_full_specialization()
{
    string s1("hello"), s2("world");

    cout << Max(10,5) << endl;
    cout << Max(s1, s2) << endl;
    cout << Max<const char* >("hello", "world") << endl;  // full specialization

}

int main()
{
    test_function_full_specialization();

    return 0;
}
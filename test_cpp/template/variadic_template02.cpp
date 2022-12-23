#include <iostream>
#include <string>

using namespace std;

template<typename... T>
void test_call_func(const T&... val)
{
    
}

template<typename T>
T getElement(const T& val)
{
    return val;
}

template<typename T>
void printOneElement(const T& val)
{
    cout << val << " ";
}

template<typename... ARGS>
void printVar(const ARGS&... args)
{
    // test_call_func(getElement(args)...);

    // 非递归方法遍历元素:
    //使用展开函数处理参数
    std::initializer_list<int>{ (printOneElement(args), 0)... };
    cout << endl;

    //  使用lambda
    std::initializer_list<int>{
        ([&] { cout << args << " "; }(), 0)...
    };
    cout << endl;
}

int main()
{
    printVar(1,2,3, "abc", true, 'd');

    return 0;
}
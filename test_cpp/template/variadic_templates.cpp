#include <iostream>
#include <bitset>

using namespace std;

// 最后一次需要特殊处理，否则编译不过
void print()
{
    cout << "void print()" << endl;
}

template <typename T, typename... U>
void print(const T& firstArg, const U&... otherArgs)
{
    cout << firstArg << ", sizeof(otherArgs): " << sizeof...(otherArgs) << endl;
    print(otherArgs...);
}

// 可以和上面的模板共存
template <typename... T>
void print(const T&... args)
{
    cout << "print(const T&... args), sizeof...(args)" << sizeof...(args) << endl;
}

int main()
{
    // 7.5, sizeof(otherArgs): 3
    // hello, sizeof(otherArgs): 2
    // 0000000101111001, sizeof(otherArgs): 1
    // 42, sizeof(otherArgs): 0
    // void print()
    print(7.5, "hello", bitset<16>(377), 42);

    cout << "-----------------------------" << endl;
    //20, sizeof(otherArgs): 1
    //40, sizeof(otherArgs): 0
    print<int>(20, 40);

    return 0;
}
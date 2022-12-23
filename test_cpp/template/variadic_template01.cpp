#include <iostream>
#include <bitset>
#include <unistd.h>
#include <string>

using namespace std;


/*
T... 称之为包扩展(pack extension)，包扩展是可以传递的。比如继承的时候，或者直接在函数参数里面传递。
然后当编译器进行推导的时候，就会对这个包扩展进行展开，上面的例子，T...就展开成了int, char。
C++11定义了可以展开包的几个地方：

1. 表达式
2. 初始化列表
3. 基类描述列表
4. 类成员初始化列表
5. 模板参数列表
6. 通用属性列表
7. lamda函数的捕捉列表
其他地方是不能展开的。
*/

#if 1
// 最后一次需要特殊处理，否则编译不过
void print()
{
    cout << "void print()" << endl;
}

template <typename T, typename... U>
void print(const T& firstArg, const U&... otherArgs)
{
    cout << "void print(const T& firstArg, const U&... otherArgs)" << endl;
    cout << firstArg << ", 类型参数的个数:" << sizeof...(U) 
                     << ", 函数参数的个数: " << sizeof...(otherArgs) << endl;
    print(otherArgs...);
}
#endif

// void print(ostream& os)
// {
//     os << "print(ostream& os)" << endl;
// }

template <typename T>
void print(ostream& os, const T& firstArg)  // 和上述版本同时存在时，优先调用这个
{
    os << "print(ostream& os, const T& firstArg)" << endl;
    os << firstArg <<endl;
}

template <typename T, typename... U>
void print(ostream& os, const T& firstArg, const U&... otherArgs)
{
    sleep(1);

    os << "print(ostream& os, const T& firstArg, const U&... otherArgs)" << endl;
    os << "firstArg: "<< firstArg
         << ", 类型参数的个数:" << sizeof...(U) 
         << ", 函数参数的个数: " << sizeof...(otherArgs) << endl;

    print(os, otherArgs...);
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
    print(cout, 7.5, "hello", bitset<16>(377), 42);

    cout << "-----------------------------" << endl;
    //20, sizeof(otherArgs): 1
    //40, sizeof(otherArgs): 0
    print<int>(20, 40);

    return 0;
}
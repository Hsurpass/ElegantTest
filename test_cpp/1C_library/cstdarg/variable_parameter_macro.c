#include <stdarg.h>
#include <stdio.h>

// 宏定义的参数允许用"...", 表示是可变参数，在宏替换的时候用__VA_ARGS__表示"..."位置的所有参数
#define test1(...) printf(__VA_ARGS__)
#define test2(fmt, ...) printf(fmt, __VA_ARGS__)

// 很多编译器扩展了可变参数的宏替换，这样的写法更容易记忆，
// 宏定义的参数后面可以带三个小数点，表示这里是可变参数，
// 宏替换的时候，直接写这个参数就表示这个位置是所有的可变参数了。
// 注：某些编译器需要用 ##args 表示 args... 位置所有的参数的宏替换。
#define test3(fmt...) printf(fmt)
#define test4(fmt, args...) printf(fmt, args)


void test_variable_parameter_macro()
{
    int i = 10;
    float f = 12.23;
    const char* str = "hello";
    // test1(str);
    test1("test1, i:%d, f:%f, str:%s\n", i, f, str);
    test2("test2, i:%d, f:%f, str:%s\n", i, f, str);
    test3("test3, i:%d, f:%f, str:%s\n", i, f, str);
    test4("test4, i:%d, f:%f, str:%s\n", i, f, str);

}

int main()
{
    test_variable_parameter_macro();

    return 0;
}
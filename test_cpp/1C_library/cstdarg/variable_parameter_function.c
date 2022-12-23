#include <stdarg.h>
#include <stdio.h>


/*
"..." 表示这个位置可以有多个参数，参数的类型和个数不是固定的。
va_start： 用来初始化 va_list 参数表
    void va_start (va_list ap, paramN);
第一个参数 ap 为要初始化的参数表，第二个参数 paramN 是函数参数当中最后一个固定的参数，也就是 "..." 前面的那个参数。
由此推断，可变参数的函数至少要有一个固定的参数，在 "..." 的前面。

va_arg: 是从 va_list 参数表里面读取出来一个参数，并且指向下一个参数，这样每调用一次 va_arg 就按顺序读取出来一个参数。
    type va_arg (va_list ap, type);
type 为变量类型，例如 int, double 或 char * 等。类型作为函数的参数很显然不属于 C 语言的标准语法，这是编译器内部执行的一个功能。

va_end: 释放 va_start 初始化参数表占用的资源。在 va_start 之后，当初始化的参数表使用完之后，必须调用 va_end，否则可能会出现程序执行异常。
    void va_end (va_list ap);
*/
void test_va_list(int n, ...)
{
    va_list vl;
    va_start(vl, n);
    
    for (int i = 0; i < n; i++)
    {
        printf("val:%f\n", va_arg(vl, double));
    }
    va_end(vl);
    
    va_end(vl);
}

int main()
{
    test_va_list(4, 2.1, 3.1, 4.1, "abc");

    return 0;
}
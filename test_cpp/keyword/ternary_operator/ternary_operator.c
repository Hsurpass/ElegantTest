#include <stdio.h>

int main()
{
    int a = 10;
    int b = 20;
    
    // a < b ? a : b = 100;    // error C语言返回的是变量值, 不能作为左值
    printf("ret=%d\n", a);  

    // (a < b ? a : b) = 100;
    // printf("ret=%d\n", a);  // error C语言返回的是变量值, 不能作为左值
}
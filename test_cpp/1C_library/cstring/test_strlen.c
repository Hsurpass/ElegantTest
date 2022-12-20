#include <stdio.h>
#include <string.h>

void test_strlen()
{
    char*p = "hello";

    int len = strlen(p);    // 不包含末尾的'\0'

    printf("len:%d\n", len);
}

int main()
{
    test_strlen();

    return 0;
}
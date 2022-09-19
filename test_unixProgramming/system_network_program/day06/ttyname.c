#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void test_ttyname01()
{
    printf("fd 0:%s\n", ttyname(0));
    printf("fd 1:%s\n", ttyname(1));
    printf("fd 2:%s\n", ttyname(2));
}

int main()
{
   test_ttyname01();

    return 0;
}
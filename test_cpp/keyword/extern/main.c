/***main.c****/
#include <stdio.h>
#include "max.c"    // 都include了，我觉得extern没什么用

/*定义两个全局变量*/
// g_X=10;
// g_Y=20;
// int g_X=10;
// int g_Y=20;
int max();

int main(void)
{
    int result;
    result = max();
    printf("the max value is %d\n",result);
    
    return 0;
}
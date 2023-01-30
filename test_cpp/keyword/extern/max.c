/****max.c****/
#include <stdio.h>
/*外部变量声明*/    // 只是声明，定义在外部定义
extern int g_X ;
extern int g_Y ;

int max()
{
    return (g_X > g_Y ? g_X : g_Y);
}
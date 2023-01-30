#include <stdio.h>

int max(int x, int y);

/*
全局变量 g_X 与 g_Y 是在 main 函数之后声明的，因此它的作用范围不在 main 函数中。
如果我们需要在 main 函数中调用它们，就必须使用 extern 来对变量 g_X 与 g_Y 作“外部变量声明”，以扩展全局变量的作用域。
也就是说，如果在变量定义之前要使用该变量，则应在使用之前加 extern 声明变量，使作用域扩展到从声明开始到本文件结束。
*/
int main(void)
{
	int result;
	/*外部变量声明*/
	extern int g_X;
	extern int g_Y;
	result = max(g_X, g_Y);
	printf("the max value is %d\n", result);
	return 0;
}

/*定义两个全局变量*/
int g_X = 10;
int g_Y = 20;
int max(int x, int y)
{
	return (x > y ? x : y);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char* str)
{
    char* p = str;
    int len = strlen(str);
    int i = 0, j = len -1;
    while(i < j)
    {
        char t = p[i];
        p[i] = p[j];
        p[j] = t;

        i++;
        j--;
    }

}

int main()
{
    char* p = "hello";
    // *p = 'c';   // 字符串常量不可被改变
    // reverseString(p);
    printf("%s\n", p);  

    return 0;
}
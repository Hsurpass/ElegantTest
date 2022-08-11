#include <stdio.h>


void copy_string(char *from,char *to)
{
    while (*to++ = *from++);
}
int main()
{
    char p1[1024] = "Hello World!\n";
    char p2[1024] = "nba";
    copy_string(p1,p2);
    printf("%s\n",p1);

    return 0;
}

//int main()
//{
//    printf("hello world\n");
//}

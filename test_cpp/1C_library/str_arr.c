#include <stdio.h>
#include <string.h>

void test_str_pointer_and_arr()
{
    // "abc" 都是存储在常量区的，不能修改
    char* p1 = "abc";
    const char* p2 = "abcd";
    // *p1 = 'v';
    // *p2 = 'g';

    char p3[] = "abc";
    printf("p3:%s\n", p3);
    p3[1] = 'm';
    printf("p3:%s\n", p3);

    const char p4[] = "def";
    printf("p4:%s\n", p4);
    // p4[1] = 'n'; // const 不可修改
    printf("p4:%s\n", p4);

}

char* func(char* t)
{
    char* p = t;
    return (p + strlen(p)/2);
}

void test_str_pointer()
{
    char* str = " abcdefghi";
    str = func(str);
    puts(str);  //efghi
}

void test_yu()
{
    int x = 98765;
    int count=0;
    while(x)
    {
        x = x&(x-1);
        ++count;
    }
    printf("count:%d, x:%d\n", count, x);   // 8 0
    
    int i = 0;
    printf("i:%d\n", i++);  // 0
    printf("i:%d\n", i);  // 1

    i = 5;
    if(i-- < 5)
    {
        printf("i:%d\n", i);
    }
    else
    {
        printf("i:%d\n", i++);  // 4
    }
}

int main()
{
    // test_str_pointer_and_arr();
    // test_str_pointer();
    test_yu();
}
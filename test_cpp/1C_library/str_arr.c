#include <stdio.h>

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

int main()
{
    test_str_pointer_and_arr();

}
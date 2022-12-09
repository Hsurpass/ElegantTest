#include <stdio.h>

// void test_no_volatie()
// {
//     int i = 0;
//     int a = i;
//     printf("i=%d\n", a);

//     // 下面汇编语句的作用就是改变内存中i的值
//     // 但是又不让编译期知道
//     __asm { mov dword ptr [ebp-4], 20h }

//     int b = i;
//     printf("i = %d\n", b);

// }

int main()
{
    // test_no_volatie();

    volatile int a = 1;
    int b =2;
    b = a;
    // a = b;
    
    printf("a:%d, b:%d\n", a, b);
    

    return 0;
}
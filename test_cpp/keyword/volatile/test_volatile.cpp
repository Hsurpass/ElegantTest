#include <iostream>
#include <chrono>
#include <stdio.h>

using namespace std;

// g++ volatile.cpp -O2
// 默认是O0,不优化的
void test_delay()
{
    const auto start = std::chrono::system_clock::now();
    // int i = INT32_MAX;
    volatile int i = INT32_MAX;

    while (--i){}
    
    cout << std::chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() << endl;
}

// void test_no_volatie()
// {
//     int i = 0;
//     int a = i;
//     printf("i=%d\n", a);

//     // 下面汇编语句的作用就是改变内存中i的值
//     // 但是又不让编译期知道
//     __asm ("mov dword ptr[ebp - 4], 20h");

//     int b = i;
//     printf("i = %d\n", b);

// }

int main()
{
    // test_no_volatie();
    test_delay();
    

    return 0;
}
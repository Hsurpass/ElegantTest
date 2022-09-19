#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// gdb attach pid 会阻塞住当前进程， continue 继续运行
void test_gdb_attach()
{
    int count = 0;

    while (1)
    {
        printf("[test_gdb_attach] pid:%d, count:%d\n", getpid(), count++);
        sleep(2);
    }
    
}

int main()
{
    test_gdb_attach();

    return 0;
}
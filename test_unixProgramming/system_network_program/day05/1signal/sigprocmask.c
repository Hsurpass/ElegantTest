#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void print_signalset(sigset_t *sig_mask)
{
    int i = 0;
    for(i = 1; i < 32; i++)
    {
        if (sigismember(sig_mask, i) == 1)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    putchar(10);
}

void test01()
{
    sigset_t mask_set, pending_mask;
    sigemptyset(&pending_mask);
    sigemptyset(&mask_set);
    sigaddset(&mask_set, SIGINT);   // 把信号集中的SIGINT的位置为1
    // sigaddset(&mask_set,SIGQUIT);

    // 设置信号屏蔽字   信号屏蔽字可以由用户设置和获取
    sigprocmask(SIG_BLOCK, &mask_set, NULL);

    int count = 0;
    while (1)
    {
        sigpending(&pending_mask);  // 获取未决信号集，未决信号集只能由内核来修改
        print_signalset(&pending_mask); // 打印一下

        if (count++ == 10) // 循环10次后，信号屏蔽字恢复原状
        {
            sigprocmask(SIG_UNBLOCK, &mask_set, NULL);
        }
        
        sleep(1);
    }
    

    while (1)
    {
        sleep(1);
    }

}

int main()
{
    // printf("%ld\n", sizeof(sigset_t));

    test01();
    
    return 0;
}
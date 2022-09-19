#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void test_alarm01()
{
    alarm(5);

    while (1)
    {   
        printf("hello world\n");
        sleep(1);
    }
}

void sighandle(int sig)
{
    printf("sighandle:%d\n", sig);
    alarm(5);   // 每隔5秒触发SIGALRM信号
}

void test_alarm02()
{
    signal(SIGALRM, sighandle);
    alarm(5);

    while (1)
    {   
        printf("hello world\n");
        sleep(1);
    }
}

int main()
{
    // test_alarm01();
    test_alarm02();
    
    return 0;
}
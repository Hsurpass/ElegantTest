#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

void sig_handle(int sig)
{
    static int i = 0;
    printf("alarm[%d], sig=%d\n", i++, sig);

}

void test_setitimer()
{
    signal(SIGALRM, sig_handle);
    struct itimerval timer;
    // 每隔多少秒发送一次信号
    // timer.it_interval.tv_sec = 1;
    // timer.it_interval.tv_usec = 0;  // 微秒
    timer.it_interval.tv_usec = 500000;    //半秒

    // 第一次定时时间
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    
    int ret = setitimer(ITIMER_REAL, &timer, NULL);
    if (ret == -1)
    {
        perror("setitimer");
    }

#if 0
    while (1)
    {
        printf("helloworld\n");
        sleep(1);
    }
#endif

#if 1
    while(1)
    {
        int sig = pause();
        printf("end pause, sig = %d\n", sig);
    }
#endif
}

int main()
{
    test_setitimer();
    
    return 0;
}
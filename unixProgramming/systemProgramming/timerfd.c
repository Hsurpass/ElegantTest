#include <unistd.h>
#include <sys/prctl.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <stdint.h>

/*
reference:
    https://www.jianshu.com/p/cf98f7f55962
    https://zhuanlan.zhihu.com/p/40572954

*/

void test_timerfd()
{
    struct timeval now; 
    gettimeofday(&now, NULL);
     // 第一次超时时间
     struct itimerspec new_value;
    new_value.it_value.tv_sec = now.tv_sec + 5;
    // new_value.it_value.tv_nsec = now.tv_usec * 1000000;
    // 设置超时间隔
    new_value.it_interval.tv_sec = 3;
    new_value.it_interval.tv_nsec = 0;
    // 创建 timerfd
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    // 设置第一次超时时间和超时间隔
    if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1){}
    // 定时器循环
    int s;
    uint64_t exp;
    for (int tot_exp = 0; tot_exp < 10; tot_exp++) 
    {
        // read timerfd，获取到超时次数
        s = read(fd, &exp, sizeof(uint64_t));
        // 累计总超时次数
        tot_exp += exp;
        // 打印超时次数的信息
        printf("read: %llu; total=%llu\n", (unsigned long long) exp, (unsigned long long) tot_exp);
    }
}

int main()
{
    test_timerfd();

    return 0;
}
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// https://jingyan.baidu.com/article/cbcede07eae5c243f50b4d28.html


void test_clock_gettime()
{
    struct timespec time1 = {0};

    // 获取从1970/1/1 0:0:0 到现在的时间
    clock_gettime(CLOCK_REALTIME, &time1);
    printf("CLOCK_REALTIME: (%lu, %lu)\n", time1.tv_sec, time1.tv_nsec);

    // 从系统启动到当前的时间
    clock_gettime(CLOCK_MONOTONIC, &time1);
    printf("CLOCK_REALTIME: (%lu, %lu)\n", time1.tv_sec, time1.tv_nsec);

    // 当前进程在CPU所消耗的时间
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    printf("CLOCK_REALTIME: (%lu, %lu)\n", time1.tv_sec, time1.tv_nsec);

    // 当前线程在CPU0所消耗的时间
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);
    printf("CLOCK_REALTIME: (%lu, %lu)\n", time1.tv_sec, time1.tv_nsec);

    // 当前时间
    printf("now time :%lu\n", time(NULL));
}

int main()
{
    test_clock_gettime();
    
    return 0;
}

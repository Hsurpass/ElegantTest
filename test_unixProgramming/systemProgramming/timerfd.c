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
#include <inttypes.h>
#include <errno.h>

/*
reference:
    https://blog.csdn.net/yusiguyuan/article/details/22936707
    https://www.jianshu.com/p/cf98f7f55962
    https://zhuanlan.zhihu.com/p/40572954

*/

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

static void print_elapsed_time(void)
{
    static struct timespec start;
    struct timespec curr;
    static int first_call = 1;
    int secs, nsecs;

    if (first_call)
    {
        first_call = 0;
        if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
            handle_error("clock_gettime");
    }

    if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
        handle_error("clock_gettime");

    secs  = curr.tv_sec - start.tv_sec;
    nsecs = curr.tv_nsec - start.tv_nsec;
    if (nsecs < 0)
    {
        secs--;
        nsecs += 1000000000;
    }
    printf("%d.%03d: ", secs, (nsecs + 500000) / 1000000);
}

int test_timerfd_CLOCK_REALTIME(struct itimerspec* new_value, int arriveTime)
{
    struct timespec now;
    if (clock_gettime(CLOCK_REALTIME, &now) == -1)
        handle_error("clock_gettime");

    /* Create a CLOCK_REALTIME absolute timer with initial
       expiration and interval as specified in command line. */

    new_value->it_value.tv_sec  = now.tv_sec + arriveTime;
    new_value->it_value.tv_nsec = now.tv_nsec;

    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if (fd == -1)
        handle_error("timerfd_create");

    if (timerfd_settime(fd, TFD_TIMER_ABSTIME, new_value, NULL) == -1)
        handle_error("timerfd_settime");
    
    return fd;
}

int test_timerfd_CLOCK_MONOTONIC(struct itimerspec* new_value, int arriveTime)
{

    /* Create a CLOCK_MONOTONIC relative timer with initial
       expiration and interval as specified in command line. */

    new_value->it_value.tv_sec  = arriveTime;
    new_value->it_value.tv_nsec = 0;

    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd == -1)
        handle_error("timerfd_create");

    if (timerfd_settime(fd, 0, new_value, NULL) == -1)
        handle_error("timerfd_settime");
    
    return fd;
}

// ./a.out 第一次到期时间 间隔时间 循环read次数
// ./a.out 3 1 5
// it_value被设置了就是周期性定时器
int main(int argc, char* argv[])
{
    struct itimerspec new_value;
    int max_exp, fd;
    uint64_t exp, tot_exp;
    ssize_t s;

    if ((argc != 2) && (argc != 4))
    {
        fprintf(stderr, "%s init-secs [interval-secs max-exp]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        new_value.it_interval.tv_sec = 0;
        max_exp                      = 1;
    }
    else
    {
        new_value.it_interval.tv_sec = atoi(argv[2]);   // 间隔时间
        max_exp                      = atoi(argv[3]);
    }
    new_value.it_interval.tv_nsec = 0;

#if 1
    fd = test_timerfd_CLOCK_REALTIME(&new_value, atoi(argv[1]));
#endif
#if 0
    fd = test_timerfd_CLOCK_MONOTONIC(&new_value, atoi(argv[1]));
#endif
    print_elapsed_time();
    printf("timer started\n");

    for (tot_exp = 0; tot_exp < max_exp;)
    {
        s = read(fd, &exp, sizeof(uint64_t));
        // print_elapsed_time();
        // printf("read: %" PRIu64 "; total=%" PRIu64 "\n", exp, tot_exp);
        if (s != sizeof(uint64_t))
            handle_error("read");

        tot_exp += exp;
        print_elapsed_time();
        printf("read: %" PRIu64 "; total=%" PRIu64 "\n", exp, tot_exp);

        if (tot_exp == 3)   // 循环3次，停止定时器
        {
            memset(&new_value, 0, sizeof(new_value));
            int r;
#if 1
            r = timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL);
#endif
#if 0     
            r = timerfd_settime(fd, 0, &new_value, NULL);
#endif
            if (r == -1)
            {    
                printf("stop timer, r=%d\n", r);
                perror("timerfd_settime");
                handle_error("timerfd_settime"); 
            }
            else
            {
                printf("stop timer, r=%d\n", r);
                perror("timerfd_settime");
                handle_error("timerfd_settime"); 
            }
        }
    }

    exit(EXIT_SUCCESS); // 退出当前进程，回收定时器。
}


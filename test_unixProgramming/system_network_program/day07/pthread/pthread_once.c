// once_run()函数仅执行一次，且究竟在哪个线程中执行是不定的，尽管pthread_once(&once,once_run)出现在两个线程中。
// 如果在一个线程初始化的时候，另外一个线程也调用了pthread_once，则调用线程将阻塞等待，直到那个线程完成初始化后返回。
// Linux Threads 使用互斥锁和条件变量保证由pthread_once()指定的函数执行且仅执行一次，而once_control则表征是否执行过。
// 如果 once_control的初值不是PTHREAD_ONCE_INIT（LinuxThreads定义为0），pthread_once()的行为就会不正常。
// 在LinuxThreads中，实际"一次性函数"的执行状态有三种：NEVER（0）、IN_PROGRESS（1）、DONE（2），
// 如果 once初值设为1，则由于所有pthread_once()都必须等待其中一个激发"已执行一次"信号，因此所有pthread_once()都会陷入永久的等待中；
// 如果设为2，则表示该函数已执行过一次，从而所有pthread_once()都会立即返回0。

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

// pthread_once_t once = PTHREAD_ONCE_INIT;
// pthread_once_t once = 1;
pthread_once_t once = 2;

void init()
{
    printf("I'm in thread id = %lx, LWP:%ld\n", pthread_self(), syscall(SYS_gettid));
}

void* task1(void* arg)
{
    printf("task1: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
    int ret = pthread_once(&once, init);
    printf("task1, ret=%d, once=%d\n", ret, once);
}

void* task2(void* arg)
{
    printf("task2: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
    int ret = pthread_once(&once, init);
    printf("task2, ret=%d, once=%d\n", ret, once);
}

void* task3(void* arg)
{
    printf("task3: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
    int ret = pthread_once(&once, init);
    printf("task3, ret=%d, once=%d\n", ret, once);
}

void test_pthread_once()
{
    pthread_t threadID1, threadID2, threadID3;
    pthread_create(&threadID1, NULL, task1, NULL);
    pthread_create(&threadID2, NULL, task2, NULL);
    pthread_create(&threadID3, NULL, task3, NULL);
    
    pthread_join(threadID1, NULL);
    pthread_join(threadID2, NULL);
    pthread_join(threadID3, NULL);
}

int main()
{
    test_pthread_once();

    return 0;
}
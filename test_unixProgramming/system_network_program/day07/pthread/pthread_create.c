// #define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* mythread(void *arg)
{
    int i = 0;
    int *pa = (int *)malloc(4);
    *pa = 222;
    
    while (++i <= 10)
    {
        printf("child thread: tid = %lx, arg = %ld\n", pthread_self(), (long)arg);
        // printf("child thread: tid = %lx, tid: %d, arg = %ld\n", pthread_self(), gettid(), (long)arg);
        sleep(1);
    }

    // 线程的退出方式一种是return， 一种是调用pthread_exit()
    #if 0
    return 0;
    // return (void*)i;    // 栈变量不能作为返回值
    // return (void*)111;
    return (void*)pa;   //如果返回的是指针，pthread_join的时候应该对其解引用
    #endif

    #if 1
    pthread_exit((void*)333);
    #endif
}

void test_pthread_create()
{
    pthread_t tid;
    int ret = 0;
    ret = pthread_create(&tid, NULL, &mythread, (void*)10);
    if (ret != 0)
    {
        printf("pthread_create error:%s\n", strerror(ret));
        exit(0);
    }

    #if 0
    int* result;
    pthread_join(tid, (void**)&result);
    printf("result:%d\n", *result);
    #endif

    #if 1
    void *result;
    pthread_join(tid, &result);
    printf("result:%ld\n", (long)(result) );
    #endif

    int i = 0;
    while (1)
    // while(i++ < 5)
    {
        printf("main pthread: thread id = %lx\n", pthread_self());
        // printf("main pthread: thread id = %lx, %d\n", pthread_self(), gettid());
        sleep(1);
    }

}

int main()
{
    test_pthread_create();

    return 0;
}
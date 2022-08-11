#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* mythread(void *arg)
{
    int i = 0;
    int *pa = (int *)malloc(4);
    *pa = 111;

    sleep(1);

    // return (void*)111;
    // return (void*)pa;
    pthread_exit((void*)111);
}

void test_thread_max()
{
    pthread_t thid;
    int ret = 0;

    pthread_attr_t pth_attr;
    pthread_attr_init(&pth_attr);
    pthread_attr_setdetachstate(&pth_attr, PTHREAD_CREATE_DETACHED);
    // 通过调整堆栈大小可以控制产生的线程个数，线程个数还受 ulimit -u 控制(轻量级进程)
    // pthread_attr_setstacksize(&pth_attr,4096);

    int i = 0;
    while (1)
    {
        ret = pthread_create(&thid, &pth_attr, &mythread, (void*)10);
        if (ret != 0)
        {
            printf("pthread_create error:%s\n", strerror(ret));
            exit(0);
        }
        else
        {
            printf("pthread create %d\n", ++i);
        }
        
    }

    pthread_attr_destroy(&pth_attr);

#if 0
    void *result;
    ret = pthread_join(thid,&result);
    if (ret != 0)
    {
        printf("pthread_join error:%s\n",strerror(ret));       
        exit(1);
    }
    printf("result:%ld\n",(long)(result) );
#endif

    // while (1)
    // {
    //     printf("main pthread: thread id = %lx\n",pthread_self() );
    //     sleep(1);
    // }
}

int main()
{


    return 0;
}
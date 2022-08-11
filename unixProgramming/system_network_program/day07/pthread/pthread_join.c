#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>

void* pthreadFunc(void* arg)
{
    int i =0;
    while (++i <= 10)
    {
        printf("child thread: pid:%d, tid = %lx, arg = %ld, LWP:%ld\n", getpid(), pthread_self(), (long)arg, syscall(SYS_gettid));
        sleep(1);
    }

    return (void*)111;
}

void test_pthread_join()
{
    pthread_t tid; 
    int ret = pthread_create(&tid, NULL, pthreadFunc, (void*)0);
    if (ret != 0)
    {
        printf("pthread_create error:%s\n", strerror(ret));
        exit(0);
    }

    // void *result;
    // pthread_join(tid, &result);  // 主线程退出，子线程也退出了。

    int i = 0;
    // while (1)
    while(i++ < 5)  
    {
        printf("main pthread: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
        sleep(1);
    }

}


int main()
{
    test_pthread_join();

    return 0;
}
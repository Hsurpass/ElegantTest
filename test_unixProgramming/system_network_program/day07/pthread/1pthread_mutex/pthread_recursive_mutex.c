#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

// 允许同一个线程加锁而不死锁,不同线程加锁和正常的互斥量一样
// 递归锁通常用在 [同一个线程] 重复加锁
void test_one_thread_recursive_mutex()
{
    pthread_mutex_t mymutex;
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mymutex, &mutex_attr);

    int ret;
    for (int i = 0; i < 10; ++i)
    {
        ret = pthread_mutex_lock(&mymutex);
        printf("ret = %d\n", ret);
    }

    for (int i = 0; i < 10; ++i)
    {
        ret = pthread_mutex_unlock(&mymutex);
        printf("ret = %d\n", ret);
    }

    if (ret == EDEADLK)
    {
        printf("EDEADLK\n");
    }

    pthread_mutex_destroy(&mymutex);
    pthread_mutexattr_destroy(&mutex_attr);
}

// 一个线程对递归锁重复的上锁，必须由这个线程重复相同的次数解锁,
// 才能解开这个递归锁，别的线程才能得到这个锁
static pthread_mutex_t mymutex;
void *worker_thread(void *param)
{
    pthread_t threadID = pthread_self();

    printf("thread start, ThreadID: %ld\n", threadID);

    int ret = pthread_mutex_lock(&mymutex);
    if (ret == EDEADLK)
    {
        printf("EDEADLK, ThreadID: %ld\n", threadID);
    }
    else
        printf("ret = %d, ThreadID: %ld\n", ret, threadID);

    //休眠1秒
    sleep(2);
    pthread_mutex_unlock(&mymutex);

    return NULL;
}

void test_multiThread_recursive_mutex()
{
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mymutex, &mutex_attr);

    int ret = pthread_mutex_lock(&mymutex);
    printf("ret = %d\n", ret);
    pthread_mutex_unlock(&mymutex);

    //创建2个工作线程
    pthread_t threadID1;
    pthread_t threadID2;
    pthread_create(&threadID1, NULL, worker_thread, NULL);
    sleep(1);

    pthread_create(&threadID2, NULL, worker_thread, NULL);
    
    pthread_join(threadID1, NULL);
    pthread_join(threadID2, NULL);

    pthread_mutex_destroy(&mymutex);
    pthread_mutexattr_destroy(&mutex_attr);
}

int main()
{
    // test_one_thread_recursive_mutex();
    test_multiThread_recursive_mutex();

    return 0;
}
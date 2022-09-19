#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

static int condition = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* mythread(void* arg)
{
    static int value = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("pthread id %lx [%ld] get lock\n", pthread_self(), (long)arg);
        
        if (condition <= 0) // 使用if会导致一个线程虚假唤醒
        {
            printf("thid %lx [%ld] unlock and wait condition... \n", pthread_self(), (long)arg);
            pthread_cond_wait(&cond, &mutex);
            printf("thid %lx [%ld] be awakened and get lock, condition:%d \n", pthread_self(), (long)arg, condition);
        }
        
        sleep(3);
        condition--;
        printf("pthread id %lx [%ld] unlock, ***** value = %d ***, condition = %d\n", pthread_self(), (long)arg, ++value, condition);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    
    pthread_exit((void* )111);
}

void pthread_condtion_if()
{
    pthread_t thid_a, thid_b;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&thid_a, NULL, mythread, (void *)0);
    pthread_create(&thid_b, NULL, mythread, (void *)1);

    // while(1)
    {
        sleep(5);
        pthread_mutex_lock(&mutex);
        printf("main thread id[%lx] get lock\n", pthread_self());

        condition++;
        printf("main thread id[%lx] add condtion:%d\n", pthread_self(), condition);
        pthread_mutex_unlock(&mutex);
        // pthread_cond_signal(&cond);
        pthread_cond_broadcast(&cond);
        // pthread_mutex_unlock(&mutex);    // 如果在通知唤醒函数之后解锁，会先解锁后，pthread_cond_wait才会处理唤醒信号， 如果不解锁的话就会一直阻塞下去
        printf("main thread id[%lx] unlock\n", pthread_self());

    }
    
    pthread_join(thid_a, NULL);
    pthread_join(thid_b, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
}

int main()
{
    pthread_condtion_if();

    return 0;
}
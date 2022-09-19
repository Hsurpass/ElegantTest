#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/syscall.h>

sem_t sem;
//a --> b --> c
void *mythread_a(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
        printf("%s tid:%lx [%ld], LWP:%ld, get sem\n", __FUNCTION__, pthread_self(), (long)arg, syscall(SYS_gettid));
        
        sleep(5);
        
        sem_post(&sem);
        printf("%s tid:%lx [%ld], LWP:%ld post sem\n", __FUNCTION__, pthread_self(), (long)arg, syscall(SYS_gettid));
        
        sleep(1);
    }

    pthread_exit((void *)0);
}

void *mythread_b(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
        printf("%s tid:%lx [%ld], LWP:%ld, get sem\n", __FUNCTION__, pthread_self(), (long)arg, syscall(SYS_gettid));

        sleep(5);

        sem_post(&sem);
        printf("%s tid:%lx [%ld], LWP:%ld post sem\n", __FUNCTION__, pthread_self(), (long)arg, syscall(SYS_gettid));
        
        sleep(1);
    }

    pthread_exit((void *)0);
}

// void *mythread_c(void *arg)
// {
//     while (1)
//     {
//         sem_wait(&sem);
//         puts(__FUNCTION__);
//         sleep(5);
//         sem_post(&sem);
//         sleep(1);
//     }

//     pthread_exit((void *)0);
// }

void binary_sem_simulate_mutex()
{
    sem_init(&sem, 0, 1);   // 匿名二值信号量模拟互斥锁
    pthread_t thid_a;
    pthread_t thid_b;
    // pthread_t thid_c;

    pthread_create(&thid_a, NULL, mythread_a, (void *)1);
    pthread_create(&thid_b, NULL, mythread_b, (void *)2);
    // pthread_create(&thid_c, NULL, mythread_c, (void *)113);

    pthread_join(thid_a, NULL);
    pthread_join(thid_b, NULL);
    // pthread_join(thid_c, NULL);

    sem_destroy(&sem);
   
}

int main()
{
    binary_sem_simulate_mutex();

    return 0;
}
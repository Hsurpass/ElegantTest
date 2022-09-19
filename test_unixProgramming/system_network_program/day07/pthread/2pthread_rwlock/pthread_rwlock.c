#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

int count = 0;
pthread_rwlock_t rwlock;

void *thread_write(void *arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rwlock);
        printf("write pthread id %lx [%ld] getwrlock\n", pthread_self(), (long)arg);

        count++;
        sleep(5);
        
        pthread_rwlock_unlock(&rwlock);
        printf("write pthread id %lx [%ld] unwrlock, count:%d \n", pthread_self(), (long)arg, count);
        
        sleep(3);
    }
    
}

void* thread_read(void* arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("read pthread id %lx [%ld] getrdlock\n", pthread_self(), (long)arg);
        
        sleep(1);

        pthread_rwlock_unlock(&rwlock);
        printf("read pthread id %lx [%ld] unrdlock, count:%d \n", pthread_self(), (long)arg, count);
        sleep(1);
    }
    
}

void test_pthread_rwlock()
{
    pthread_t thid[6];
    pthread_rwlock_init(&rwlock, NULL);

    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&thid[i], NULL, thread_read, (void *)i);
    }

    pthread_create(&thid[5], NULL, thread_write, (void *)666);

    for (size_t i = 0; i < 6; i++)
    {
        pthread_join(thid[i], NULL);
    }
    
    pthread_rwlock_destroy(&rwlock);
}

int main()
{
    test_pthread_rwlock();

    return 0;
}
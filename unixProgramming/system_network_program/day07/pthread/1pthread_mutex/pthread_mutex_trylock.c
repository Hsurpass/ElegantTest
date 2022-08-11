#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

static int value = 0;
pthread_mutex_t mutex;

void* mythread(void* arg)
{
    int i = 0, tmp;
    // while (pthread_mutex_trylock(&mutex) == EBUSY)
    // {
    //     printf("pthread id %lx trylock busy\n",pthread_self());
    //     sleep(1);
    // }

    for (size_t i = 0; i < 10; i++)
    {
        // pthread_mutex_lock(&mutex);
        while (pthread_mutex_trylock(&mutex) == EBUSY)
        {
            printf("pthread id %lx [%ld] trylock busy\n", pthread_self(), (long)arg);
            sleep(1);
        }

        printf("thread ID: %lx, arg:%ld, locked\n", pthread_self(), (long)arg);
        tmp = value;
        tmp++;
        value = tmp;
        
        pthread_mutex_unlock(&mutex);
        printf("thread ID: %lx, arg:%ld, unlocked\n", pthread_self(), (long)arg);
        
        sleep(3);
    }
    
    // pthread_mutex_unlock(&mutex);

    printf("thread ID: %lx, arg:%ld, value = %d\n", pthread_self(), (long)arg, value);
    return (void *)111;
}

void test_pthread_mutex_trylock()
{
    pthread_t thid0, thid1;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thid0, NULL, mythread, (void *)0);
    pthread_create(&thid1, NULL, mythread, (void *)1);

    pthread_join(thid0, NULL);
    pthread_join(thid1, NULL);

    pthread_mutex_destroy(&mutex);
}

int main()
{
    test_pthread_mutex_trylock();

    return 0;
}
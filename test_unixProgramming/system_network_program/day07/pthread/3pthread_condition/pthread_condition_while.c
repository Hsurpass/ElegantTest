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
        
        while (condition <= 0)
        {
            printf("thid %lx [%ld] wait condition...\n", pthread_self(), (long)arg);
            pthread_cond_wait(&cond, &mutex);
            printf("thid %lx [%ld] be awakened, condition:%d \n", pthread_self(), (long)arg, condition);
        }
        
        sleep(3);
        condition--;
        
        pthread_mutex_unlock(&mutex);
        printf("pthread id %lx [%ld] unlock, ***** value = %d ***, condition = %d\n", pthread_self(), (long)arg, ++value, condition);
        
        sleep(1);
    }
    
    pthread_exit((void* )111);
}

void test_pthread_cond_while()
{
    pthread_t thid_a, thid_b;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&thid_a, NULL, mythread, (void *)0);
    pthread_create(&thid_b, NULL, mythread, (void *)1);

    while(1)
    {
        sleep(5);
        printf("main thread id[%lx] get lock\n", pthread_self());
        pthread_mutex_lock(&mutex);
        
        condition++;
        printf("main thread id[%lx] add condtion:%d\n", pthread_self(), condition);

        pthread_mutex_unlock(&mutex);
        printf("main thread id[%lx] unlock\n", pthread_self());
        
        // pthread_cond_signal(&cond);
        pthread_cond_broadcast(&cond);

        // pthread_mutex_unlock(&mutex);
        sleep(5);
    }
    
    pthread_join(thid_a,NULL);
    pthread_join(thid_b,NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
 
}

int main()
{
    test_pthread_cond_while();

    return 0;
}
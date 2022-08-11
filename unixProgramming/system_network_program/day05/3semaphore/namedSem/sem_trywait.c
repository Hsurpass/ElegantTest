#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

void test_sem_trywait()
{
    int ret;
    sem_t* sem = sem_open("/mytrysem", O_CREAT, 0664, 1);
    // sem_t* sem = sem_open("/mytrysem", O_CREAT, 0664, 2);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        _exit(0);
    }
    printf("sem create success\n");
    
    while (1)
    {
        ret = sem_trywait(sem);
        if (-1 == ret)
        {
            if (errno == EAGAIN)
            {
                printf("trywait again\n");
                sleep(1);
                continue;
            }
            perror("trywait");
            _exit(0);
        }
        
        printf("get\n");
        sleep(5);

        sem_post(sem);
        printf("post\n");
        sleep(1);
    }
    
    sem_close(sem);
    // ret = sem_unlink("/mytrysem");
    // ret = sem_unlink("mytrysem");
    // ret = unlink("/dev/shm/sem.mytrysem");
    // ret = sem_unlink("/run/shm/sem.mytrysem");
    ret = unlink("/run/shm/sem.mytrysem");
    if(ret == -1)
    {
        perror("sem_unlink");
    }
    exit(0);
}

int main()
{
    test_sem_trywait();

    return 0;
}
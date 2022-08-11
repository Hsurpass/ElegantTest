#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

void test_sem_wait()
{
    int ret;
    sem_t* sem = sem_open("/mysem",O_CREAT, 0664, 1);   // 二值信号量
    // sem_t* sem = sem_open("/mysem",O_CREAT, 0664, 2);    // 计数信号量
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        _exit(0);
    }
    printf("sem create success\n");

    while (1)
    {
        sem_wait(sem);
        printf("get\n");
        sleep(5);

        sem_post(sem);
        printf("post\n");
        sleep(1);
    }
    
    sem_close(sem);
    sem_unlink("/mysem");
}

int main()
{
    test_sem_wait();

    return 0;
}
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

void test_sem_open()
{
    int ret = 0;
    // 推荐加个/ 方便跨平台， 默认还是在/dev/shm下创建信号量文件
    sem_t *sem = sem_open("/mysem", O_CREAT, 0664, 1);  // 二值信号量
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        _exit(0);
    }
    printf("create sem success\n");

    sem_close(sem);
    sem_unlink("/mysem");   // 删除信号量文件
    // unlink("/dev/shm/sem.mysem");   // 使用全路径就必须使用全路径了
    printf("unlink sem success\n");
}

int main()
{
    test_sem_open();

    return 0;
}
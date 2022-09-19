#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <pthread.h>

struct id_fd
{
    int id;
    int fd;
};

// 文件锁 写线程
void* thread_flock_EX(void* arg)
{
    struct id_fd writefd = *(struct id_fd*)arg;

    int id = writefd.id;
    int fd = writefd.fd;

    char buf[32] = "0123456789";
    int ret = 0;
    while (1)
    {
        flock(fd, LOCK_EX);
        printf("pthread id: %lx [%d] get file lock __EX, write...\n", pthread_self(), id);
        
        ret = write(fd, buf, strlen(buf));
        if (ret == -1)
        {
            perror("write");
        }
        printf("write buf = %s, ret:%d\n", buf, ret);

        flock(fd, LOCK_UN);
        printf("pthread id: %lx [%d] write flock unlock __EX\n", pthread_self(), id);

        sleep(5);
    }
}

// 文件锁 读线程
void* thread_flock_SH(void* arg)
{
    struct id_fd readfd = *(struct id_fd*)arg;

    int id = readfd.id;
#if 0
    // int fd = readfd.fd;
#endif

#if 1
    int fd = open("log1.txt", O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        exit(-1);
    }
#endif

    char buf[32] = { 0 };
    int ret = 0;
    memset(buf, 0x31, sizeof(buf));

    while(1)
    {
        sleep(1);

        flock(fd, LOCK_SH); // 文件所其实是对vnode文件加锁
        printf("pthread id: %lx [%d] get file lock __share, read....\n", pthread_self(), id);

        ret = read(fd, buf, 10);
        if (ret == -1)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("read buf = %s, ret: %d\n", buf, ret);

        flock(fd, LOCK_UN);
        printf("pthread id: %lx [%d] read flock unlock __share\n", pthread_self(), id);

        sleep(2);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [filename]\n", argv[0]);
        exit(0);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT);
    if (-1 == fd)
    {
        perror("open");
        exit(-1);
    }

    pthread_t tid1;
    pthread_t tid2;

    struct id_fd idfd1; idfd1.id = 0; idfd1.fd = fd;
    struct id_fd idfd2; idfd2.id = 1; idfd2.fd = fd;

    pthread_create(&tid1, NULL, thread_flock_EX, &idfd1);
    pthread_create(&tid2, NULL, thread_flock_SH, &idfd2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    close(fd);


    return 0;
}
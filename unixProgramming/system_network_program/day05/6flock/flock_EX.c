#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// 写进程
void test_between_process_LOCK_EX(int argc, char **argv)
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
    char buf[32] = "0123456789";
    int ret = 0;
    
    while (1)
    {
        flock(fd, LOCK_EX);
        printf("process id: %d get file lock __EX, write...\n", getpid());
        
        ret = write(fd, buf, strlen(buf));
        if (ret == -1)
        {
            perror("write");
        }
        printf("write buf = %s, ret:%d\n", buf, ret);

        flock(fd, LOCK_UN);
        printf("write flock unlock __EX\n");

        sleep(1);
    }

    close(fd);
}

int main(int argc, char **argv)
{
    test_between_process_LOCK_EX(argc, argv);

    return 0;
}
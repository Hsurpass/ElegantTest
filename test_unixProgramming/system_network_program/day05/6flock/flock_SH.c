#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// 读进程
void test_between_process_LOCK_SH(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [filename]\n", argv[0]);
        exit(0);
    }

    int fd = open(argv[1], O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        exit(-1);
    }

    char buf[32];
    int ret = 0;
    memset(buf, 0x31, sizeof(buf));

    while(1)
    {
        flock(fd, LOCK_SH); // 文件所其实是对vnode文件加锁
        printf("process id: %d get file lock __share, read....\n", getpid());

        ret = read(fd, buf, 10);
        if (ret == -1)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("read buf = %s, ret: %d\n", buf, ret);

        flock(fd, LOCK_UN);
        printf("read flock unlock __share\n");

        sleep(3);
    }

    close(fd);
}

int main(int argc, char **argv)
{
    test_between_process_LOCK_SH(argc, argv);

    return 0;
}
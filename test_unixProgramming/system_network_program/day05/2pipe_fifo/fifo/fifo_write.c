#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// const char*filename = "myfifo";
const char* filename = "/home/hcy1804/myfifo";

void sighandle(int sig)
{
    printf("write broken\n");
}

void fifo_write()
{
    signal(SIGPIPE, sighandle);

    int ret = 0;
    ret = mkfifo(filename, 0640);
    if (ret == -1)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");        
            exit(0);
        }
    }
    printf("mkfifo success\n");

    int fd = open(filename, O_WRONLY);
    if (-1 == fd)
    {
        perror("write open");
        exit(0);
    }
    printf("open success\n");

    char buf[32]; int i = 0;
    while (1)
    {
        sprintf(buf, "DATA%d", ++i);
        ret = write(fd, buf, strlen(buf));  // 如果读端没有打开，则阻塞在write()上。如果读端打开后关闭，写端将会触发SIGPIPE信号导致进程退出。
        if (ret == -1)
        {
            perror("write");
            exit(0);
        }
        printf("write: buf = %s, ret = %d\n", buf, ret);

        #if 0
        if (i == 10)
        {
            printf("write fifo close\n");
            close(fd);  // 关闭写端
            break;
        }
        #endif

        sleep(1);
    }

    exit(0);
}

int main()
{
    fifo_write();
        
    return 0;
}


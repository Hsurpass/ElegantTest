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

void fifo_read()
{
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
    
    int fd = open(filename, O_RDONLY);
    if (-1 == fd)
    {
        perror("read open");
        exit(0);
    }
    printf("open success\n");

    char buf[32]; int i = 0;
    while (1)
    {
        // 如果写端没有打开，则阻塞在write()上。
        ret = read(fd, buf, sizeof(buf) - 1);   // 给"\0"留一位
        if (ret == -1)
        {
            perror("read");
            exit(0);
        }
        else if (ret == 0)  // 如果写端打开后关闭，读端将会返回0.
        {
            printf("read fifo close\n");
            close(fd);
            break;
        }
        
        buf[ret] = '\0';
        printf("read: buf = %s,ret = %d\n", buf, ret);
        if (i++ == 10)    // 如果读端打开后关闭，写端将会触发SIGPIPE信号导致进程退出。
        {
            printf("read fifo close\n");
            close(fd);
            break;
        }

        sleep(1);
    }

    exit(0);
}

int main()
{
    fifo_read();
        
    return 0;
}


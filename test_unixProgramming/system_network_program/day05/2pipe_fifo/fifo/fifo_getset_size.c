#define _GNU_SOURCE
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

// const char* filename = "myfifo";
const char* filename = "/home/hcy1804/myfifo";

void test_F_GETPIPE_SZ()
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
    // int fd = open(filename, O_RDONLY);
    // int fd = open(filename, O_RDONLY | O_NONBLOCK);
    // int fd = open(filename, O_WRONLY | O_NONBLOCK);
    int fd = open(filename, O_RDWR | O_NONBLOCK);

    if (-1 == fd)
    {
        perror("read open");
        exit(0);
    }
    printf("open success\n");

    printf("fifosize = %d\n", fcntl(fd, F_GETPIPE_SZ));
    // fcntl(fd, F_SETPIPE_SZ, 4096*3);        
    printf("fifosize = %d\n",fcntl(fd, F_GETPIPE_SZ));
    printf("atomic_fifo_maxsize: %ld\n", pathconf(filename, _PC_PIPE_BUF));
}

int main()
{
    test_F_GETPIPE_SZ();
    
    return 0;
}


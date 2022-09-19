#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void forkBeforeOpenFile()
{
    char buf[32];
    memset(buf, 0x31, sizeof(buf));

    pid_t pid = fork();
    int fd = open("log1.txt", O_RDONLY);

    if (pid == 0)
    {
        int ret = read(fd, buf, 10);    
        if (-1 == ret)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("child process, buf = %s,pid = %d\n", buf, getpid());
        exit(0);
    }
    else if (pid > 0)
    {
        sleep(2);
        int ret = read(fd, buf, 10);    
        if (-1 == ret)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("parent process, buf = %s,pid = %d\n", buf, getpid());
        exit(1);
    }
    else
    {
        perror("fork");
    }

}

int main()
{
    forkBeforeOpenFile();
    
    return 0;
}
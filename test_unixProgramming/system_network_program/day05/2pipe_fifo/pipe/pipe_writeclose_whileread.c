#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

//child read
void child_process(int fd[2])
{
    close(fd[1]);
    int ret;
    char buf[32] = { 0 };
    while(1)
    {
        ret = read(fd[0], buf, sizeof(buf));
        if (-1 == ret)
        {
            perror("read");
        }
        else if (ret == 0)  // 写端关闭的情况下，会返回0，也把读端关闭
        {
            printf("child close fd[0] read\n");
            close(fd[0]);
            exit(1);
        }
        
        // buf[ret] = '\0';
        printf("child process[%d] read:buf=%s, ret = %d\n", getpid(), buf, ret);
        sleep(1);
    }  
}

//parent write
void parent_process(int fd[2])
{
    close(fd[0]);
    int ret; int i = 0;
    char buf[32];
    //close(fd[1]);
    while (1)
    {
        sleep(1);
        sprintf(buf, "event%d", ++i);
        ret = write(fd[1], buf, strlen(buf));
        if (-1 == ret)
        {
            perror("write");
        }
        
        printf("parent process[%d] write:buf = %s, ret = %d\n", getpid(), buf, ret);
        
        if(i == 10)
        {
            printf("parent close fd[1] write\n");
            close(fd[1]);
            break;
        }
    }
    
    int status;
    pid_t childpid = wait(&status);
    printf("waitpid, pid:%d\n", childpid);
    exit(0);
}

// 写端关闭，读端一直读会一直返回0
void pipe_writeclose_whileread()
{
    int fd[2], ret;
    
    ret = pipe(fd);
    if (-1 == ret)
    {
        perror("pipe");
    }
    
    pid_t pid = fork();
    if (pid == 0)
    {
        child_process(fd);
    }
    else if(pid > 0)
    {
        parent_process(fd);
    }
    else
    {
        perror("fork");
    }
}

int main()
{
    pipe_writeclose_whileread();

    return 0;
}


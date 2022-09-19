#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

//child read
void child_process(int fd[2])
{
    close(fd[1]);
    int ret;
    char buf[32];
    while(1)
    {
        ret = read(fd[0], buf, sizeof(buf));
        if (-1 == ret)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("child process read:buf=%s,ret = %d\n", buf, ret);
        // sleep(1);
    }  
}

//parent write
void parent_process(int fd[2])
{
    close(fd[0]);
    int ret;int i = 0;
    char buf[32];
    while (1) //write_sleep ---> read_block
    {
        sleep(5);
        // sprintf(buf,"event%d",++i);
        // ret = write(fd[1],buf,strlen(buf) );
        // if (-1 == ret)
        // {
        //     perror("write");
        // }
        // printf("parent process write:buf = %s,ret = %d\n",buf,ret);
    }
    
}

// 测试写端未关闭，管道无数据的情况下，读端会阻塞。
void test_pipe_readblock()
{
    int fd[2],ret;
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
    test_pipe_readblock();

    return 0;
}


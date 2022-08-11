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
        // ret = read(fd[0],buf,sizeof(buf));
        // if (-1 == ret)
        // {
        //     perror("read");
        // }
        // buf[ret] = '\0';
        // printf("child process read:buf=%s,ret = %d\n",buf,ret);
        sleep(1);
    }  
}

//parent write
void parent_process(int fd[2])
{
    close(fd[0]);
    int ret;
    int i = 0, count =0;
    char buf[32];
    while (1)
    {
        // sleep(5);
        // sprintf(buf,"event%d",++i);
        ret = write(fd[1], "1", 1); // 管道写满之后会阻塞住
        if (-1 == ret)
        {
            perror("write");
        }
        printf("parent process write:count = %d, ret = %d\n", ++count, ret);
    }
    
}

// 测试能往管道写多少字节数据 //65536bytes 64k
void test_pipe_max()
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
    test_pipe_max();

    return 0;
}


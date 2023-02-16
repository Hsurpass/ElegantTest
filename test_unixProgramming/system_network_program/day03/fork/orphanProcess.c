#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>

void handle_sig(int sig)
{
    printf("pid = %d, sig=%d\n",getpid(), sig);     // 17
}

void testOrphanProcess()
{
    for (int i = 1;i <=31; i++)
    {
        signal(i, handle_sig);
    }
    pid_t pid = fork();

    if (pid > 0)
    {
        // 父进程先于子进程退出，会产生孤儿进程, 最终由init进程回收
        for (size_t i = 0; i < 5; i++)
        {
            printf("parent process, me pid:%d, child pid: %d\n", getpid(), pid);
            sleep(1);
        }
        exit(0);
    }
    else if(pid == 0)
    {
        for (size_t i = 0; i < 10; i++)
        {
            printf("child process, child pid:%d, parent pid: %d\n", getpid(), getppid());
            sleep(1);
        }
        exit(0);
    }
    else
    {
        perror("fork");
    }
}

int main()
{
    printf("current pid: %d\n", getpid());
    testOrphanProcess();

    return 0;
}
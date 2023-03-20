#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

// fork之后父子进程有自己的全局变量和信号处理函数，且不会相互影响。

int g_var = 1;

void handle_sig(int sig)
{
    printf("handle_sig sig:%d, pid:%d\n", sig, getpid());
    g_var = 2;
}

void child_handle_sig(int sig)
{
    printf("child_handle_sig sig:%d, pid:%d\n", sig, getpid());
    g_var = 3;
}

void fork_signal()
{
    signal(SIGINT, handle_sig);

    pid_t pid = fork();
    if (pid > 0)
    {
        while (1)
        {
            printf("parent process:%d, g_var:%d\n", getpid(), g_var);
            sleep(2);
        }
    }
    else if (pid == 0)
    {
        signal(SIGINT, child_handle_sig); 
        while (1)
        {
            printf("child process:%d, g_var:%d\n", getpid(), g_var);
            sleep(2);
        }
    }
    else
    {
        perror("fork");
    }
}

int main()
{
    fork_signal();

    return 0;
}
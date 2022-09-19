#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/syscall.h>

// fork 只能复制当前线程的状态，不能复制其他线程的状态，不要在多线程程序中使用fork
// pthread_atfork 在调用fork之前调用prepare， fork后在进入父进程之前调用parent, 在进入子进程之前调用child
void prepare()
{
    sleep(1);
    printf("prepare func: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
}

void parent()
{
    sleep(1);
    printf("parent func: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
}

void child()
{
    sleep(1);
    printf("child func: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
}

int main()
{

    printf("main1: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));
    if(pthread_atfork(prepare, parent, child) != 0)
    {
        perror("pthread_atfork");
    }
    printf("main2: pid:%d, thread id = %lx, LWP:%ld\n", getpid(), pthread_self(), syscall(SYS_gettid));

    pid_t pid = fork();
    if(pid > 0)
    {
        printf("parent process\n");
    }
    else if (pid == 0)
    {
        printf("child process\n");
    }
    else
    {
        perror("fork");
    }

    printf("return\n");
    return 0;
}
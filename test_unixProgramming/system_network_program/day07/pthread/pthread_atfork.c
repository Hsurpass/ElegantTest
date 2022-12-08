#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/syscall.h>

/*
在调用fork时，内部创建子进程之前在父进程中会调用prepare，内部创建子进程成功后，父进程会调用parent ，子进程会调用child， 这就是pthread_atfork()的作用。
因为在fork之前可能有多个线程，有可能是在主线程中调用也有可能是在子线程中调用， 如果fork()是在子线程中调用得到一个新进程，新进程就只有一个执行序列，只有一个线程（调用fork的线程被继承下来）。

对于编写多线程程序来说，最好不要调用fork()，即不要编写多线程多进程程序，因为Linux的fork()只克隆当前线程的thread of control， 不克隆其他线程。 
fork()之后，除了当前线程之外，其他线程都消失了，也就是说，不能够一下子fork()和父进程一样的多线程子进程。

fork()之后子进程中只有一个线程，其他线程都消失了，这就造成一个危险的局面：其他线程可能正好位于临界区指内，持有了某个锁，而它忽然死亡，再也没有机会去解锁了。
如果子进程试图再对同一个mutex加锁，就会死锁。

那我们调用pthread_atfork()的话就可以在fork之前，即创建子进程之前去解锁，那样拷贝下来的就是解锁的，就不会死锁了
*/

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


void test_pthread_atfork()
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

}

int main()
{
    test_pthread_atfork();
  
    printf("return\n");
    return 0;
}
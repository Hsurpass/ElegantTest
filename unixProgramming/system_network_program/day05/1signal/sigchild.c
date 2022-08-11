#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void child_process()
{
    printf("child process: pid = %d\n", getpid());
    sleep(50);  // 子进程后于父进程退出本身就是不对的，嘻嘻，所以父进程一定要等待回收子进程
    exit(1);
}

void sig_handle_while_waitpid(int sig)
{
    int status;
    pid_t childpid;
    
    while((childpid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
    {
        sleep(1);
        printf("recycle child process: sig = %d,childpid = %d\n", sig, childpid);

        if(WIFEXITED(status))
        {
            printf("parent process, parent pid = %d, child pid =%d,exit code = %d\n", getpid(), childpid, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status))
        {   
            printf("parent process, parent pid = %d, child process [%d] killed by signal %d\n", getpid(), childpid, WTERMSIG(status) );
        }
        else if (WIFSTOPPED(status))
        {
            printf("parent process, parent pid = %d, child process [%d] stopped by signal %d\n", getpid(), childpid, WSTOPSIG(status));
        }
        else if (WIFCONTINUED(status))
        {
            printf("parent process, parent pid = %d, child process [%d] continued by signal 18 \n", getpid(), childpid);
        }
        else
        {
            printf("other\n");        
        }

    }
}

void sig_handle_waitpid(int sig)
{
    int status;
    // 使用了WNOHANG，但不进行轮询，如果子进程后于父进程退出，子进程就变成了孤儿进程。
    pid_t childpid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);    
    printf("recycle child process: sig = %d, childpid = %d\n", sig, childpid);
    
    if(WIFEXITED(status))
    {
        printf("parent process, parent pid = %d, child pid =%d,exit code = %d\n", getpid(), childpid, WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {   
        printf("parent process, parent pid = %d, child process [%d] killed by signal %d\n", getpid(), childpid, WTERMSIG(status) );
    }
    else if (WIFSTOPPED(status))
    {
        printf("parent process, parent pid = %d, child process [%d] stopped by signal %d\n", getpid(), childpid, WSTOPSIG(status));
    }
    else if (WIFCONTINUED(status))
    {
        printf("parent process, parent pid = %d, child process [%d] continued by signal 18 \n", getpid(), childpid);
    }
    else
    {
        printf("other\n");        
    }

}

void sig_handle_wait(int sig)
{
    pid_t childpid;
    int status;
    childpid = wait(&status);   // 如果收到 kill -19 信号就被阻塞住了
    
    printf("recycle child process: sig = %d, childpid = %d\n", sig, childpid);
    if (WIFEXITED(status))
    {
        printf("child pid = %d, exited status = %d\n", childpid, WEXITSTATUS(status));
    }
    if(WIFSIGNALED(status))
    {
        printf("child pid = %d, signaled status = %d\n", childpid, WTERMSIG(status));
    }
}

void sig_handle(int sig)
{
    printf("signal:%d, pid:[%d]\n", sig, getpid());
}

pid_t test_sigchild01()
{
    // 分别尝试kill -9 -19 -18这三种信号
    // signal(SIGCHLD, sig_handle);
    // signal(SIGCHLD, sig_handle_wait);
    // signal(SIGCHLD, sig_handle_waitpid);
    signal(SIGCHLD, sig_handle_while_waitpid);

    signal(SIGHUP, sig_handle); // 如果子进程处于暂停状态，父进程在退出时将会发送SIGHUP信号回收子进程
    
    pid_t pid = fork();
    if (pid == 0)
    {
        child_process();
    }
    else if (pid == -1)
    {
        perror("fork");
    }

    return pid;
}

void test_fork_ten_childprocess()
{
    // signal(SIGCHLD, sig_handle_waitpid);
    signal(SIGCHLD, sig_handle_while_waitpid);

    int i = 0;
    for(int i = 0; i < 10; i++)
    {
        pid_t pid = fork();
        if(pid == 0)
        {
            printf("child pid:[%d]\n", getpid());
            sleep(5);
            exit(0);    // 子进程退出的时候会连续发送10个SIGCHID信号，但是未决信号集不支持排队，同时发送多个信号就会处理一次,z这样就会产生僵尸进程。
        }
        else if(pid < 0)
        {
            perror("fork");
        }
    }
    
    
}

int main()
{
    // pid_t childpid = test_sigchild01();
    // printf("childPid:%d\n", childpid);
    test_fork_ten_childprocess();


/* 
    int i = 0;
    for (size_t i = 0; i < 10; i++)
    {
        __pid_t pid = fork();
        if (pid == 0)
        {
            child_process();
        }
        else if (pid == -1)
        {
            perror("fork");
        }
    }
*/
    int count = 0;
    while (1)
    {
        if(count++ == 20)
        {
            // kill(childpid, SIGHUP);
            break;
        }

        printf("parent process: pid = %d\n", getpid());
        sleep(1);
    }

    return 0;
}
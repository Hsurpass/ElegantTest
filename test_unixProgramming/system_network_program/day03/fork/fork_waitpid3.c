#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int test02()
{
    printf("pid = %d\n",getpid());
    printf("ppid = %d\n",getppid() );
    printf("uid = %d\n",getuid());
    printf("euid = %d\n",geteuid());
    printf("gid = %d\n",getgid());
    printf("egid = %d\n",getegid());
    return 0;
}

void handle_sig(int sig)
{
    printf("pid = %d, sig=%d\n",getpid(), sig);     // 17
}

// 父进程退出前有暂停的子进程会怎样？
// 父进程会检查所有暂停的子进程，并发送一个SIGHUP信号导致子进程退出
int test01()
{
    // signal(SIGHUP, handle_sig);
    // for (int i = 1;i <=31; i++)
    // {
    //     signal(i, handle_sig);
    // }
    pid_t pid = fork();
    if (pid > 0)
    {
        pid_t childpid;
        int status;
        while(1)
        {
            // childpid = waitpid(-1, &status, WUNTRACED | WCONTINUED);
            childpid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
            if (childpid == 0)
            {
                printf("parent process, parent pid = %d, reutrnChildId = %d, status = %d\n", getpid(), childpid, status);
                sleep(1);
            }

            #if 1
            else
            {
                if(WIFEXITED(status))
                {
                    printf("parent process, parent pid = %d, child pid =%d,exit code = %d\n", getpid(), childpid, WEXITSTATUS(status));
                    break; // 注意这个break
                }
                else if(WIFSIGNALED(status))
                {   
                    printf("parent process, parent pid = %d, child process [%d] killed by signal %d\n", getpid(), childpid, WTERMSIG(status) );
                    break;  // 注意这个break
                }
                else if (WIFSTOPPED(status))// kill -19
                {
                    printf("parent process, parent pid = %d, child process [%d] stopped by signal %d\n", getpid(), childpid, WSTOPSIG(status));
                    // break; //父进程会检查所有暂停的子进程，并发送一个SIGHUP信号导致子进程退出
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
            #endif  
        }

        #if 0
        {
            if(WIFEXITED(status))
            {
                printf("parent process, parent pid = %d, child pid =%d,exit code = %d\n", getpid(), childpid, WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {   
                printf("parent process, parent pid = %d, child process [%d] killed by signal %d\n", getpid(), childpid, WTERMSIG(status) );
            }
            else if (WIFSTOPPED(status))    // 子进程挂起，父进程退出变成孤儿进程
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
        #endif

        exit(0);
    }
    else if(pid == 0)
    {
        for (size_t i = 0; i < 10; i++)
        {
            printf("child process, ppid = %d,childid = %d\n",getppid(),getpid());
            sleep(1);
        }

        exit(-1);
    }
    else
    {
        perror("fork");
    }
    

    return 0;
}

int main()
{
    test01();

    return 0;
}

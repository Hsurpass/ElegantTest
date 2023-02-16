#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void hand_SIGCHLD(int sig)
{
    printf("pid = %d, sig=%d\n",getpid(), sig);     // 17
    int status;
    pid_t childpid = wait(&status);
    printf("child pid = %d, status = %d\n", childpid, status);
}

int main()
{
    // signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, hand_SIGCHLD);
    pid_t pid = fork();
    if (pid > 0)
    {
        while (1)
        {
            printf("parent id = %d\n",getpid());
            sleep(1);
        }
        
    }
    else if(pid == 0)
    {
        for (size_t i = 0; i < 10; i++)
        {
            printf("parent id = %d, child id = %d\n",getppid(),getpid());
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
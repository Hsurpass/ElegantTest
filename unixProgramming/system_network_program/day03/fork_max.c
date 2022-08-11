#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// ulimit -u 1024
void fork_max()
{
    pid_t pid;
    int count = 0;

FORK_AGAIN:
    pid = fork();
    if(pid == 0)
    {
        sleep(20);
        exit(0);
    }
    else if(pid > 0)
    {
        printf("[%d] child process pid: [%d]\n", ++count, pid);
        goto FORK_AGAIN; 
    }
    else
    {
        perror("fork");
    }
}

int main()
{
    fork_max();

    return 0;
}
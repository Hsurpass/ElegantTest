#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void get_process_group_id()
{
    __pid_t pid = fork();
    if (pid > 0)
    {
        printf("parent: pid = %d, pgid = %d\n", getpid(), getpgrp());
        printf("parent: pid = %d, pgid = %d\n", getpid(), getpgid(0));
        printf("parent: pid = %d, pgid = %d\n", getpid(), getpgid(getpid()));
        sleep(1);
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("child: pid = %d, pgid = %d\n", getpid(), getpgrp() );
        printf("child: pid = %d, pgid = %d\n", getpid(), getpgid(0) );
        printf("child: pid = %d, pgid = %d\n", getpid(), getpgid(getpid()) );
        sleep(5);
        printf("child: pid = %d, pgid = %d\n", getpid(), getpgrp() );
        printf("child: pid = %d, pgid = %d\n", getpid(), getpgid(0) );
        printf("child: pid = %d, pgid = %d\n", getpid(), getpgid(getpid()) );
    }
    else
    {
        perror("fork");
    }
    
    wait(NULL);
}

int main()
{
    get_process_group_id();
    
    return 0;
}
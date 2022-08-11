#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void test_setsid()
{
    __pid_t pid = fork();
    if (pid > 0)
    {
        printf("parent: pid = %d, ppid:%d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgrp(), getsid(0) );
        sleep(1);
        exit(0);
    }
    else if (pid == 0)
    {
        // sleep(1);
        printf("child: pid = %d, ppid:%d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgrp(), getsid(0) );
        setsid();
        sleep(5);
        printf("child: pid = %d, ppid:%d, pgid = %d, sid = %d\n", getpid(), getppid(), getpgrp(), getsid(0) );
        while (1)
        {
            sleep(1);
        }
        
    }
    else
    {
        perror("fork");
    }
}

int main()
{
    test_setsid();
    
    return 0;
}
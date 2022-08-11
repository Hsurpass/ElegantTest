#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void set_process_group_id()
{
    __pid_t pid = fork();
    if (pid > 0)
    {
        printf("parent: pid = %d, ppid:%d, pgid = %d\n", getpid(), getppid(), getpgrp() );

        sleep(2);
        // 父进程重新设置子进程的组id为它自己
        // setpgid(pid, 0);
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("child: pid = %d, ppid:%d, pgid = %d\n", getpid(), getppid(), getpgrp() );
        sleep(3);
        // 子进程重新设置子进程的组id为它自己
        setpgid(0,0);
        printf("child: pid = %d, ppid:%d, pgid = %d\n", getpid(), getppid(), getpgrp() );
        while (1)
        {
            sleep(1);
        }
        
    }
    else
    {
        perror("fork");
    }

    // wait(NULL);
}

int main()
{
    set_process_group_id();
    
    return 0;
}
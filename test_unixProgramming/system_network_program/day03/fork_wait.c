#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int test02()
{
    printf("pid = %d\n", getpid());
    printf("ppid = %d\n", getppid());
    printf("uid = %d\n", getuid());
    printf("euid = %d\n", geteuid());
    printf("gid = %d\n", getgid());
    printf("egid = %d\n", getegid());
    return 0;
}

int test01()
{
    pid_t pid = fork();
    printf("pid = %d\n", pid);
    if (pid > 0)
    {
        // for(int i = 0;i < 10;i++)
        // {
        // printf("parent process, parent pid = %d\n",getpid());
        // sleep(1);
        // }
        sleep(12);
        int status;
        pid_t childpid = wait(&status);

        printf("child pid = %d,status = %d\n", childpid, status);
        if (WIFEXITED(status))
        {
            printf("child pid = %d, exited status = %d\n", childpid, WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status))
        {
            printf("child pid = %d, signaled status = %d\n", childpid, WTERMSIG(status));
        }

        exit(0);
    }
    else if (pid == 0)
    {
        for (size_t i = 0; i < 10; i++)
        {
            printf("child process, ppid = %d,childid = %d\n", getppid(), getpid());
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

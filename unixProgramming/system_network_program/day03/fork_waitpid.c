#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void test_any_id()
{
    printf("pid = %d\n", getpid());
    printf("ppid = %d\n", getppid());
    printf("uid = %d\n", getuid());
    printf("euid = %d\n", geteuid());
    printf("gid = %d\n", getgid());
    printf("egid = %d\n", getegid());
}

void test01()
{
    pid_t pid = fork();
    printf("pid = %d\n", pid);
    if (pid > 0)
    {
        int status;
        pid_t childpid;

#if 0
            childpid = waitpid(-1, &status, 0);     // 等价于 wait(&status);
#endif

#if 1
        // sleep(5);
        while (1)
        {
            childpid = waitpid(-1, &status, WNOHANG); // WNOHANG 标志表明非阻塞状态
            if (childpid == 0)
            {
                printf("parent process, child pid = %d, status = %d\n", childpid, status);
                sleep(1);
            }
            else
            {
                break;
            }
        }
#endif

        // sleep(3);
        if (WIFEXITED(status))
        {
            printf("parent process,child pid = %d,exited status = %d\n", childpid, WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status))
        {
            printf("parent process,child pid = %d,signaled status = %d\n", childpid, WTERMSIG(status));
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
}

int main()
{
    test01();

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

int g_var = 1;

void fork_vlobal_var()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("parent process:%d, g_var:%d\n", getpid(), g_var);
        // g_var = 2;
        sleep(1);
        printf("parent process:%d, g_var:%d\n", getpid(), g_var);
    }
    else if(pid == 0)
    {
        printf("child process:%d, g_var:%d\n", getpid(), g_var);
        // sleep(1);
        g_var = 2;
        printf("child process:%d, g_var:%d\n", getpid(), g_var);
    }
    else
    {
        perror("fork");
    }

}

int main()
{
    fork_vlobal_var();

    return 0;
}
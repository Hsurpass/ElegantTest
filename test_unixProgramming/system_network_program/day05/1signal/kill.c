#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void test_kill01(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("usage:%s signal pid\n", argv[0]);
    }
    
    int ret = kill(atoi(argv[1]), atoi(argv[2])); 
    if (ret == -1)
    {
        perror("kill");
    }
}

void handle_sig()
{
    printf("SIGBUS\n");
}

void handle_sigkill()
{
    printf("sigkill\n");
}

void test_kill02()
{
    pid_t pid;
    pid = fork();
    signal(SIGBUS, handle_sig);
    signal(SIGKILL, handle_sigkill);

    if(pid == 0)
    {
        printf("child process\n");
        kill(getppid(), SIGBUS);
        kill(getppid(), SIGKILL);

        printf("child send SIGBUS\n");

        while (1)
        {
            sleep(1);
        }
        
    }
    else if(pid != -1)
    {
        while(1)
            sleep(1);
    } 
    else
    {
        perror("fork:");
    } 
    
    return ;
}

int main(int argc, char** argv)
{
    // test_kill01(argc, argv);
    test_kill02();
    
    return 0;
}
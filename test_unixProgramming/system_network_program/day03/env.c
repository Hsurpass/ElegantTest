#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

void test1()
{
    printf("PATH:%s\n", getenv("PATH") );
    printf("#############################\n");
    printf("LD_LIBRARY_PATH:%s\n", getenv("LD_LIBRARY_PATH") );
    printf("#############################\n");
    printf("LIBRARY_PATH:%s\n", getenv("LIBRARY_PATH") );

}

void printEnv(char** env)
{
    int count = 0;
    while (env[count] != NULL)
    {
        printf("%s\n",env[count]);
        count++;
    }

    // printf("----------------------------------------\n");

    // char** e = env;
    // while (*e != NULL)
    // {
    //     printf("%s\n",*e++);
    // }

}

void testIPCEnv01()
{
    setenv("MYTEST", "mytest", 0);

    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(1);
        printf("child process id:%d, ${MYTEST}:%s\n", getpid(), getenv("MYTEST"));
        setenv("MYTEST", "mytest/test", 1);
        setenv("MYTEST1", "mytest1", 1);

        printf("child process id:%d, ${MYTEST}:%s\n", getpid(), getenv("MYTEST"));
        printf("child process id:%d, ${MYTEST1}:%s\n", getpid(), getenv("MYTEST1"));

    }
    else if(pid > 0)
    {
        printf("parent process id:%d, ${MYTEST}:%s\n", getpid(), getenv("MYTEST"));
        sleep(3);
        printf("parent process id:%d, ${MYTEST}:%s\n", getpid(), getenv("MYTEST"));
        printf("parent process id:%d, ${MYTEST1}:%s\n", getpid(), getenv("MYTEST1"));

    }
    else
    {
        perror("fork");
    }

}

int main(int argc, char* argv[], char** env)
{
    printEnv(env);
    // test1();
    // testIPCEnv01();

    return 0;
}





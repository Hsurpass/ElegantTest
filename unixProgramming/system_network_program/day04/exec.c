#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void test_execl()
{
    printf("test_execl\n");

    int ret = execl("/bin/ls", "ls", "-l", "-a", NULL);
    if(-1 == ret)
    {
        perror("execl");
    }
}

void test_execlp()
{
    printf("test_execlp\n");

    int ret = execlp("ls", "ls", "-l", "-a", NULL);
    if(-1 == ret)
    {
        perror("execlp");
    }
}

void test_execle(char** envBuf)
{
    printf("test_execle\n");

    // exece也必须写全路径
    int ret = execle("/bin/ls", "ls", "-l", "-a", NULL, envBuf);
    if(-1 == ret)
    {
        perror("execle");
    }
}

void test_execv()
{
    printf("test_execv\n");

    char* command[] = {"ls", "-l", "-a", NULL};
    int ret = execv("/bin/ls", command);
    if(-1 == ret)
    {
        perror("execv");
    }
}

void test_execvp()
{
    printf("test_execvp\n");

    char* command[] = {"ls", "-l", "-a", NULL};
    int ret = execvp("ls", command);
    if(-1 == ret)
    {
        perror("execvp");
    }
}

void test_execve(char** env)
{
    printf("test_execve\n");

    char* command[] = {"ls", "-l", "-a", NULL};
    int ret = execve("/bin/ls", command, env);
    if(-1 == ret)
    {
        perror("execve");
    }
}

void test_execvpe(char** env)
{
    printf("test_execvpe\n");

    char* command[] = {"ls", "-l", "-a", NULL};
    int ret = execvpe("ls", command, env);
    if(-1 == ret)
    {
        perror("execvpe");
    }
}

int main(int argc,char **argv,char **env)
{
    // char* buf[2] = { NULL };
    // char* path = getenv("PATH");
    // printf("%s\n", path);
    // char dst[1024] = { 0 };
    // sprintf(dst, "PATH=%s", path);
    // buf[0] = dst; 
    // printf("%s", buf[0]);
    // buf[1] = NULL;


    // test_execl();
    // test_execlp();
    // test_execle(env);
    // test_execv();
    // test_execvp();
    // test_execve(env);
    test_execvpe(env);





    printf("helloworld\n");
    return 0;
}

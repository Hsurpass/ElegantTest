#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

void test03()
{
    // 子进程的文件描述符表也是从父进程copy过来的
    // 所以fd指向同一个FILE结构体，共享同一个偏移量。

    char buf[32] = {0};
    int fd = open("log1.txt", O_RDONLY);
    int nr = 0;

    pid_t pid = fork();
    if(pid == 0)
    {
        printf("chind process, ppid = %d,childid = %d\n", getppid(), getpid());
        nr = read(fd, buf, 5);
        buf[nr] = '\0';
        printf("buf: %s\n", buf);
        exit(0);
    }
    nr = read(fd, buf, 5);
    buf[nr] = '\0';
    printf("buf: %s, pid:%d\n", buf, getpid());
}

int void02()
{
    printf("pid = %d\n", getpid());
    printf("ppid = %d\n", getppid() );
    printf("uid = %d\n", getuid());
    printf("euid = %d\n", geteuid());
    printf("gid = %d\n", getgid());
    printf("egid = %d\n", getegid());

    return 0;
}

int void01()
{
    pid_t pid = fork();
    printf("pid = %d\n", pid);
    if (pid > 0)
    {
        for(int i = 0;i < 10;i++)
        {
            printf("parent process, parent pid = %d, child pid = %d\n", getpid(), pid);
            sleep(1);
        }
        
    }
    else if(pid == 0)
    {
        for (size_t i = 0; i < 5; i++)
        {
            printf("chind process, ppid = %d,childid = %d\n", getppid(), getpid());
            sleep(1);
        }
    }
    else
    {
        perror("fork");
    }
    

    return 0;
}

int main()
{
    // void01();
    // void02();
    test03();
    
    return 0;
}
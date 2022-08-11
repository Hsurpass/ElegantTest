#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

void init_daemon()
{
    int ret = 0;
    __pid_t pid = fork();
    if (pid == 0)
    {
        // 子进程创建一个新的会话
        ret = setsid();
        if (-1 == ret)
        {
            perror("setsid");
        }

        // 改变当前的工作目录
        // ret = chdir("/");
        // if (ret == -1)
        // {
        //     perror("chdir");
        // }

        // 设置umask为0
        umask(0000);

        // 关闭用不到的文件描述符
        for (size_t i = 0; i < NOFILE; i++)
        {
            close(i);
        }

        return;
    }
    else if (pid > 0)
    {
        exit(0);
    }
    else
    {
        perror("fork");
    }
    
}

void create_daemon_process()
{
    time_t now_time;
    init_daemon();
    while (1)
    {
        FILE *fp = fopen("time.log", "a+");
        if (NULL == fp)
        {
            printf("fopen error\n");
        }
        now_time = time(NULL);
        fputs(ctime(&now_time), fp);
        fclose(fp);
        sleep(1);
    }
}

int main()
{
    create_daemon_process();
    
    return 0;
}
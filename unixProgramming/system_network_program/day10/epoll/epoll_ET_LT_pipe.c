/*
 *pipe创建一个管道&#xff0c;fork创建子进程&#xff0c;子进程往管道中写数据&#xff0c;父进程从管道中读数据
 *子进程每次发10个字节的数据&#xff0c;然后延时5s&#xff0c;父进程每次收5个字节的数据&#xff0c;
 *当设置为ET模式时&#xff0c;因为边缘触发只有数据到来才触发&#xff0c;不管缓存区中是否还有数据&#xff0c;这样父进程每个
 *5s内只会收到5个字节数据&#xff0c;当下个5s到来时&#xff0c;父进程才会收到上个5s子进程发的10个字节中的剩余5个字节数据。
 *当设置为LT模式时&#xff0c;默认情况下就是这个模式&#xff0c;只要有数据都会触发&#xff0c;所以每次5s中都会将缓冲区中的数据
 *读完&#xff0c;即都会将10个Bytes的数据读完。
 *
 */

#include <poll.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>
#include <sys/epoll.h>

#define MAXLINE 10

void epoll_server_LT_ET_pipe()
{
    char buf[1024] = {0};
    char ch = 'a';
    int fd[2];
    int ret = 0;
    int nready = 0;
    ret = pipe(fd);
    if (ret == -1)
    {
        perror("pipe");
        exit(errno);
    }

    int i = 0;
    pid_t pid = fork();
    if (pid == 0) //child process write
    {
        close(fd[0]); // 关闭读端
        while (1)
        {
            for (i = 0; i < MAXLINE / 2; i++)
            {
                buf[i] = ch;
            }
            buf[i - 1] = '\n'; //aaaa\n

            ch++;

            for (; i < MAXLINE; i++)
            {
                buf[i] = ch;
            }
            buf[i - 1] = '\n';
            ch++;

            printf("child process writebuf:%s", buf);
            write(fd[1], buf, strlen(buf));
            sleep(3);
        }

        close(fd[1]);
    }
    else if (pid > 0) //  parent process read 父进程作为服务器
    {
        close(fd[1]); // 关闭写端
        struct epoll_event event, reevent[10];

        int epfd = epoll_create(10);
        if (ret == -1)
        {
            perror("epoll_create");
            exit(0);
        }

        event.data.fd = fd[0];
        // event.events = EPOLLIN;
        event.events = EPOLLIN | EPOLLET;
        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0], &event); // 把读端描述符挂到树上
        if (ret == -1)
        {
            perror("epoll_ctl");
        }

        while (1)
        {
            nready = epoll_wait(epfd, reevent, 10, -1);
            printf("nready:%d\n", nready);

            for (int i = 0; i < nready; i++)
            {
                if(reevent[i].data.fd == fd[0])
                {
                    ret = read(fd[0], buf, MAXLINE / 2);
                    if (ret == 0)
                    {
                        printf("ret == 0\n");
                        break;
                    }

                    write(STDOUT_FILENO, buf, ret);
                }
            }
        }

        close(fd[0]);
        close(epfd);
    }
    else
    {
        perror("fork");
        exit(errno);
    }
}

int main()
{
    epoll_server_LT_ET_pipe();

    return 0;
}
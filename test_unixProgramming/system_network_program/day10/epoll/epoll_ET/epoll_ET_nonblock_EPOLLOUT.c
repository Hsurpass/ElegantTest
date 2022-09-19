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
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "../../../common/mysocket.h"

#define SERVERPORT 8888
#define MAXLINE 1024
#define OPENMAX 1024

void handleSIGPIPE(int sig)
{
    printf("sig=%d\n",sig);
}

void epoll_server_ET_nonblock_EPOLLOUT()
{
    signal(SIGPIPE, handleSIGPIPE);

    int sockfd, connfd;
    struct epoll_event event, epev[10];
    int ret = -1;
    int nready = 0;
    char buf[12] = "helloworld!";
    char client_ip[INET_ADDRSTRLEN];
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));

    int nullFd = open("/dev/null", O_RDONLY | O_CLOEXEC);

    // socket
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    int flag = 1;
    int len = sizeof(flag);
    // 设置端口复用
    ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &flag, len);
    if (ret == -1)
    {
        perr_exit("setsockopt");
    }

    // bind
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(listen_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // listen
    Listen(listen_fd, 128);

    int epfd = epoll_create(10);
    if (-1 == epfd)
    {
        perr_exit("epoll_create");
        exit(errno);
    }
    // 把监听fd挂树上
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event);
    if (-1 == ret)
    {
        perr_exit("epoll_ctl");
        exit(errno);
    }

    // epoll_wait
    socklen_t client_len;
    while (1)
    {
        printf("epoll_wait...\n");
        nready = epoll_wait(epfd, epev, 10, -1);
        if (nready < 0)
        {
            perr_exit("epoll_wait");
            exit(errno);
        }
        printf("nready = %d\n", nready);
        for (size_t i = 0; i < nready; i++)
        {
            printf("EVENT:%d\n", epev[i].events);
            printf("fd: %d\n", epev[i].data.fd);
            if (! ((epev[i].events & EPOLLIN) || (epev[i].events & EPOLLOUT)) )
            {
                continue;
            }

            if (epev[i].data.fd == listen_fd)
            {
                client_len = sizeof(clientaddr);
                connfd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
                if(connfd == -1)
                {
                    printf("ACCEPT ERRNO:%d\n", errno);
                    perror("accept: ");
                    if (errno == EMFILE)    //如果超出可监听的文件描述符, listen_fd 会busy loop
                    {
                        close(nullFd);
                        connfd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
                        close(connfd);
                        nullFd = open("/dev/null", O_RDONLY | O_CLOEXEC, 0664);

                        continue;
                    }
                }
                printf("epoll_ET_nonblock_server fd:%d, client_ip = %s, port = %d\n", connfd, inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));

                // 设置为非阻塞
                int status = fcntl(connfd, F_GETFL);
                status |= O_NONBLOCK;
                fcntl(connfd, F_SETFL, status);

                // event.events = EPOLLIN | EPOLLET;

                // ET模式 一开始不会触发EPOLLOUT事件
                event.events = EPOLLIN | EPOLLET | EPOLLOUT;
                event.data.fd = connfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
                if (-1 == ret)
                {
                    perr_exit("epoll_ctl");
                }
            }
            else    // 其他套接字 测试EPOLLOUT 只向对端写
            {
                sockfd = epev[i].data.fd;

                ret = Write(sockfd, buf, strlen(buf));
                if(ret == -1)
                {
                    perror("WRITE:");

                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if (ret < 0)
                    {
                        perr_exit("epoll_ctl");
                    }
                    Close(sockfd);
                }
                Write(STDOUT_FILENO, buf, ret);

                sleep(1);
            }

        }
    }

    Close(epfd);
    Close(listen_fd);
}

int main()
{
    epoll_server_ET_nonblock_EPOLLOUT();

    return 0;
}
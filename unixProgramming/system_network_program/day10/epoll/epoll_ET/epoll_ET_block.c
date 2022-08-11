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
#include "../../../common/mysocket.h"

#define SERVERPORT 8888
#define MAXLINE 1024
#define OPENMAX 1024

void epoll_server_ET_block()
{
    int sockfd, connfd;
    struct epoll_event event, epev[10];
    int ret = -1;
    int nready = 0;
    char buf[MAXLINE];
    char client_ip[INET_ADDRSTRLEN];
    memset(buf, 0, sizeof(buf));
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));

    // socket
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    
    // 设置端口复用
    int flag = 1;
    int len = sizeof(flag);
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

    // 把监听套接字挂到树上
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
            if (!(epev[i].events & EPOLLIN))
            {
                continue;
            }
            
            if (epev[i].data.fd == listen_fd)   // 监听套接字触发EPOLLIN事件
            {
                client_len = sizeof(clientaddr);
                connfd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
                printf("epoll_ET_server fd:%d, client_ip = %s, port = %d\n", connfd, inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));
                event.events = EPOLLIN | EPOLLET;
                event.data.fd = connfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
                if (-1 == ret)
                {
                    perr_exit("epoll_ctl");
                }
            }
            else    // 其他套接字
            {
                sockfd = epev[i].data.fd;

                while (1)
                {
                    // ET模式下应该使用非阻塞IO，否则一直阻塞在read, 其他连接无法处理
                    ret = Read(sockfd, buf, 5); // 阻塞IOread使用while, ET模式只会触发一次
                    if (ret == 0)   // 写端关闭，读端也关闭
                    {
                        printf("client[fd:%d] close\n", epev[i].data.fd);
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL); // 从树上摘下来
                        if (ret < 0)
                        {
                            perr_exit("epoll_ctl");
                        }
                        Close(sockfd);
                        printf("--------\n");
                        break;
                    }
                    else
                    {
                        Write(STDOUT_FILENO, buf, ret);

                        for (size_t j = 0; j < ret; j++)
                        {
                            buf[j] = toupper(buf[j]);
                        }
                        Write(sockfd, buf, ret);
                    }

                    sleep(2);
                }
            }
        }
    }

    Close(epfd);
    Close(listen_fd);
}

int main()
{
    epoll_server_ET_block();

    return 0;
}
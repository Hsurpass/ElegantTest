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

#include <iostream>
#include <string>

#include "../../../common/mysocket.h"

using namespace std;

#define SERVERPORT 8888
#define MAXLINE 1024
#define OPENMAX 1024

static string epollEVENT_To_String(uint32_t events)
{
    string str = "[";

    if(events & EPOLLIN)    // 1
        str += "EPOLLIN,";
    if(events & EPOLLPRI)   // 2
        str += "EPOLLPRI,";
    if(events & EPOLLOUT)   // 4
        str += "EPOLLOUT,";
    if(events & EPOLLERR)   // 8
        str += "EPOLLERR,";
    if(events & EPOLLHUP)   // 16
        str += "EPOLLHUP,";
    if(events & EPOLLRDNORM)    // 64
        str += "EPOLLRDNORM,";
    if(events & EPOLLRDBAND)    // 128
        str += "EPOLLRDBAND,";
    if(events & EPOLLWRNORM)    // 0001 0000 0000
        str += "EPOLLWRNORM,";
    if(events & EPOLLWRBAND)    // 0020 0000 0000
        str += "EPOLLWRBAND,";
    if(events & EPOLLMSG)       // 0100 0000 0000
        str += "EPOLLMSG,";
    if(events & EPOLLRDHUP) // 0010 0000 0000 0000
        str += "EPOLLRDHUP,";
    if(events & EPOLLEXCLUSIVE) // (unsigned int) 1 < 28
        str += "EPOLLEXCLUSIVE,";
    if(events & EPOLLWAKEUP)    // (unsigned int) 1 < 29
        str += "EPOLLWAKEUP,";
    if(events & EPOLLONESHOT)   // (unsigned int) 1 < 30
        str += "EPOLLONESHOT,";
    if(events & EPOLLET)        // (unsigned int) 1 < 231
        str += "EPOLLET,";
    
    str += "]";
    return str;
}

void epoll_server_ET_nonblock()
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

    // 用来处理超出可监听的套接字
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
            printf("EVENT:%d, %s\n", epev[i].events, epollEVENT_To_String(epev[i].events).c_str());
            printf("fd: %d\n", epev[i].data.fd);
            if (!(epev[i].events & EPOLLIN))
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

                event.events = EPOLLIN | EPOLLET;
                event.data.fd = connfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
                if (-1 == ret)
                {
                    perr_exit("epoll_ctl");
                }
            }
            else
            {
                sockfd = epev[i].data.fd;
                while (1)
                {
                    // 边缘触发使用非阻塞IO，循环读，一次把缓冲区的数据读完
                    ret = Read(sockfd, buf, 5);
                    printf("read ret = %d\n",ret);
                    if (ret == 0)   // 写端关闭了
                    {
                        printf("client[fd:%d] close\n", epev[i].data.fd);
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                        if (ret < 0)
                        {
                            perr_exit("epoll_ctl");
                        }
                        Close(sockfd);
                        printf("--------\n");
                        break;
                    }
                    else if (ret == -1)
                    {
                        printf("ERRNO:%d\n", errno);
                        perror("read==-1: ");
                        if (errno == EAGAIN)
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

                    sleep(1);
                }
            }

        }
    }

    Close(epfd);
    Close(listen_fd);
}

int main()
{
    epoll_server_ET_nonblock();

    return 0;
}
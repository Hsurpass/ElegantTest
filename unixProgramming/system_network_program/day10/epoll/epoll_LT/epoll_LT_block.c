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
#define OPENMAX 10

void epoll_server_LT_block()
{
    int sockfd, connfd;
    struct epoll_event event, epev[10];
    int ret = -1; int nready = 0;
    char buf[MAXLINE]; char client_ip[INET_ADDRSTRLEN]; 
    memset(buf, 0, sizeof(buf));
    
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));

    // socket
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    printf("listen fd: %d\n", listen_fd);

    // 设置允许端口复用
    // int flag = 1;
    // int len = sizeof(flag);
    // ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &flag, len);
    // if (ret == -1)
    // {
    //     perr_exit("setsockopt");
    // }
    
    // bind
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(listen_fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    // listen
    Listen(listen_fd, 128);

    int epfd = epoll_create(OPENMAX);
    if (-1 == epfd)
    {
        perr_exit("epoll_create");
        exit(errno);
    }
    printf("epoll fd: %d\n", epfd);

    // event.events = EPOLLIN; // 监听读事件 默认水平触发
    event.events = EPOLLIN | EPOLLOUT; // 监听读写事件 默认水平触发
    event.data.fd = listen_fd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event);
    if (-1 == ret)
    {
        perr_exit("epoll_ctl");
        exit(errno);
    }
    
    socklen_t client_len;
    while (1)
    {
        printf("epoll_server wait...\n");
        nready = epoll_wait(epfd, epev/*就绪队列(数组) 传出参数*/, OPENMAX, -1);  // -1代表阻塞监听
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
            if ( !(epev[i].events & EPOLLIN) )
            {
                continue;
            }

            if (epev[i].data.fd == listen_fd)   // 监听文件描述符
            {
                client_len = sizeof(clientaddr);
                connfd = Accept(listen_fd, (struct sockaddr*)&clientaddr, &client_len);
                printf("epoll server: client fd = %d, client ip = %s, port = %d\n", connfd, inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));

                event.events = EPOLLIN;     // 只监听EPOLLIN事件
                event.data.fd = connfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);   // 有新的连接进来，把它挂到树上
                if (-1 == ret)
                {
                    perr_exit("epoll_ctl");
                }
            }
            else    // 其他套接字
            {
                sockfd = epev[i].data.fd;
                ret = Read(sockfd, buf, sizeof(buf));
                if (ret == 0)
                {
                    printf("client[fd:%d] close\n", epev[i].data.fd);
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL); // 写端关闭了，把这个fd从树上摘下来
                    if (ret < 0)
                    {
                        perr_exit("epoll_ctl");
                    }
                    Close(sockfd);
                }
                else if(ret == -1)
                {
                    perror("read==-1: ");
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL); // 写端关闭了，把这个fd从树上摘下来
                    if (ret < 0)
                    {
                        perr_exit("epoll_ctl");
                    }
                    Close(sockfd);
                }
                else
                {
                    buf[ret] = '\0';
                    printf("read: %s\n", buf);
                    
                    for (size_t j = 0; j < ret; j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(sockfd,buf,ret);
                }
            }
            
        }
        
    }

    Close(epfd);
    Close(listen_fd);
    exit(0);
}

int main()
{
    epoll_server_LT_block();

    return 0;
}
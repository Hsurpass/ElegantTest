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
#include "../../common/mysocket.h"

#define SERVERPORT 8888
#define OPEN_MAX 1024
#define MAXLINE 1024

void poll_server()
{
    int ret = 0;
    char buf[MAXLINE] = { 0 };
    char client_ip[INET_ADDRSTRLEN];
    memset(buf, 0x31, sizeof(buf));
    int maxi = 0;
    int connfd;
    int nready = 0;

    struct pollfd clientfd[OPEN_MAX];
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));

    // socket
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // bind
    Bind(listen_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // listen
    Listen(listen_fd, 128);
    // 设置需要监听的fd和事件
    clientfd[0].fd = listen_fd;
    clientfd[0].events = POLLRDNORM | POLLERR; // 普通数据可读 | 发生错误
    for (size_t i = 1; i < OPEN_MAX; i++)
    {
        clientfd[i].fd = -1;
    }

    maxi = 0;
    socklen_t client_len;
    while (1)
    {
        printf("poll_server listen...\n");
        nready = poll(clientfd, maxi + 1, -1);
        if (nready == -1)
        {
            perr_exit("poll");
        }
        printf("nready = %d\n", nready);

        if (clientfd[0].revents & (POLLRDNORM | POLLERR)) // 监听fd有数据可读
        {
            client_len = sizeof(clientaddr);
            connfd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
            printf("poll_server: client_connfd: %d, client_ip = %s, port = %d\n", connfd, inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));

            int i = 1;
            for (i = 1; i < OPEN_MAX; i++)
            {
                if (clientfd[i].fd < 0)
                {
                    clientfd[i].fd = connfd;
                    break;
                }
            }
            printf("i:%d\n", i);

            // 是否超过可监听的最大文件描述符
            if (i == OPEN_MAX)
            {
                printf("open too many connfd > 1024\n");
            }
            else
            {
                clientfd[i].events = POLLRDNORM | POLLERR;

                // reset maxi
                if (i > maxi)
                {
                    maxi = i;
                }
                printf("maxi:%d\n", maxi);

                // --nready
                if (--nready <= 0)
                {
                    continue;
                }
            }
        }

        // 其他套接字处理
        for (size_t i = 1; i <= maxi; i++)
        {
            if (clientfd[i].fd < 0)
            {
                continue;
            }

            // 判断传出参数中是否有需要处理的事件
            if (clientfd[i].revents & (POLLRDNORM | POLLERR))
            {
                ret = Read(clientfd[i].fd, buf, MAXLINE);
                if (ret == 0)
                {
                    printf("client[fd:%d] close\n", clientfd[i].fd);
                    close(clientfd[i].fd); // 如果写端关闭，则关闭此条连接
                    clientfd[i].fd = -1;
                }
                else
                {
                    buf[ret] = '\0';
                    printf("poll_server readData:%s, ret:%d\n", buf, ret);
                    for (int j = 0; j < ret; j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(clientfd[i].fd, buf, ret);
                }

                if (--nready <= 0)
                {
                    break;
                }
            }
        }
    }

    Close(listen_fd);
    exit(0);
}

int main()
{
    poll_server();

    return 0;
}
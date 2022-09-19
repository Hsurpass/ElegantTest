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
#define MAXLINE 1024

void select_server()
{
    int sockfd;
    int ret = 0;
    int nready = 0;
    int maxfd = -1;
    int clientfd[FD_SETSIZE];
    int maxi = -1;
    char client_ip[INET_ADDRSTRLEN];
    char buf[MAXLINE];
    memset(buf, 0, sizeof(buf));

    // 文件描述符集合 1024位
    fd_set rfdset, allfdset;
    FD_ZERO(&rfdset);
    FD_ZERO(&allfdset);

    // socket
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t server_len = sizeof(serveraddr);

    // bind
    Bind(listen_fd, (struct sockaddr *)&serveraddr, server_len);

    // listen
    Listen(listen_fd, 20);

    maxfd = listen_fd;
    for (size_t i = 0; i < FD_SETSIZE; i++)
    {
        clientfd[i] = -1;
    }

    // 把listenfd添加到监听文件描述符集合
    FD_SET(listen_fd, &allfdset);

    socklen_t client_len;
    int client_fd;
    int i = 0;
    while (1)
    {
        // 每次循环开始都必须重新设置监控文件描述符集合， 传入传出参数，select返回后会修改传入的文件描述符集合
        rfdset = allfdset;

        printf("select server listen...\n");
        nready = select(maxfd + 1, &rfdset, NULL, NULL, NULL);
        if (nready < 0)
        {
            perr_exit("select");
        }
        printf("nready = %d\n", nready);

        if (FD_ISSET(listen_fd, &rfdset)) // 如果listenfd可读
        {
            client_len = sizeof(clientaddr);
            client_fd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
            printf("accept client: client_fd=%d, client_ip = %s, port = %d\n", client_fd, inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));

            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (clientfd[i] < 0)
                {
                    clientfd[i] = client_fd;
                    break;
                }
            }
            printf("i = %d\n", i);

            // 判断是否超过了可监听的最大文件描述符
            if (i == FD_SETSIZE)
            {
                printf("too many client_fd...  > 1024\n");
                break;
            }
            else
            {
                // 把客户端的连接添加到fd_set
                FD_SET(client_fd, &allfdset);
                // 重置maxfd
                if (maxfd < client_fd)
                {
                    maxfd = client_fd;
                }
                printf("maxfd = %d\n", maxfd);

                // 重置最大下标
                if (i > maxi)
                {
                    maxi = i;
                }
                printf("maxi = %d\n", maxi);

                if (--nready == 0)
                {
                    continue;
                }
            }
        }

        // 其他套接字处理
        for (int k = 0; k <= maxi; k++) // 解复用
        {
            if ((sockfd = clientfd[k]) < 0)
            {
                continue;
            }

            // 判断sockfd是否有数据可读
            if (FD_ISSET(sockfd, &rfdset))
            {
                ret = Read(sockfd, buf, sizeof(buf));
                if (ret == 0) // 返回0说明写端关闭了
                {
                    printf("client[%s:%d] close\n", inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));

                    Close(sockfd);             /* 当client关闭链接时，服务器端也关闭对应链接*/
                    FD_CLR(sockfd, &allfdset); /* 解除select监控此文件描述符*/
                    clientfd[k] = -1;
                }
                else
                {
                    buf[ret] = '\0';
                    printf("select_server readData:%s, ret:%d\n", buf, ret);
                    
                    for (int j = 0; j < ret; j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(sockfd, buf, ret);
                    printf("buf = %s\n", buf);
                }

                // --nready
                if (--nready == 0)
                {
                    break;
                }
            }

            // 放在这里错误，一些没有可读事件的fd导致--nready
            // if (--nready == 0)
            // {
            //     break;
            // }
        }
    }

    Close(listen_fd);
    exit(1);
}

int main()
{
    select_server();

    return 0;
}
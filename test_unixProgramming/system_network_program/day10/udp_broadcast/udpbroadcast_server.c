#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERVERPORT 8000
#define SERVERADDR_LIMITEDBROADCAST "225.225.225.255"

void udp_server_broadcast()
{
    //printf("%d,%d\n",INET_ADDRSTRLEN,INET6_ADDRSTRLEN);16,46
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr =
        htonl(INADDR_ANY); // use 任何地址/SERVERADDR_DIRECTBROADCAST/SERVERADDR_LOOPDIRECTBROADCAST success
    // inet_pton(AF_INET, SERVERADDR_LIMITEDBROADCAST, &serveraddr.sin_addr.s_addr); // FAILED

    int ret = 0;
    // socket
    socklen_t serverlen = sizeof(serveraddr);
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // bind
    ret = bind(server_fd, (struct sockaddr*)&serveraddr, serverlen);
    if (ret == -1) {
        perror("bind");
        exit(errno);
    }
    printf("bind success\n");

    // 设置套接字层次允许使用广播
    // 使用SERVERADDR_LIMITEDBROADCAST时，不设置SO_BROADCAST也能接收。
    int flag = 1;
    ret = setsockopt(server_fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));
    if (-1 == ret) {
        perror("setsockopt");
    }

    char buf[32], client_ip[16];
    memset(buf, 0x31, sizeof(buf));
    socklen_t clientlen = sizeof(clientaddr);
    int count = 0;
    printf("recvfrom...\n");
    while (1) {
        ret = recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&clientaddr, &clientlen);
        if (ret == -1) {
            perror("recvfrom");
            exit(errno);
        }
        else {
            buf[ret] = '\0';
            printf("udp_server recv: buf = %s, ret = %d, clientaddr = %s, clientport = %d\n",
                   buf,
                   ret,
                   inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)),
                   ntohs(clientaddr.sin_port));
        }

        memset(buf, 0x31, sizeof(buf));
        sprintf(buf, "WORLD%d", count++);
        // ret = send(server_fd, buf, sizeof(buf), 0); // error 必须使用sendto指定对端地址
        // if (ret == -1) {
        //     perror("send");
        //     exit(errno);
        // }
        // else {
        //     printf("server send: buf = %s,ret = %d\n", buf, ret);
        // }

        ret = sendto(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&clientaddr, clientlen);
        if (ret == -1) {
            perror("sendto");
            exit(errno);
        }
        else {
            printf("server sendto: buf = %s,ret = %d\n", buf, ret);
        }
    }

    close(server_fd);
}

int main()
{
    udp_server_broadcast();

    return 0;
}
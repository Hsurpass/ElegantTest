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
#define SERVERADDR_DIRECTBROADCAST "172.23.127.255"
#define SERVERADDR_LIMITEDBROADCAST "225.225.225.255"

void udp_client_broadcast()
{
    //printf("%d, %d\n", INET_ADDRSTRLEN, INET6_ADDRSTRLEN);16,46

    int ret = 0;
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    // inet_pton(AF_INET, SERVERADDR_DIRECTBROADCAST, &serveraddr.sin_addr.s_addr);
    inet_pton(AF_INET, SERVERADDR_LIMITEDBROADCAST, &serveraddr.sin_addr.s_addr);

    // socket
    socklen_t serverlen = sizeof(serveraddr);
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // 设置套接字层次允许使用广播
    int flag = 1;
    ret = setsockopt(client_fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));
    if (-1 == ret)
    {
        perror("setsockopt");
    }
    
    int i = 0;
    char buf[32];
    memset(buf, 0x31, sizeof(buf));

    printf("sendto...\n");
    while (1)
    {
        sprintf(buf, "DATA%d", ++i);
        ret = sendto(client_fd, buf, strlen(buf), 0, (struct sockaddr *)&serveraddr, serverlen);
        if (ret == -1)
        {
            perror("sendto");
            exit(errno);
        }
        else
        {
            printf("client sendto: buf = %s,ret = %d\n", buf, ret);
        }
        sleep(1);
    }

    close(client_fd);
}

int main()
{
    udp_client_broadcast();

    return 0;
}
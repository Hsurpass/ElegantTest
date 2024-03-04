#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>

/*
客户端和服务端均在同一台主机上，并且客户端向 255.255.255.255 发送广播消息时，服务端通常是无法接收到这个广播消息的。
这是因为在同一台主机上，操作系统会阻止从一个网络接口发送的广播消息被同一台主机上的另一个网络接口接收。

如果您希望测试广播消息的功能，可以尝试在不同的主机上运行客户端和服务端程序，然后客户端向 255.255.255.255 发送广播消息，
服务端应该能够接收到这个广播消息。这样可以模拟真实的网络环境，其中客户端和服务端位于不同的主机上。

如果您需要在同一台主机上测试广播消息的功能，可以考虑使用不同的端口或者不同的 IP 地址来模拟客户端和服务端。
这样客户端向 255.255.255.255 发送广播消息时，服务端可以监听特定的端口或者特定的 IP 地址来接收这个广播消息。

right or wrong?
*/

#define SERVERPORT 8000
#define SERVERADDR_DIRECTBROADCAST "172.25.79.255"
#define SERVERADDR_LIMITEDBROADCAST "225.225.225.255"
#define SERVERADDR_LOOPDIRECTBROADCAST "127.255.255.255"

void udp_client_broadcast()
{
    //printf("%d, %d\n", INET_ADDRSTRLEN, INET6_ADDRSTRLEN);16,46

    int ret = 0;
    struct sockaddr_in serveraddr, remoteaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&remoteaddr, sizeof(remoteaddr));
    socklen_t serverlen = sizeof(serveraddr);
    socklen_t remotelen = sizeof(remoteaddr);
    char remote_ip[32] = {0};

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    // inet_pton(AF_INET, SERVERADDR_LIMITEDBROADCAST, &serveraddr.sin_addr.s_addr); // FAILED
    // inet_pton(AF_INET, SERVERADDR_DIRECTBROADCAST, &serveraddr.sin_addr.s_addr);             // SUCCESS
    inet_pton(AF_INET, SERVERADDR_LOOPDIRECTBROADCAST, &serveraddr.sin_addr.s_addr); // SUCCESS

    // socket
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // 设置套接字层次允许使用广播
    int flag = 1;
    ret = setsockopt(client_fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));
    if (-1 == ret) {
        perror("setsockopt");
    }

    int i = 0;
    char buf[32];
    memset(buf, 0x31, sizeof(buf));

    printf("sendto...\n");
    while (i < 3) {
        sprintf(buf, "HELLO%d", ++i);
        ret = sendto(client_fd, buf, strlen(buf), 0, (struct sockaddr*)&serveraddr, serverlen);
        if (ret == -1) {
            perror("sendto");
            exit(errno);
        }
        else {
            printf("client sendto: buf = %s,ret = %d\n", buf, ret);
        }
        memset(buf, 0x31, sizeof(buf));

        printf("client wait recv...\n");
        recvfrom(client_fd, buf, sizeof(buf), 0, (struct sockaddr*)&remoteaddr, &remotelen);
        printf("udp_client recv: buf = %s, ret = %d, remoteaddr = %s, remoteport = %d\n",
               buf,
               ret,
               inet_ntop(AF_INET, &remoteaddr.sin_addr.s_addr, remote_ip, sizeof(remote_ip)),
               ntohs(remoteaddr.sin_port));

        sleep(1);
    }

    close(client_fd);
}

int main()
{
    udp_client_broadcast();

    return 0;
}
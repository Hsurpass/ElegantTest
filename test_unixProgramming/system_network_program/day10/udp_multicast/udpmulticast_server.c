#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>

#define MULTICAST_PORT 8888
//#define MULTICAST_GROUP "224.0.0.10"
#define MULTICAST_GROUP "224.224.224.245"

void udp_server_multicast()
{
    //printf("%d,%d\n",INET_ADDRSTRLEN,INET6_ADDRSTRLEN);16,46
    struct sockaddr_in serveraddr, clientaddr, multicastaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));
    bzero(&multicastaddr, sizeof(multicastaddr));
    int ret = 0;

    // 设置组播地址
    memset(&multicastaddr, 0, sizeof(multicastaddr));
    multicastaddr.sin_family = AF_INET;
    multicastaddr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    multicastaddr.sin_port = htons(MULTICAST_PORT);
    socklen_t multicastaddrlen = sizeof(multicastaddr);

    // server 地址
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(MULTICAST_PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // use 任何地址
    socklen_t serverlen = sizeof(serveraddr);

    // socket
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // bind
    ret = bind(server_fd, (struct sockaddr*)&serveraddr, serverlen);
    // ret = bind(server_fd, (struct sockaddr*)&multicastaddr, multicastaddrlen); // error
    if (ret == -1) {
        perror("bind");
        exit(errno);
    }
    printf("bind success\n");

    // 加入组播组
    /*
     * int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
     * param:
     *      level:
     *          * IPPROTO_IP: 表示设置的选项属于 IP 层级的套接字选项。
     *          
     *      optname
     *          * IP_MULTICAST_LOOP 支持多播数据回送
     *          * IP_ADD_MEMBERSHIP 加入多播组
     *          * IP_DROP_MEMBERSHIP 离开多播组
     *      optval
     *          * IP_MULTICAST_LOOP 选项对应传入 unsigned int 来确认是否支持多播数据回送
     *          * IP_ADD_MEMBERSHIP 传入 ip_mreq
     *          * IP_DROP_MEMBERSHIP 传入 ip_mreq
    */
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP); // 组播地址, 类似于 群号
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);    // 将监听地址添加到组播组中, 类似于 成员号
    if (setsockopt(server_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
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
    udp_server_multicast();

    return 0;
}

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
#define MULTICAST_GROUP "224.0.0.10"

void udp_client_multicast()
{
    //printf("%d, %d\n", INET_ADDRSTRLEN, INET6_ADDRSTRLEN);16,46

    int ret = 0;
    struct sockaddr_in remoteaddr, multicast_addr;
    bzero(&remoteaddr, sizeof(remoteaddr));
    socklen_t remotelen = sizeof(remoteaddr);
    char remote_ip[32] = {0};

    // 设置组播地址
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    multicast_addr.sin_port = htons(MULTICAST_PORT);

    // socket
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    int i = 0;
    char buf[32];
    memset(buf, 0x31, sizeof(buf));
    printf("sendto...\n");
    while (i < 3) {
        sprintf(buf, "HELLO%d", ++i);
        ret = sendto(client_fd, buf, strlen(buf), 0, (struct sockaddr*)&multicast_addr, sizeof(multicast_addr));
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
    udp_client_multicast();

    return 0;
}
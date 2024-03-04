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
// #define SERVERADDR_UNICAST "127.0.0.1"
// #define SERVERADDR_UNICAST "172.25.75.118"

void udp_client_unicast()
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
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, SERVERADDR_UNICAST, &serveraddr.sin_addr.s_addr);
    // inet_pton(AF_INET, SERVERADDR_UNICAST, &serveraddr.sin_addr.s_addr);

    // socket
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);

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
        printf("udp_client recv: buf = %s, ret = %d, clientaddr = %s, clientport = %d\n",
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
    udp_client_unicast();

    return 0;
}
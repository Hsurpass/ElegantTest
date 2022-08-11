#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/un.h>

#define SERVERPORT 8000

void udp_server()
{
    //printf("%d,%d\n",INET_ADDRSTRLEN,INET6_ADDRSTRLEN);16,46
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&serveraddr, sizeof(clientaddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t serverlen = sizeof(serveraddr);
    // socket
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    int ret = 0;
    // bind
    ret = bind(server_fd, (struct sockaddr *)&serveraddr, serverlen);
    if (ret == -1)
    {
        perror("bind");
        exit(errno);
    }
    printf("bind success\n");
    
    char buf[32], client_ip[16];
    memset(buf, 0x31, sizeof(buf));
    socklen_t clientlen;
    
    // recvfrom
    printf("recvfrom...\n");
    while (1)
    {
        clientlen = sizeof(clientaddr);
        ret = recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, &clientlen);
        if (ret == -1)
        {
            perror("recvfrom");
            exit(errno);
        }
        else
        {
            buf[ret] = '\0';
            printf("udp server recv: buf = %s, ret = %d, clientaddr = %s, clientport = %d\n",
            buf, ret, inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)),
            ntohs(clientaddr.sin_port));
        }
    }

    close(server_fd);
}

int main()
{
    udp_server();

    return 0;
}
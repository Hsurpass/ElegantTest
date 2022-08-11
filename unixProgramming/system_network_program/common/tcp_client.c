#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include "mysocket.h"

#define SERVERADDR "127.0.0.1"
#define SERVERPORT 8888

void sigpipe(int sig)
{
    printf("sig=%d\n",sig);
}

void sighandle(int sig)
{
    printf("signal = %d\n",sig);
}

void tcp_client()
{
    // for (size_t i = 0; i < 32; i++)
    // {
    //     signal(i,sighandle);    
    // }
    signal(SIGINT, sighandle);   
    signal(SIGPIPE, sigpipe);   

    // struct sigaction act;
    // // act.sa_flags = SA_RESTART;
    // act.sa_handler = sighandle;
    // __sigemptyset(&act.sa_mask);
    // sigaction(SIGINT, &act, NULL);     

    char buf[64] = { 0 };
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERADDR, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(SERVERPORT);

    socklen_t server_len = sizeof(serveraddr);
    int ret = 0;
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    printf("connnect...\n");
    Connect(sockfd, (struct sockaddr *)&serveraddr, server_len);
    printf("connect success\n");
    int i = 0;
    int count = 0;

#if 1

#if 0
    int k = 0;
    while (k++ < 10)    // 写十次后停止
#endif    
#if 1
    while (1)
#endif
    {
        sprintf(buf, "data%d", ++i);
        ret = write(sockfd, buf, strlen(buf));
        if (ret == -1)
        {
            perror("write");
            close(sockfd);
            exit(errno);
        }
        else
        {
            count += ret;
            printf("client write: buf = %s, ret = %d,count = %d\n",buf,ret,count);
        }
        
        ret = Read(sockfd, buf, sizeof(buf));
        buf[ret] = '\n';

        // printf("%s, %d\n", buf, ret);
        write(STDOUT_FILENO, buf, ret + 1);
        
        sleep(1);
    }
#endif
#if 0
    while(fgets(buf, sizeof(buf), stdin) != NULL)
    {
        ret = Write(sockfd, buf, strlen(buf));
        if (ret == -1)
        {
            perror("write");
            break;
        }

        ret = Read(sockfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        
    }

    close(sockfd);
    exit(0);
#endif

}

int main()
{
    tcp_client();

    return 0;
}
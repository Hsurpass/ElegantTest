#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERVERPORT 8888

void sighandle(int sig)
{
    printf("sig:%d\n", sig);
    // sleep(3);
}

void tcp_server()
{
#if 0
    signal(SIGINT, sighandle);    // signal 相当于 SA_RESTART
#endif
#if 1
    struct sigaction act;
    // act.sa_flags = 0;
    act.sa_flags = SA_RESTART;  // 设置为SA_RESTART 会重启被打断的 system call,(read or accept)
    act.sa_handler = sighandle;
    sigemptyset(&act.sa_mask);
    // sigaddset(&act.sa_mask, SIGQUIT);   // 只会临时性的去屏蔽SIGQUIT，等信号处理函数处理完后，再来处理SIGQUIT这个信号
    sigaction(SIGINT, &act, NULL);
#endif

    // unsigned int serbuf;
    // char serip[] = "192.168.226.129";
    char buf[64];
    memset(buf, 0x31, sizeof(buf));
    char clientip[16];
    memset(clientip, 0x31, sizeof(clientip));
    
    int ret = 0;
    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, serip, &serbuf);
    // server_addr.sin_addr.s_addr = serbuf;
    server_addr.sin_port = htons(SERVERPORT);

    // socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    // bind
    ret = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == -1)
    {
        perror("bind");
        exit(0);
    }
    // listen
    ret = listen(listen_fd, 128);
    if (-1 == ret)
    {
        perror("listen");
        exit(1);
    }

    socklen_t clientaddr_len = sizeof(client_addr);
    while (1)
    {
        // clientaddr_len = sizeof(client_addr);

        // accept可以被信号打断
        printf("listen port:%d ...\n", SERVERPORT);
        int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
        if (-1 == client_fd)
        {
            perror("accept");
            continue;
            // exit(2);
        }
        printf("accept, client_fd = %d, client_ip = %s, client_port = %d\n",
               client_fd, inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clientip, sizeof(clientip)), 
               ntohs(client_addr.sin_port));

        // read       
        while (1)
        {
            // read 可以被信号打断
            ret = read(client_fd, buf, sizeof(buf));    // read socket和 read 管道是一样的
            if (-1 == ret)
            {
                perror("read");
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    perror("read");
                    break;
                }
            }
            else if (ret == 0)
            {
                printf("client close\n");
                break;
            }
            else
            {
                buf[ret] = '\0';
                printf("server read: buf = %s,ret = %d\n", buf, ret);
            }
            // sleep(1);
        }

        close(client_fd);
    }

    close(listen_fd);
}

int main()
{
    tcp_server();
    
    return 0;
}
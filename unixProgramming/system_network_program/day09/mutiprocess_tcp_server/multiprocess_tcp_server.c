#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include "../../common/mysocket.h"

#define SERVERPORT 8888

// 父进程不用处理SIGPIPE信号， 子进程可以选择处理，也可以选择不处理(默认就退出了)
void sigPipe(int sig)
{
    printf("signal = %d\n",sig);
}

void sigCHILD(int sig)
{
    pid_t childpid;
    // 使用while是为了避免多个子进程同时退出，而信号处理函数只处理一次的情况
    while((childpid = waitpid(-1,NULL,WNOHANG)) > 0)    
    {
        printf("server recycle child process id:%d, sig = %d\n", childpid, sig);
    }
}

void sighandle(int sig)
{
    printf("sig:%d\n", sig);
}

void mutiProcessTcpServer()
{
    // 子进程退出会发送SIGCHILD 信号
    signal(SIGCHLD, sigCHILD);

    struct sigaction act;
    act.sa_flags = SA_RESTART;
    act.sa_handler = sighandle;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);

    char buf[64];
    memset(buf, 0x31, sizeof(buf));
    char clientip[16];
    memset(clientip, 0x31, sizeof(clientip));
    int ret = 0;
    
    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVERPORT);

    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    Listen(listen_fd, 128);

    socklen_t clientaddr_len;
    while (1)
    {
        clientaddr_len = sizeof(client_addr);
        printf("accept...\n");
        int client_fd = Accept(listen_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
        
        pid_t pid = fork();                
        
        if(pid == 0)
        {
            // 引用计数减一
            close(listen_fd);

            printf("server:child_process id = %d, client_fd = %d,client_ip = %s,client_port = %d\n",
               getpid(),client_fd, inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clientip, sizeof(clientip)), ntohs(client_addr.sin_port));
            while (1)
            {
                ret = Read(client_fd, buf, sizeof(buf));
                if (ret == 0)
                {
                    printf("client close\n");
                    break;
                }
                /*else
                {
                    buf[ret] = '\0';
                    printf("server childid[%d] read: buf = %s,ret = %d\n", getpid(),buf, ret);
                }*/
                else
                {
                    for (size_t i = 0; i < ret; i++)
                    {
                        buf[i] = toupper(buf[i]);
                    }
                    ret = Write(client_fd, buf, ret);
                    if (ret == -1)
                    {
                        perror("write");
                        break;
                    }
                }
                // sleep(1);
            }

            Close(client_fd);
            exit(0);
        }
        else if(pid > 0)
        {
            // 引用计数减一
            close(client_fd);          
        }
        else
        {
            perr_exit("fork");
        }
    }

    close(listen_fd);
}

int main()
{   
    mutiProcessTcpServer();

    return 0;
}
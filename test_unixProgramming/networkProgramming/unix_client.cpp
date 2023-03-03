#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <errno.h>

#include <iostream>
#include <string>
using namespace std;

const int MAX_LINE = 2048;

int main(int argc, char **argv)
{
    /*声明套接字和链接服务器地址*/
    int sockfd;
    /*声明服务器地址和客户链接地址*/
    struct sockaddr_un server_addr;
    string tmpAddr = getenv("HOME");
    tmpAddr += "/test.sock";
    cout << "destAddr:" << tmpAddr << endl;
    const char* destAddr = tmpAddr.c_str();
    // const char *destAddr = "~/test.sock";    // error

    /*(1) 创建套接字*/
    if ((sockfd = socket(PF_UNIX, SOCK_STREAM, 0)) == -1)
    {    
        perror("socket");
        return -1;
    }

    /*(2) 设置链接服务器地址结构*/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, destAddr);
    /*  (3) 发送链接服务器请求  */
    int status = connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr_un));
    if (status == -1)
    {
        perror("connect");
        close(sockfd);
        return -1;
    }
    char buf[MAX_LINE];
    while (1)
    {
        /* code */
        memset(buf, '\0', sizeof(buf));
        int len = read(sockfd, buf, sizeof(buf) - 1);
        if (len == 0)
        {
            printf("server close..\n");
            return 0;
        }
        printf("recv from server:%s", buf);

        memset(buf, '\0', sizeof(buf));
        printf("please enter:\n");
        len = read(0, buf, sizeof(buf) - 1);
        if (len > 0)
        {
            if (strcmp(buf, "quit") == 0)
            {
                printf("quit\n");
                break;
            }
            buf[len - 1] = '\0';
            write(sockfd, buf, strlen(buf));
        }
    }
    close(sockfd);
    return 0;
}

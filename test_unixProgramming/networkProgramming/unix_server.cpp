#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <errno.h>
#include <iostream>
#include <string>
using namespace std;

#define MAX_BUFF 1024

int unix_server()
{
    /*声明服务器地址和客户链接地址*/
    struct sockaddr_un server_addr, client_addr;
    struct stat st_sock;
    string tmpAddr = getenv("HOME");
    tmpAddr += "/test.sock";
    cout << "destAddr:" << tmpAddr << endl;
    const char* srcAddr = tmpAddr.c_str();
    // const char *srcAddr = "test.sock";   //error

    if (stat(srcAddr, &st_sock) != -1)
    {
        // 如果此文件已存在,且是一个SOCKET文件,则删除
        if (S_ISSOCK(st_sock.st_mode))
            unlink(srcAddr);
    }

    /*声明服务器监听套接字和客户端链接套接字*/
    int listen_fd, connect_fd;

    /*(1) 初始化监听套接字listenfd*/
    if ((listen_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
        perror("socket");
        return -1;
    }

    /*(2) 设置服务器 sockaddr_un 结构*/
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, srcAddr);

    /*(3) 绑定套接字和端口*/    //bind函数执行完就创建了test.sock
    if (bind(listen_fd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind");
        close(listen_fd);
        return -1;
    }
#if 1

    /*(4) 监听客户请求*/
    if (listen(listen_fd, 4) == -1)
    {
        perror("listen");
        close(listen_fd);
        return -1;
    }

    /*(5) 接受客户请求*/
    for (;;)
    {
        socklen_t client_len = sizeof(client_addr);
        connect_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
        if (connect_fd < 0)
        {
            perror("accept error");
            return 0;
        }
        /*声明缓冲区,向客户端发送数据*/
        char buff[MAX_BUFF] = "hello\n";
        if (-1 == write(connect_fd, buff, strlen(buff)))
        {
            perror("Send error\n");
            return 0;
        }
        printf("Send success...\n");
        /*清空缓冲区,阻塞等待读取客户端发过来的数据*/
        memset(buff, '\0', sizeof(buff));
        if (-1 == read(connect_fd, buff, MAX_BUFF))
        {
            perror("read error\n");
            return 0;
        }
        write(1, buff, strlen(buff));
        close(connect_fd);
    }
 
#endif
    close(listen_fd);
    return 0;
}

int main()
{
    unix_server();

    return 0;
}
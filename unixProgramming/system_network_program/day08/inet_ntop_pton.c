#include <stdio.h>
#include <arpa/inet.h>

void test_inet_pton()
{
    char buf[] = "192.168.1.255";
    unsigned int n_ip; 
    inet_pton(AF_INET, buf, &n_ip); // 点分十进制转换成网络字节序
    printf("buf = %s, n_ip = %x\n", buf, n_ip); //0xff01a8c0
}

void test_inet_ntop()
{
    char ip[16];
    unsigned int n_ip = 0xff01a8c0; // "192.168.1.255"

    inet_ntop(AF_INET, &n_ip, ip, sizeof(ip));
    printf("ip = %s, n_ip = %x\n", ip, n_ip);

    unsigned int h_ip = 0xc0a801ff;
    printf("htonl = %x\n", htonl(h_ip));    // 0xff01a8c0
    printf("ntohl = %x\n", ntohl(n_ip));    // 0xc0a801ff
}

int main()
{
    // test_inet_pton();
    test_inet_ntop();
    
    return 0;
}

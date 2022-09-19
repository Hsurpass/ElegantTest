#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

void ip2host()
{
    char buf[1024];
    int i = 0;
    char ip[INET_ADDRSTRLEN] = "220.181.38.150";
    struct hostent *hent;
    
    hent = gethostbyaddr(ip, sizeof(ip), AF_INET);
    if (hent != NULL)
    {
        printf("h_name:%s\n", hent->h_name);

        i = 0;
        while (hent->h_aliases[i] != NULL)
        {
            printf("alias:%s\n", hent->h_aliases[i] );
            i++;
        }
        printf("hostaddrtype:%d\n", hent->h_addrtype);
        printf("hostlength:%d\n", hent->h_length);
        i = 0;
        while (hent->h_addr_list[i] != NULL)
        {
            printf("addr_list:%s\n", inet_ntop(AF_INET, hent->h_addr_list[i], buf, sizeof(buf)) );
            i++;
        }
        
    }
    
}

void host2ip()
{
    char buf[INET_ADDRSTRLEN];
    const char *hostname = "www.baidu.com";
    // const char *hostname = "w.mapbar.com";
    // const char *hostname = "w.autoai.com";
    // const char *hostname = "navicore.mapbar.com";
    // const char *hostname = "svr.navicore.cn";

    struct hostent *hent = NULL;
    hent = gethostbyname(hostname);

    int i = 0;
    if (hent != NULL)
    {
        printf("h_name:%s\n", hent->h_name);    // 主机的规范名
        printf("hostaddrtype:%d\n", hent->h_addrtype);  // 主机ip地址的类型， ipv4 ipv6
        printf("hostlength:%d\n", hent->h_length);  // 主机ip地址的长度

        i = 0;
        while (hent->h_aliases[i] != NULL)  // 主机的别名，可能有多个别名
        {
            printf("alias:%s\n", hent->h_aliases[i]);
            i++;
        }

        i = 0;
        while (hent->h_addr_list[i] != NULL)    // 主机的ip地址， 可能有多个ip
        {
            printf("addr_list: %s\n", inet_ntop(AF_INET, hent->h_addr_list[i], buf, sizeof(buf)) );
            i++;
        }
        
    }
}

int main()
{
    host2ip();
    printf("--------------------------\n");
    ip2host();

    return 0;
}


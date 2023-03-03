#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <iostream>

// using namespace std;

/* 
    If an option was successfully found, then getopt() returns the option character.  
    If all command-line options have been parsed, then getopt() returns -1.  
    If getopt() encounters an option character that was not in optstring, then '?' is returned.  
    If getopt() encounters an option with a missing argument, 
    then the return value depends on the first character in optstring:
    if it is ':', then ':' is returned; otherwise '?' is returned.
    
    功能：处理以'-'开头的命令行参数
    optstring:  "a?bc:d::"
        单个字符：表示选项，后面不跟参数。
        单个字符后接一个冒号：表示选项后必须跟一个参数。参数紧跟在选项后或以空格隔开。参数指针赋给optarg
        单个字符后接两个冒号：表示选项后可以跟一个参数也可以不跟。如果跟一个参数，该参数必须紧跟在选项后不能以空格隔开。参数指针赋给optarg。
    返回值：
        如果optstring中的字符被找到，则返回这个字符。switch...case
        如果所有命令行选项都已经解析，则返回-1。退出while循环条件
        如果命令行选项的字符不在optstring中则返回'?'
        如果某个命令行选项缺少参数，它的返回值依赖optstring的第一个字符，如果第一个字符是':'则返回':'。否则返回'?'
    optind: 初始值为1，指向argv中下一个待处理值得下标。可以把它重置为1，重新开始扫描。
*/

void test_getopt01(int argc, char **argv)
{
    char *nvalue = NULL;
    int c = 0;
    int tvalue = -1;

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]:%s\n", i, argv[i]);
    }
    printf("optind:%d\n", optind);


    // while ((c = getopt(argc, argv, "n::tj:C:")) != -1)
    // while ((c = getopt(argc, argv, ":n:t:j:C:")) != -1)
    // while ((c = getopt(argc, argv, ":n:t:")) != -1)
    while ((c = getopt(argc, argv, "ntj::C:")) != -1)
    {
        switch (c)
        {
        case 'n':
            nvalue = optarg;
            printf("nvalue:%s\n", nvalue);
            printf("optarg:%s\n", optarg);
            printf("optind:%d\n", optind);
            break;
        case 't':
            if(optarg != NULL)
            {
                tvalue = strtol(optarg, NULL, 10);
            }
            else{
                printf("optarg is NULL\n");
            }
            printf("optind:%d\n", optind);
            break;
        case 'j':
            printf("case j | %s\n", optarg);
            printf("optind:%d\n", optind);
            break;
        case 'C':
            printf("case C | %s\n", optarg);
            printf("optind:%d\n", optind);
            break;
        case ':':
            printf("case : | %c\n", c); // 如果某个命令行选项缺少参数, optstring第一个字符是':' return':'; 第一个字符不是':', return '?'
            printf("optind:%d\n", optind);
            break;
        default:
            printf("default: %c\n", c);
            printf("optind:%d\n", optind);
        }
    }
    printf("-------------------------\n");
    printf("optind:%d\n", optind);
}

void test_getopt2(int argc, char **argv)
{
    char *fcgi_app = NULL, *changeroot = NULL, *username = NULL,
         *groupname = NULL, *unixsocket = NULL, *pid_file = NULL,
         *sockusername = NULL, *sockgroupname = NULL, *fcgi_dir = NULL,
         *addr = NULL;

    char *endptr = NULL;
    unsigned short port = 0;
    int child_count = -1;
    int fork_count = 1;
    int backlog = 1024;
    int sockbeforechroot = 0;
    mode_t sockmode;
    int nofork = 0;

    int o;
    while (-1 != (o = getopt(argc, argv, "c:d:f:g:?hna:p:b:u:vC:F:s:P:U:G:M:S")))
    {
        switch (o)
        {
        case 'f':
            fcgi_app = optarg;
            break;
        case 'd':
            fcgi_dir = optarg;
            break;
        case 'a':
            addr = optarg; /* ip addr */
            break;
        case 'p':
            port = strtol(optarg, &endptr, 10); /* port */
            if (*endptr)
            {
                fprintf(stderr, "spawn-fcgi: invalid port: %u\n", (unsigned int)port);
                return;
            }
            break;
        case 'C':
            child_count = strtol(optarg, NULL, 10); /*  */
            break;
        case 'F':
            fork_count = strtol(optarg, NULL, 10); /*  */
            break;
        case 'b':
            backlog = strtol(optarg, NULL, 10); /*  */
            break;
        case 's':
            unixsocket = optarg; /* unix-domain socket */
            break;
        case 'c':
        {
            changeroot = optarg;
        } /* chroot() */
        break;
        case 'u':
        {
            username = optarg;
        } /* set user */
        break;
        case 'g':
        {
            groupname = optarg;
        } /* set group */
        break;
        case 'U':
        {
            sockusername = optarg;
        } /* set socket user */
        break;
        case 'G':
        {
            sockgroupname = optarg;
        } /* set socket group */
        break;
        case 'S':
        {
            sockbeforechroot = 1;
        } /* open socket before chroot() */
        break;
        case 'M':
            sockmode = strtol(optarg, NULL, 8); /* set socket mode */
            break;
        case 'n':
            nofork = 1;
            break;
        case 'P':
            pid_file = optarg; /* PID file */
            break;
        case 'v':
            return;
        case '?':
        case 'h':
            return;
        default:
            return;
        }
    }
}

int main(int argc, char **argv)
{
    test_getopt01(argc, argv);

    return 0;
}
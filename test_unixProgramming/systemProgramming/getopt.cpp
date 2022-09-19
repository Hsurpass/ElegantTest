#include <unistd.h>
#include <iostream>

using namespace std;

/* 
    If an option was successfully found, then getopt() returns the option character.  
    If all command-line options have been parsed, then getopt() returns -1.  
    If getopt() encounters an option character that was not in optstring, then '?' is returned.  
    If getopt() encounters an option with a missing argument, 
    then the return value depends on the first character in optstring:
    if it is ':', then ':' is returned; otherwise '?' is returned.
*/

void test_getopt01(int argc, char **argv)
{
    char *nvalue = "World";
    int c = 0;
    int tvalue = -1;

#if 0
    while ((c = getopt(argc, argv, "n:tjC:")) != -1)
#endif
#if 1
    while ((c = getopt(argc, argv, "ntjC:")) != -1)
#endif
#if 0
    while ((c = getopt(argc, argv, ":n:t:")) != -1)
#endif
    {
        switch (c)
        {
        case 'n':
            nvalue = optarg;
            break;
        case 't':
            tvalue = atoi(optarg);
            break;
        case 'j':
            printf("case j | %s\n", optarg);
            break;
        case 'C':
            printf("case C | %s\n", optarg);
            break;
        case ':':
            printf("case : | %c\n", c); // 如果是 -n, optstring第一个字符是':' return':'; 第一个字符不是':', return '?'
            break;
        default:
            printf("default: %c\n", c);
        }

        printf("optind:%d, argc:%d\n", optind, argc);

        for (int i = 0; i < tvalue; i++)
        {
            cout << "[" << i << "] Hello " << nvalue << "!\n";
        }
    }
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
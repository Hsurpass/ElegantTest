#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

char buf0[] = "1 2 3 4 5 6";
char buf1[] = "a b c d e f";

#if 1
void sighandle(int sig)
{
    char *p, *psave;
    p = strtok_r(buf1, " ", &psave); 
    while (p)
    {
        printf("%s\n", p);
        p = strtok_r(psave, " ", &psave);   // a b c d e f
        sleep(1);
    }
}
int main()
{
    signal(SIGINT, sighandle);
    char *p, *psave;
    p = strtok_r(buf0, " ", &psave);   
    while (p)
    {
        printf("%s\n", p);
        p = strtok_r(psave, " ", &psave);   // 1 2 3 4 5 6
        sleep(1);
    }

    return 0;
}

#endif

#if 0
void sighandle(int sig)
{
    char *p = strtok(buf1, " "); 
}
int main()
{
    signal(SIGINT, sighandle);
    char *p = strtok(buf0, " ");
    while (p)
    {
        printf("%s\n", p);
        p = strtok(NULL, " ");
        sleep(1);
    }
    return 0;
}
#endif

#if 0
static char buf[] = "hello world good book";
void sig_handle(int sig)
{
    strtok(NULL, " ");
} 

int main(int argc, char** argv)
{
    signal(SIGINT, sig_handle);
    printf("%s\n", strtok(buf, " "));
    printf("%s\n", strtok(NULL, " "));
    sleep(5); //可以被信号打断，返回剩余的时间，想想看这个函数应该怎么调用
    printf("%s\n", strtok(NULL, " "));
    
    return 0;
}
#endif
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void sig_handle(int sig)
{
    // sigset_t sig_mask;
    // __sigemptyset(&sig_mask);
    // __sigaddset(&sig_mask,SIGQUIT);
    // sigprocmask(SIG_BLOCK,&sig_mask,NULL);

    printf("sig_handle:%d\n", sig);
    sleep(2);
    printf("sig_handle end\n");

    // sigprocmask(SIG_UNBLOCK,&sig_mask,NULL);
}

void test_signal01()
{
    signal(SIGINT, sig_handle);

    while (1)
    {
        sleep(1);
    }
    
}

void test_signal02()
{
    // signal 函数相当于默认设置了SA_RESTART， 也会重启打断的函数
    signal(SIGINT, sig_handle); 

    char buf[32];
    int ret;
    ret = read(STDIN_FILENO, buf, sizeof(buf));
    if (-1 == ret)
    {
        if(errno == EINTR)
        {
            perror("read");
        }
        else
        {
            exit(0);
        }
        
    }
}

int main()
{
    // test_signal01();
    test_signal02();

    return 0;
}

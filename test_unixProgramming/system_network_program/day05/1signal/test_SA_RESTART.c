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
    sleep(3);
    printf("sig_handle end\n");

    // sigprocmask(SIG_UNBLOCK,&sig_mask,NULL);
}

void test_SA_RESTART()
{
    struct sigaction sig_act;
    // sig_act.sa_flags = 0; 
    sig_act.sa_flags = SA_RESTART;  // set SA_RESART can restart interrupted system call
    sig_act.sa_handler = sig_handle;
    sigemptyset(&sig_act.sa_mask);
    sigaddset(&sig_act.sa_mask, SIGQUIT);
    sigaction(SIGINT, &sig_act, NULL);

    int ret;
    char buf[32] = { 0 };
    ret = read(STDIN_FILENO, buf, sizeof(buf));
    if(-1 == ret)
    {
        perror("read");
        if(errno == EINTR)
        {
            perror("read");
        }
        else
        {
            exit(0);
        }
    }
    else 
    {
        printf("%s\n", buf);
    }
}

int main()
{
    test_SA_RESTART();

    return 0;
}
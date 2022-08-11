#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

static void print_signalset(sigset_t *sig_mask)
{
    int i = 0;
    for(i = 1; i < 32; i++)
    {
        if (sigismember(sig_mask, i) == 1)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    putchar(10);
}

void sig_handle(int sig)
{
    // sigset_t sig_mask, oldProcMask;
    // __sigemptyset(&sig_mask);
    // __sigaddset(&sig_mask,SIGQUIT);
    // sigprocmask(SIG_BLOCK,&sig_mask,NULL);
    // sigprocmask(SIG_UNBLOCK, NULL, &oldProcMask);
    // print_signalset(&oldProcMask);

    // sigset_t pendingSet;
    // sigpending(&pendingSet);
    // print_signalset(&pendingSet);

    printf("sig_handle:%d\n",sig);
    sleep(3);
    printf("sig_handle end\n");

    // sigpending(&pendingSet);
    // print_signalset(&pendingSet);

    // sigprocmask(SIG_UNBLOCK, NULL, &oldProcMask);
    // print_signalset(&oldProcMask);

    // sigprocmask(SIG_UNBLOCK,&sig_mask,NULL);
}

void sig_action_handle(int sig, siginfo_t * siginfo, void * arg)
{
    printf("sig_handle:%d\n",sig);
    sleep(3);
    printf("sig_handle end\n");
}

void test_sigaction()
{
    // sigset_t pendingSet;
    // sigpending(&pendingSet);
    // print_signalset(&pendingSet);

    struct sigaction sig_act;
    #if 0
    sig_act.sa_flags = 0;   // 设置为0代表使用sa_handler， 设置为SA_SIGINFO使用sa_sigaction
    sig_act.sa_handler = sig_handle;
    #endif

    #if 1
    sig_act.sa_flags = SA_SIGINFO;   // 设置为0代表使用sa_handler， 设置为SA_SIGINFO使用sa_sigaction
    sig_act.sa_handler = sig_action_handle;
    #endif
    sigemptyset(&sig_act.sa_mask);
    sigaddset(&sig_act.sa_mask, SIGQUIT);
    sigaction(SIGINT, &sig_act, NULL);
    print_signalset(&sig_act.sa_mask);

    // sigemptyset(&pendingSet);
    // sigpending(&pendingSet);
    // print_signalset(&pendingSet);
}

int main()
{
    test_sigaction();

    while (1)
    {
        sleep(1);
    }
    
    return 0;
}
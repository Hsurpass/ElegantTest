#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

void test_abort01()
{
    abort();
}

void sig_handle(int sig)
{
    printf("sig:%d\n", sig);
}

void test_abort02()
{
    signal(SIGABRT, sig_handle);
    abort();
}

int main()
{
    // test_abort01();
    test_abort02();

    while (1)
    {
        sleep(1);
    }
    

    return 0;
}
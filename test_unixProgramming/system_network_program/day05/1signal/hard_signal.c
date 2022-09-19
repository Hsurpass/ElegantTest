#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigfpe(int sig)
{
    printf("SIGFPE\n");
    sleep(1);
}

void test_sigfpe()
{
    // signal(SIGFPE, handle_sigfpe);
    int a = 1;
    a /= 0;
}

int main()
{
    test_sigfpe();

    return 0;
}
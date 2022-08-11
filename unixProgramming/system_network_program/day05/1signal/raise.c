#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void handle_sig(int sig)
{
    if(sig == SIGBUS)
    {
        printf("get SIGBUS\n");
    }
} 

void test_raise()
{
    signal(SIGBUS, handle_sig);
    int ret = raise(SIGBUS);
    if (ret == -1)
    {
        perror("raise");
    }
    
}

int main(int argc, char** argv)
{
    test_raise();
    
    return 0;
}
#include <unistd.h>
#include <sys/prctl.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* func(void* arg)
{
    int i = (int)arg;
    char buf[16] = { 0 };
    sprintf(buf, "prctlThread_%d", i);
    printf("buf:%s\n", buf);

    prctl(PR_SET_NAME, "xxxxxxx");    // prctl最多只能设置16字节

    char buf1[16] = {0};
    prctl(PR_GET_NAME, buf1);
    printf("buf1:%s\n", buf1);

    sleep(10);
}

void test_prctl()
{
    pthread_t threadId[3];
    for (int i = 0; i < sizeof(threadId)/sizeof(threadId[0]); i++)
    {
        pthread_create(&threadId[i], NULL, func, (void*)i);
    }

    // sleep(20);

    for (size_t i = 0; i < sizeof(threadId)/sizeof(threadId[0]); i++)
    {
        pthread_join(threadId[i], NULL);
    }
    
}

int main()
{
    test_prctl();

    return 0;
}


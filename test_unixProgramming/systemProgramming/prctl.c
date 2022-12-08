#include <unistd.h>
#include <sys/prctl.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// top -Hp pid 查看该程序的状态
// 除了使用“PR_SET_NAME”参数可以设置线程名字外，另外一个函数pthread_setname_np()也可以实现此功能。
// 设置完成后我们可以通过线程的tid来查看它的新名字：cat /proc/pid/task/[tid]/comm
// 在/proc/pid/task/tid/目录下的stat文件和status文件，也可以看到相应的名字，方便查看线程状态。

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

    sleep(100);
}

void test_prctl()
{
    pthread_t threadId[3];
    for (int i = 0; i < sizeof(threadId)/sizeof(threadId[0]); i++)
    {
        pthread_create(&threadId[i], NULL, func, (void*)i);
    }

    // sleep(100);

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


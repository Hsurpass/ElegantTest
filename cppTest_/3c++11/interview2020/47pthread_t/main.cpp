#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
void func()
{
    for(int i = 0;i < 5;++i)
    {
        sleep(1);
        cout << "func() id:" << pthread_self() << endl;
        if(i == 3)
        {
            pthread_exit((void*)3);
        }

    }
    pthread_exit((void*)5);
}
void* mythread(void *arg)
{
    cout << "mythread() id:" << pthread_self() << endl;
    func();

}
int main()
{
    pthread_t tid;
    int ret = -1;
    pthread_create(&tid,NULL,mythread,NULL);

    for(int i = 0;i < 10;++i)
    {
        cout << "main thread() id:" << pthread_self() << endl;
        cout << gettid();
        sleep(1);
    }

    void* result;
    ret = pthread_join(tid,&result);
    if(ret != 0)
    {
        cout << "pthread join fail" << endl;
    }
    printf("pthread join result:%d\n",(int)result);

    return 0;
}

#if 0
void func(int *p)
{
    *p = 100;
}
int main01()
{
//    int *p1 = new int(10);
//    func(p1);
//    cout << *p1 << endl;
    int i = 10;
    cout << (void*)i << endl;
    cout << (void**)i << endl;
}
#endif

#if 0
void* mythread(void *arg)
{
    int i = 0;

    for(i = 1;i < 5;++i)
    {
        cout << "mythread id:" << pthread_self() << endl;
        sleep(1);
    }

//    pthread_exit((void*)i);
    return ((void*)i);
}
int main()
{
    //    pid_t
    pthread_t pth;
    int ret= -1;
    ret = pthread_create(&pth,NULL,mythread,NULL);
    if(ret != 0)
    {
        cout << "pthread create fail" << endl;
    }
//    printf("thread id:%lx\n",pth);
//    cout << "main thread id:" << pthread_self() << endl;
//    pthread_detach(pth);

    for(int i = 0;i < 10;++i)
    {
        printf("main thread id:%lx\n",pthread_self());
        sleep(1);
    }
//    pthread_detach(pth);

    void* result;
//    int result;
    //    pthread_join(pth,NULL);
    ret = pthread_join(pth,(void**)&result);
    if (ret != 0)
    {
        cout << "pthread_join error code:" << ret << "," << strerror(ret) << endl;
    }
//    cout << "pthread exit code: " << (int)result << endl;
    cout << "pthread exit code: " << (int)result << endl;
    return 0;
}
#endif

#if 0
void* mythread(void * arg)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("pthread\n");
        sleep(1);
    }
    pthread_exit((void *)i);
}
int main(int argc, char** argv)
{
    pthread_t pth;
    int i, ret;

    void* result;
    ret = pthread_create(&pth, NULL, mythread, NULL);
    if(ret != 0)
    {
        printf("create pthread error\n");
        exit(1);
    }
    for(i = 0; i < 5; i++)
    {
        printf("main process\n");
        sleep(1);
    }
    pthread_join(pth, &result);
    printf("pthread exit code = [%d]\n", (int)result);
    return 0;
}
#endif




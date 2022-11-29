#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
一共创建 5 个线程，每个线程都会自己生成一个日志文件，
每个线程将自己的日志写入自己的文件中，当线程执行结束时，会关闭打开的日志文件句柄。
生成的 5 个日志文件中，其内容都写入了一行“Thread starting…”。

程序首先调用 pthread_key_create 函数来申请一个槽位。
在 NPTL 实现下，pthread_key_t 是无符号整型，
pthread_key_create 调用成功时会将一个小于 1024 的值填入第一个入参指向的 pthread_key_t 类型的变量中。
之所以小于 1024，是因为 NPTL 实现一共提供了 1024 个槽位。
*/

//线程局部存储 key
pthread_key_t thread_log_key;

void write_to_thread_log(const char* message)
{
    if (message == NULL)
        return;
    
    printf("%d\n", thread_log_key);
    FILE* logfile = (FILE*)pthread_getspecific(thread_log_key);
    fprintf(logfile, "%s\n", message);
    fflush(logfile);
} 

// 线程结束的时候，关闭FILE*
void close_thread_log(void* logfile)
{
    char logfilename[128];
    sprintf(logfilename, "close logfile: thread%ld.log\n", (unsigned long)pthread_self());
    printf(logfilename);

    fclose((FILE *)logfile);
} 

void* thread_function(void* args)
{
    char logfilename[128];
    sprintf(logfilename, "thread%ld.log", (unsigned long)pthread_self());

    FILE* logfile = fopen(logfilename, "w");
    if (logfile != NULL)
    {
        pthread_setspecific(thread_log_key, logfile);
        printf("[thread_function] threadID:%ld, thread_log_key: %d\n", (unsigned long)pthread_self(), thread_log_key);

        write_to_thread_log("Thread starting...");
    }

    return NULL;
} 

int main()
{
    pthread_t threadIDs[5]; 
    pthread_key_create(&thread_log_key, close_thread_log);
    printf("%d\n", thread_log_key);
    
    for(int i = 0; i < 5; ++i)
    {
        pthread_create(&threadIDs[i], NULL, thread_function, NULL);
    }

    for(int i = 0; i < 5; ++i)
    {
        pthread_join(threadIDs[i], NULL);
    }

    return 0;
}
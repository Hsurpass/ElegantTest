#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

void test_anonymousShm01()
{
    int* ptr = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // int* ptr = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    pid_t pid = fork();
    if(pid == 0)
    {
        printf("child process, pid:%d, ppid:%d, intValue:%d\n", getpid(), getppid(), *(int*)ptr);
        *ptr = 10;
        printf("child process, pid:%d, ppid:%d, intValue:%d\n", getpid(), getppid(), *(int*)ptr);
    }
    else
    {
        sleep(1);
        printf("parent process, pid:%d, childpid:%d, intValue:%d\n", getpid(), pid, *(int*)ptr);
    }
}

void test_anonymousShm02()
{
    void* ptr = mmap(0, sizeof(bool), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // void* ptr = (void*)mmap(0, sizeof(bool), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

    pid_t pid = fork();
    if(pid == 0)
    {
        printf("child process, pid:%d, ppid:%d, boolValue:%d\n", getpid(), getppid(), *(bool*)ptr);
        *(bool*)ptr = true;
        printf("child process, pid:%d, ppid:%d, boolValue:%d\n", getpid(), getppid(), *(bool*)ptr);
    }
    else
    {
        sleep(1);
        printf("parent process, pid:%d, childpid:%d, boolValue:%d\n", getpid(), pid, *(bool*)ptr);
    }
}

int main()
{
    // test_anonymousShm01();
    test_anonymousShm02();

    return 0;
}
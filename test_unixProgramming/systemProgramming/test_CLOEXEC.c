#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void test_CLOEXEC()
{
    // O_CLOEXEC的作用是在fork后，在子进程执行exec函数时fd被关闭，并不是在fork后就立即关闭，在子进程是可以使用的。
    int fd = open("a.txt", O_RDWR | O_CREAT | O_CLOEXEC, 0664);
    if(fd < 0)
        perror("open");

    printf("fd:%d\n", fd);

    pid_t pid = fork();
    if(pid > 0)
    {
        sleep(2);
        // 因为共享同一个文件结构体，此时的文件指针在末尾，所以是读不到数据的。要使用lseek移动文件指针到头部。
        off_t ret = lseek(fd, 0, SEEK_SET);
        char buf[16] = {0};
        int n = read(fd, buf, 16);  
        printf("ret:%ld, n:%d, buf:%s\n", ret, n, buf);
    }
    else
    {
        char buf[] = "hello";
        int n = write(fd, buf, strlen(buf));
        printf("write n:%d\n", n);
    }

    close(fd);
}

int main()
{
    test_CLOEXEC();

    return 0;
}
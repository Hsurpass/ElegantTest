#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd0 = open("log1.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(-1 == fd0)
    {
        perror("open");
    }
    printf("fd0:%d\n", fd0);
    int fd1 = dup(fd0); // fd0 fd1指向同一个FILE结构体
    printf("fd1:%d\n", fd1);

    char* buf1 = "hello ";
    char* buf2 = "world!";

    int len = strlen(buf1);
    printf("len: %d\n", len);
    if(write(fd0, buf1, len) != 6)
        perror("write fd0");

    off_t off_fd0 = lseek(fd0, 0, SEEK_CUR);
    off_t off_fd1 = lseek(fd1, 0, SEEK_CUR);
    printf("off_fd0 = %ld\n", off_fd0);      // 6
    printf("off_fd1 = %ld\n", off_fd1);      // 6

    if(write(fd1, buf2, strlen(buf2)) != 6)
        perror("write fd1");

    off_fd0 = lseek(fd0, 0, SEEK_CUR);
    off_fd1 = lseek(fd1, 0, SEEK_CUR);
    printf("off_fd0 = %ld\n", off_fd0);      // 12
    printf("off_fd1 = %ld\n", off_fd1);      // 12

    close(fd0);
    close(fd1); // 引用计数为0的时候释放FILE结构体
    return 0;
}





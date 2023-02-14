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
    int fd = open("log3.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);    // 3
    if(-1 == fd)
    {
        perror("open");
    }
    printf("fd = %d\n", fd);    // 3

    int fd1 = dup2(fd, STDOUT_FILENO);  // STDOUT_FILENO指向fd的FILE结构体，释放自身的结构体， 引用计数加一
    int fd2 = dup2(fd, STDERR_FILENO);  // STDERR_FILENO指向fd的FILE结构体，释放自身的结构体， 引用计数加一
    printf("fd1 = %d\n", fd1);  // 1 
    printf("fd2 = %d\n", fd2);  // 2

    close(fd); // fd 所指向的FILE结构体引用计数减一
    printf("fd = %d\n", fd);    // 3

    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);    

    puts("hello");      // close STDOUT_FILENO再写入 就会 dup2: Bad file descriptor
    printf("world\n");  // close STDERR_FILENO再写入 就会 dup2: Bad file descriptor
    perror("dup2");     // close STDERR_FILENO再写入 就会 dup2: Bad file descriptor

    return 0;
}
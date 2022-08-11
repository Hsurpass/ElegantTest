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
    int fd0 = open("log2.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(-1 == fd0)
    {
        perror("open");
    }

    int fd1 = open("log2.txt", O_RDWR);
    if(-1 == fd1)
    {
        perror("open");
    }

    char* buf1 = "hello ";
    char* buf2 = "world!!";

    int len = strlen(buf1);
    printf("len: %d\n", len);
    if(write(fd0, buf1, len) != 6)
        perror("write fd0");
    
    off_t off_fd0 = lseek(fd0,0,SEEK_CUR);
    off_t off_fd1 = lseek(fd1,0,SEEK_CUR);
    printf("off_fd0 = %ld\n",off_fd0);  // 6
    printf("off_fd1 = %ld\n",off_fd1);  // 0

    if(write(fd1, buf2, strlen(buf2)) != 6)
        perror("write fd1");

    off_fd0 = lseek(fd0, 0, SEEK_CUR);
    off_fd1 = lseek(fd1, 0, SEEK_CUR);
    printf("off_fd0 = %ld\n", off_fd0);      // 6
    printf("off_fd1 = %ld\n", off_fd1);      // 7   fd0 和 fd1 指向不同的FILE结构体，但最终指向同一个inode,所以后写入的就把前面的覆盖了

    close(fd1);
    close(fd0);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd = open("rootfile.txt", O_RDWR);
    printf("fd:%d\n", fd);
    perror("open");
    char buf[] = "abc";
    int n = write(fd, buf, strlen(buf));
    printf("write to rootfile.txt [n:%d] byte\n", n);
    
    close(fd);

    printf("finish\n");
    return 0;
}
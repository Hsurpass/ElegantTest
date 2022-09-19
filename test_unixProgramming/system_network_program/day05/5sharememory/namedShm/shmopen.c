#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* shm_name = "/myshm";

void test_shm_open()
{
    // int fd = shm_open(shm_name, O_CREAT | O_RDWR | O_EXCL, 0664);    // O_EXCL 文件存在会返回-1
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0664);
    // int fd = shm_open(shm_name, O_CREAT | O_RDWR | O_TRUNC, 0664);
    if (-1 == fd)
    {
        perror("shm_open");
        exit(0);
    }
    printf("shm create success\n");
    int ret = 0;
    long pageszie = sysconf(_SC_PAGE_SIZE); // _SC_PAGE_SIZE 为内存页的大小
    printf("pagesize = %ld\n", pageszie);
    // ret = ftruncate(fd, pageszie * 2);  // 把fd指向的文件大小改为 2 * pagesize 这么大
    ret = ftruncate(fd, 512);   /// 把fd指向的文件大小改为 512字节 这么大

    if (-1 == ret)
    {
        perror("ftruncate");
        exit(0);
    }
    printf("ftruncate success\n");

}

int main()
{
    test_shm_open();
    
    return 0;
}
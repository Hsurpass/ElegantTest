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

void test_shm_read()
{
    // 1.创建共享内存文件
    // int fd = shm_open(shm_name, O_RDWR, 0664);
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0664);
    if (-1 == fd)
    {
        perror("shm_open");
        exit(0);
    }
    printf("shm create success\n");

    // 2.扩展文件大小
    int ret = 0;
    long pageszie = sysconf(_SC_PAGE_SIZE);
    printf("pagesize = %ld\n", pageszie);
    ret = ftruncate(fd, pageszie * 2);
    if (-1 == ret)
    {
        perror("ftruncate");
        exit(0);
    }
    printf("ftruncate success\n");

    // 3.把共享内存映射到进程的虚拟内存
    void *pread = mmap(0, pageszie * 2, PROT_READ, MAP_SHARED, fd, 0);  // mmap必须以内存页为单位进行映射，不足一内存页的按一内存页处理
    if (pwrite == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    printf("pread:%p, strlen(pread) = %ld\n", pread, strlen(pread));

    int count = 0;
    while (count++ < 10)
    // while(1)
    {
        printf("read share memory: %s\n", (char *)pread);
        sleep(1);   
    }

    munmap(pread, pageszie * 2);    // 卸载共享内存
    // shm_unlink(shm_name);   //删除共享内存文件   // 读端不应该主动删除



    // char* ptmp = (char *)pread;
    // while (1)
    // {
    //     printf("read share memory: %s\n",(char *)ptmp);
    //     ptmp += (strlen(ptmp)+1);
    //     sleep(1);   
    // }
}

int main()
{
    test_shm_read();
    
    return 0;
}
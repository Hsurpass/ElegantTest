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

void test_shm_write()
{
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0664);
    if (-1 == fd)
    {
        perror("shm_open");
        exit(0);
    }
    printf("shm create success\n");

    int ret = 0;
    long pageszie = sysconf(_SC_PAGE_SIZE);
    printf("pagesize = %ld\n",pageszie);
    ret = ftruncate(fd, pageszie * 2);
    if (-1 == ret)
    {
        perror("ftruncate");
        exit(0);
    }
    printf("ftruncate success\n");
    
    void *pwrite = mmap(0, pageszie * 2, PROT_WRITE, MAP_SHARED, fd, 0);
    if (pwrite == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    printf("pwrite: %p\n", pwrite);

    int count = 0;
    // while (count < 10)
    while(1)
    {
        sprintf(pwrite, "DATA%d", ++count);
        printf("write share memory:%s \n",(char*)pwrite);
        sleep(1);   
    }
    munmap(pwrite, pageszie * 2);
    shm_unlink(shm_name);



    // char* ptmp = (char *)pwrite;
    // while (1)
    // {
    //     sprintf(ptmp,"DATA%d",++count);
    //     printf("write share memory:%s \n",ptmp);
    //     ptmp += (strlen(ptmp) + 1);
    //     sleep(1);   
    // }
}

int main()
{
    test_shm_write();
    
    return 0;
}
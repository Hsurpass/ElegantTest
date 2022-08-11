#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int a = 2;
    pid_t pid = fork();
    if (pid == 0)
    {
        // linux的写时复制技术(COW)，fork之后子进程的虚拟内存从父进程拷贝过来，但物理内存指向同一块（浅拷贝）, 读时共享，写时才会在物理内存开辟一块新空间
        a = 4; 
        printf("child process, a = %d, pid = %d\n",a,getpid() );
        exit(0);
    }
    else if (pid > 0)
    {
        sleep(3);
        // a = 10; 
        printf("parent process, a = %d, pid = %d\n",a,getpid() );
        exit(1);
    }
    else
    {
        perror("fork");
    }

    
    
    return 0;
}
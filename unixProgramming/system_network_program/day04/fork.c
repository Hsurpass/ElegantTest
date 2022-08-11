#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    printf("c1....\n");
    // printf("c1....");    // 没有刷新缓冲区
    pid_t pid = fork();
    printf("c2...");
    if(pid == 0)
    {

    }
    else if (pid > 0) {

    }
    else {
        perror("fork");
    }
    printf("Hello World!,pid = %d\n",getpid() );
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    printf("pipe buf %ld\n", pathconf("myfifo", _PC_PIPE_BUF));

    return 0;
}
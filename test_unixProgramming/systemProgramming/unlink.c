#include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void test_unlink()
{
    int r = unlink("hardlink.txt");
    printf("r:%d\n", r);
    perror("unlink");

    r = unlink("softlink.txt");
    printf("r:%d\n", r);
    perror("unlink");

}

int main()
{
    test_unlink();
    
    return 0;
}
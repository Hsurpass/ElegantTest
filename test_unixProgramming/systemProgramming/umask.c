#include <stdio.h>
#include <sys/stat.h>

void test_umask()
{
    mode_t mask = umask(0);
    printf("%u\n", mask);
    printf("0x%x\n", mask);

    mask = umask(mask);
    printf("%u\n", mask);
    printf("0x%x\n", mask);

    mask = umask(mask);
    printf("%u\n", mask);
    printf("0x%x\n", mask);

    mask = umask(mask);
    printf("%u\n", mask);
    printf("0x%x\n", mask);
}

int main()
{
    test_umask();

    return 0;
}
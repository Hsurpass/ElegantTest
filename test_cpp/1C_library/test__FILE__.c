#include <stdio.h>

/*
    gcc /home/hchy/test__FILE__.c
    hchy@DESKTOP-EI7DNUT:~$ ./a.out
    /home/hchy/test__FILE__.c 5 main
*/
int main()
{
    printf("%s %d %s\n", __FILE__, __LINE__, __func__);
    return 0;
}
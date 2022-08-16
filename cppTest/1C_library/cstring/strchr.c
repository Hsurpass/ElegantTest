#include <stdio.h>
#include <string.h>

void test_strchr()
{
    char str[] = "This is a sample string";
    char *pch;
    printf("Looking for the 's' character in \"%s\"...\n", str);
    pch = strchr(str, 's');
    char buf[32] = {0};
    while (pch != NULL)
    {
        printf("found at %ld\n", pch - str + 1);
        strncpy(buf, str, pch - str + 1);
        printf("buf:%s\n", buf);
        pch = strchr(pch + 1, 's');
    }
}

int main()
{
    test_strchr();

    return 0;
}
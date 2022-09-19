#include <stdio.h>
#include <string.h>

void test01()
{
    char str[] = "hello world";
    char* p = strtok(str, " ");
    while (p != NULL)
    {
        printf("%s\n", p);  // hello world
        p = strtok(NULL, " ");
    }
}

void test02()
{
    char str[] ="- This, a sample string.";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok(str," ,.-");
    while (pch != NULL)
    {
      printf ("%s\n", pch);
      pch = strtok (NULL, " ,.-");
    }
    // This
    // a
    // sample
    // string
}

int main()
{
    // test01();
    test02();

    return 0;
}
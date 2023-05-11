#include <stdio.h>
#include <stdlib.h>

void test_calloc()
{
    int* p = (int*)calloc(5, sizeof(int));
    for(int i = 0; i < 5; i++)
    {
        printf("%d\n", p[i]);
    }

    free(p);
}

int main()
{
    test_calloc();
    
    return 0;
}
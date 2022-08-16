#include <stdarg.h>
#include <stdio.h>

void test_va_list(int n, ...)
{
    va_list vl;
    va_start(vl, n);
    
    for (int i = 0; i < n; i++)
    {
        printf("val:%f\n", va_arg(vl, double));
    }
    va_end(vl);
    
    va_end(vl);
}

int main()
{
    test_va_list(3, 2.1, 3.1, 4.1);

    return 0;
}
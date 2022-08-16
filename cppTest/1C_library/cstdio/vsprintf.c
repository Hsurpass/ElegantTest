#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

void test_vsprintf_log(const char* format, ...)
{
    va_list vl;
    va_start(vl, format);

    char buf[64] = {0};
    vsprintf(buf, format, vl);
    printf("%s\n", buf);

    va_end(vl);
}

int main()
{
    test_vsprintf_log("age:%d, name:%s, score:%f, flag:%d.\n", 20, "shit", 12.3, 1);

    return 0;
}
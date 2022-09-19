#include <stdio.h>
#include "stack_list_c.h"
#include <stdlib.h>

int main()
{
    Stacklist s;
    initStacklist(&s);
    for(char ch = 'A';ch <= 'Z';ch++)
    {
            push(&s,ch);
    }
//    resetstacklist(&s);
    while (!isempty(&s)) {
        printf("%c ",pop(&s));
    }
    clearstacklist(&s);

    return 0;
}

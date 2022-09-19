#include <stdio.h>
#include "stack_c.h"

int main()
{
    Stack s;
    initStack(&s,30);
    for(char ch = 'a';ch <= 'z';ch++)
    {
        if(!isfull(&s))
        {
            push(&s,ch);
        }
    }
//    resetstack(&s);
    while (!isempty(&s)) {
        printf("%c ",pop(&s));
    }
    destroystack(&s);

    return 0;
}

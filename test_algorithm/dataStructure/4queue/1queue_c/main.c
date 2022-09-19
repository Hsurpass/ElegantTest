#include <stdio.h>
#include "queue_c.h"
#include <stdlib.h>

int main()
{
    Queue q;
    queueinit(&q,27);

    for(char ch = 'a';ch <= 'z';ch++)
    {
        if(!isqueuefull(&q))
        {
            enqueue(&q,ch);
        }
    }
    while (!isqueueempty(&q)) {
        printf("%c ",dequeue(&q));
    }

    return 0;
}

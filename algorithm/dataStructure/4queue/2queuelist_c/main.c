#include <stdio.h>
#include "queuelist_c.h"

int main()
{
    QNode q;
    queueinit(&q);
    for(int i='a'; i<='z'; i++)
    {
    enqueue(&q,i);
    }
    while(!isqueueempty(&q))
    {
    printf("%c ",dequeue(&q));
    }
    destroyqueue(&q);
    return 0;
}

#include <stdio.h>
#include "doublelist_c.h"
#include <time.h>
#include <stdlib.h>
int main()
{
    DNode *head = createdlist();
    srand(time(NULL));
    for(int i = 0;i < 10;i++)
    {
        insertdlist(head,rand()%10);
    }
    traversedlist(head);
    putchar(10);
    int len = lendlist(head);
    printf("%d\n",len);
    DNode*pfind = searchdlist(head,1);
    if(pfind != NULL)
    {
        deletedlist(head,pfind);
    }
    traversedlist(head);
    putchar(10);
    bubblesortdlist(head);
    traversedlist(head);
    putchar(10);
    destroydlist(head);
    deletedlist(head,pfind);
    return 0;
}

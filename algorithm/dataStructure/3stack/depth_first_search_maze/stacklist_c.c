#include"stack_list_c.h"
#include <stdlib.h>
#include <stdio.h>

void initStacklist(Stacklist *s)
{
    s->top = (Node*)malloc(sizeof(Node));
    s->top->next = NULL;
}
int isempty(Stacklist *s)
{
    return s->top->next == NULL;
}
void push(Stacklist *s, Point data)
{
    Node* cur = (Node*)malloc(sizeof(Node));
    cur->data = data;
    cur->next= s->top->next;
    s->top->next = cur;
}
Point pop(Stacklist *s)
{
    Node *t = s->top->next;
    Point tdata = t->data;
    s->top->next = s->top->next->next;
    free(t);
    return tdata;
}

void resetstacklist(Stacklist *s)
{
    while (!isempty(s)) {
        pop(s);
    }
}
void clearstacklist(Stacklist *s)
{
    resetstacklist(s);
    free(s->top);
}

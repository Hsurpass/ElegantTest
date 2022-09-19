#include<stdio.h>
#include <stdlib.h>
#include "stack_c.h"
#include <unistd.h>

void initStack(Stack *s,int size)
{
    s->len = size;
    s->top = 0;
    s->space = (char *)malloc(s->len);
}
int isfull(Stack *s)
{
    if(s->top == s->len)
    {
        return 1;
    }
    return 0;
}
int isempty(Stack *s)
{
    if(s->top == 0)
    {
        return 1;
    }
    else {
        return 0;
    }
}
void push(Stack* s,char ch)
{
    s->space[s->top++] = ch;
}
char pop(Stack *s)
{
    return s->space[--s->top];
}
void resetstack(Stack *s)
{
    s->top = 0;
}
void destroystack(Stack *s)
{
    free(s->space);
}

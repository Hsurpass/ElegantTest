#ifndef STACK_LIST_C_H
#define STACK_LIST_C_H

typedef struct _Node
{
    char data;
    struct _Node *next;
}Node;

typedef struct _Stack
{
    Node *top;
}Stacklist;

void initStacklist(Stacklist *s);
int isempty(Stacklist *s);
void push(Stacklist *s,char data);
char pop(Stacklist *s);
void resetstacklist(Stacklist *s);
void clearstacklist(Stacklist *s);
#endif // STACK_LIST_C_H

#ifndef STACK_LIST_C_H
#define STACK_LIST_C_H

typedef struct _Point
{
    int _x;
    int _y;
}Point;

typedef struct _Node
{
    Point data;
    struct _Node *next;
}Node;

typedef struct _Stack
{
    Node *top;
}Stacklist;

void initStacklist(Stacklist *s);
int isempty(Stacklist *s);
void push(Stacklist *s,Point data);
Point pop(Stacklist *s);
void resetstacklist(Stacklist *s);
void clearstacklist(Stacklist *s);
#endif // STACK_LIST_C_H

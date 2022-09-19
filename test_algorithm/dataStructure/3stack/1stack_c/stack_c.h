#ifndef STACK_C_H
#define STACK_C_H

typedef struct _stack
{
    int len;
    char* space;
    int top;
}Stack;

void initStack(Stack *s,int size);
int isfull(Stack *s);
int isempty(Stack *s);
void push(Stack* s,char ch);
char pop(Stack *s);
void resetstack(Stack *s);
void destroystack(Stack *s);
#endif // STACK_C_H

#include "queue_c.h"
#include <stdio.h>
#include <stdlib.h>

void queueinit(Queue *q,int size)
{
    q->len = size;
    q->space = (char *)malloc(size);
    q->front = q->rear = 0;
}
int isqueuefull(Queue *q)
{
    return (q->rear+1) % q->len == q->front;
}
int isqueueempty(Queue *q)
{
    return q->front == q->rear;
}
void enqueue(Queue *q,char data)
{
    q->space[q->rear] = data;
    q->rear = (q->rear+1)%q->len;
}
char dequeue(Queue *q)
{
    char ch = q->space[q->front];
    q->front = (q->front+1) % q->len;
    return ch;
}
void resetqueue(Queue *q)
{
    q->front = q->rear;
}
void destroyqueue(Queue *q)
{
    q->len = q->front = q->rear = 0;
    free(q->space);
}

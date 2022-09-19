#ifndef QUEUE_C_H
#define QUEUE_C_H

typedef struct _Queue
{
    int len;
    int front;
    int rear;
    char *space;
}Queue;

void queueinit(Queue *q, int size);
int isqueuefull(Queue *q);
int isqueueempty(Queue *q);
void enqueue(Queue *q,char data);
char dequeue(Queue *q);
void resetqueue(Queue *q);
void destroyqueue(Queue *q);

#endif // QUEUE_C_H

#ifndef QUEUELIST_C_H
#define QUEUELIST_C_H

typedef struct _QNode
{
    char data;
    struct _QNode *next;
}QNode;

typedef struct _PQueue
{
   QNode *front;
   QNode *rear;
}PQueue;

void queueinit(PQueue *pq);
int isqueueempty(PQueue *pq);
void enqueue(PQueue *pq,char data);
char dequeue(PQueue *pq);
void resetqueue(PQueue *pq);
void destroyqueue(PQueue *pq);

#endif // QUEUELIST_C_H

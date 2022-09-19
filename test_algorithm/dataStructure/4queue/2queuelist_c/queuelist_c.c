#include "queuelist_c.h"
#include <stdio.h>
#include <stdlib.h>


void queueinit(PQueue *pq)
{
    pq->front = pq->rear = (QNode*)malloc(sizeof(QNode));
    pq->rear->next = NULL;
}
int isqueueempty(PQueue *pq)
{
    return pq->front == pq->rear;
}
void enqueue(PQueue *pq,char data)
{
    QNode *cur = (QNode*)malloc(sizeof(QNode));
    cur->data = data;
    cur->next = NULL;

    pq->rear->next = cur;
    pq->rear = cur;
}
char dequeue(PQueue *pq)
{
    char data = pq->front->next->data;
    if(pq->front->next == pq->rear)//只有一个元素
    {
        free(pq->rear);
        pq->rear = pq->front;
        pq->front->next = NULL;
    }
    else {
        QNode *t = pq->front->next;
        pq->front->next = t->next;
        free(t);
    }

    return data;
}
void resetqueue(PQueue *pq)
{
    QNode *head = pq->front->next;
    pq->front->next = NULL;
    pq->rear = pq->front;
    QNode *t;
    while (head) {
        t = head->next;
        free(head);
        head = t;
    }
}

void destroyqueue(PQueue *pq)
{
    resetqueue(pq);
    free(pq);
}

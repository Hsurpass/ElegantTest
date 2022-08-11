#ifndef QUEUELIST_C_H
#define QUEUELIST_C_H

typedef struct _treenode
{
    char _data;
    struct _treenode *_left;
    struct _treenode *_right;
}TreeNode;

typedef struct _QNode
{
    TreeNode* data;
    struct _QNode *next;
}QNode;

typedef struct _PQueue
{
   QNode *front;
   QNode *rear;
}PQueue;

void queueinit(PQueue *pq);
int isqueueempty(PQueue *pq);
void enqueue(PQueue *pq,TreeNode* data);
TreeNode* dequeue(PQueue *pq);
void resetqueue(PQueue *pq);
void destroyqueue(PQueue *pq);

#endif // QUEUELIST_C_H

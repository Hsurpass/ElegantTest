#ifndef STACK_LIST_C_H
#define STACK_LIST_C_H

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;

typedef struct _Node
{
    TreeNode* data;
    struct _Node *next;
}Node;

typedef struct _Stack
{
    Node *top;
}Stacklist;

void initStacklist(Stacklist *s);
int isempty(Stacklist *s);
void push(Stacklist *s,TreeNode* data);
TreeNode *pop(Stacklist *s);
void resetstacklist(Stacklist *s);
void clearstacklist(Stacklist *s);
#endif // STACK_LIST_C_H

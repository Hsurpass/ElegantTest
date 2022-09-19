#ifndef LIST_C_H
#define LIST_C_H

typedef struct _Node
{
    int data;
    struct _Node *next;
}Node;

Node* createList();
void traverseList(Node* head);
int lenList(Node* head);
void insertList(Node *head,int data);
Node* searchList(Node* head,int finddata);
void deleteList(Node* head,Node *pfind);
void bubblesortList(Node* head);
void reverseList(Node* head);
void destroyList(Node *head);

#endif // LIST_C_H

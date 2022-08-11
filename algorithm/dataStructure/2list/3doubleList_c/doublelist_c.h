#ifndef DOUBLELIST_C_H
#define DOUBLELIST_C_H
#include <stdio.h>

typedef struct _DNode
{
    int data;
    struct _DNode* next;
    struct _DNode* pre;
}DNode;

DNode* createdlist();
int lendlist(DNode* head);
void traversedlist(DNode *head);
void insertdlist(DNode* head,int data);
DNode* searchdlist(DNode* head,int finddata);
void deletedlist(DNode* head,DNode* pfind);
void bubblesortdlist(DNode* head);
void destroydlist(DNode* head);

#endif // DOUBLELIST_C_H

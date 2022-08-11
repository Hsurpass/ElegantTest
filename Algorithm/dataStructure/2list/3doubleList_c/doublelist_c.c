#include "doublelist_c.h"
#include <stdio.h>
#include <stdlib.h>

DNode* createdlist()
{
    DNode* head = (DNode*)malloc(sizeof(DNode));
    if(NULL == head)
    {
        printf("dlist create error\n");
    }
    head->next = head->pre = head;
    return head;
}
int lendlist(DNode* head)
{
    DNode *t = head->next;
    int len=0;
    while (t != head) {
        len++;
        t = t->next;
    }
    return len;
}
void traversedlist(DNode *head)
{
    DNode *t = head->next;
    while (t != head) {
        printf("%d ",t->data);
        t = t->next;
    }
}
void insertdlist(DNode* head,int data)
{
    DNode* cur = (DNode*)malloc(sizeof(DNode));
    cur->data = data;
    cur->next = head->next;
    cur->pre = head;
    head->next = cur;
    cur->next->pre = cur;
}
DNode* searchdlist(DNode* head,int finddata)
{
    DNode *clock = head->next;
    DNode *anticlock = head->pre;

    while (anticlock != clock->pre)
    {
        if(clock->data == finddata)
        {
            return clock;
        }
        if(anticlock->data == finddata)
        {
            return anticlock;
        }
        if(clock == anticlock)
        {
            return NULL;
        }
        clock = clock->next;
        anticlock = anticlock->pre;
    }
    return NULL;
}
void deletedlist(DNode* head,DNode* pfind)
{
    pfind->pre->next = pfind->next;
    pfind->next->pre = pfind->pre;
    free(pfind);
}
void bubblesortdlist(DNode* head)
{
    //swap pointer
    int len = lendlist(head);
    DNode *p,*q;
    for(int i = 0;i < len-1;i++)
    {
        p = head->next;
        q = p->next;
        for(int j = 0;j < len-1-i;j++)
        {
            if(p->data > q->data)
            {
                p->pre->next = q;
                q->pre = p->pre;
                p->next = q->next;
                p->pre = q;
                q->next = p;
                p->next->pre = p;

                q = p->next;
                continue;
            }
            p = p->next;
            q = q->next;
        }

    }
}
void destroydlist(DNode* head)
{
    head->pre->next = NULL;
    DNode *t =head;
    while (head) {
        t = head->next;
        free(head);
        head = t;
    }
}

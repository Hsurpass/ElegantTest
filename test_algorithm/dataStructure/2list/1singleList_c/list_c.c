#include "list_c.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

Node* createList()
{
    Node *head = (Node*)malloc(sizeof(Node));
    if(NULL == head)
    {
        printf("create head error\n");
        return NULL;
    }
    head->next = NULL;
    
    return head;
}

void traverseList(Node* head)
{
    head = head->next;
    while (head) {
        printf("%d ",head->data);
        head = head->next;
    }
}

int lenList(Node* head)
{
    head = head->next;
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

// 头插法
void insertList(Node *head,int data)
{
    Node *cur = (Node*)malloc(sizeof(Node));
    if(NULL == cur)
    {
        printf("cur create error\n");
        exit(-1);
    }
    cur->data = data;
    cur->next = head->next;
    head->next = cur;
}

Node* searchList(Node* head,int finddata)
{
    head = head->next;
    while (head) 
    {
        if(head->data == finddata)
        {
            break;
        }
        head = head->next;
    }

    return head;
}

void deleteList(Node* head, Node *pfind)
{
    if(NULL == pfind)
    {
        while (head->next != pfind) 
        {
            head = head->next;
        }
        head->next = pfind->next;
        free(pfind);
    }
    else 
    {
        pfind->data = pfind->next->data;
        Node* t = pfind->next;
        pfind->next = pfind->next->next;
        free(t);
    }
}

void bubblesortList(Node* head)
{

    int len = lenList(head);
    /*********swap data************
    Node *p,*q;
    for(int i = 0;i < len-1;i++)
    {
        p = head->next;
        q = p->next;
        for(int j = 0;j < len-1-i;j++)
        {
            if(p->data > q->data)
            {
                p->data = p->data^q->data;
                q->data = p->data^q->data;
                p->data = p->data^q->data;
            }
            p = p->next;
            q = q->next;
        }
    }
    *********swap data************/
    /*********swap pointer************/
    Node *pre,*p,*q;
    for(int i = 0;i < len-1;i++)
    {
        pre = head;
        p = head->next;
        q = p->next;
        for(int j = 0;j < len-1-i;j++)
        {
            if(p->data > q->data)
            {
                pre->next = q;
                p->next = q->next;
                q->next = p;

                pre = q;
                q = p->next;
                continue;
            }
            pre = pre->next;
            p = p->next;
            q= q->next;
        }
    }
    /*********swap pointer************/
}

void reverseList(Node* head)
{
    Node *h = head->next;
    Node *t = NULL;
    head->next = NULL;  // 先把链表打断，再采用头插法，就能逆序链表
    while (h) {
        t = h->next;

        h->next = head->next;
        head->next = h;

        h = t;
    }
}

void destroyList(Node *head)
{
    Node *t = NULL;
    while (head) {
        t = head->next;
        free(head);
        head = t;
    }
}

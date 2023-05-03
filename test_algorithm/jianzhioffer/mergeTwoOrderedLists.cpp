#include <iostream>

using namespace std;

struct LinkList
{
    int data;
    struct LinkList *next;
};

LinkList* mergeTwoOrderedLists(LinkList *l1, LinkList *l2)
{
    LinkList node;
    LinkList* cur = &node;

    while (l1 && l2)
    {
        if(l1->data < l2->data)
        {
            cur->next = l1;
            l1 = l1->next;
        }   
        else
        {
            cur->next = l2;
            l2 = l2->next;
        } 
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;

    return node.next;
}

int main()
{
    LinkList node1{1}, node2{3}, node3{5};
    LinkList node4{2}, node5{4}, node6{6};

    node1.next = &node2; node2.next = &node3;
    node4.next = &node5; node5.next = &node6;

    LinkList* tmp = mergeTwoOrderedLists(&node1, &node4);
    while(tmp)
    {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    putchar(10);
    
    return 0;
}
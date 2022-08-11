#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    int val;
    struct LinkedNode* next;
}LinkedNode;

LinkedNode* initSingleLinkedList()
{
    LinkedNode* pNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    LinkedNode* pNode1 = (LinkedNode*)malloc(sizeof(LinkedNode));
    LinkedNode* pNode2 = (LinkedNode*)malloc(sizeof(LinkedNode));
    LinkedNode* pNode3 = (LinkedNode*)malloc(sizeof(LinkedNode));
    LinkedNode* pNode4 = (LinkedNode*)malloc(sizeof(LinkedNode));

    pNode->val = 0;
    pNode->next = pNode1;
    
    pNode1->val = 1;
    pNode1->next = pNode2;
    
    pNode2->val = 2;
    pNode2->next = pNode3;
    
    pNode3->val = 3;
    pNode3->next = pNode4;
    
    pNode4->val = 4;
    pNode4->next = NULL;

    return pNode;
}

void destorySingleLinkedList(LinkedNode* pNode)
{
    LinkedNode* p = pNode;
    while (p != NULL)
    {
        LinkedNode* tmpNode = p->next;
        free(p);
        p = tmpNode;
    }
    
}

void printSingleLinkedList(LinkedNode* pNode)
{   
    LinkedNode* p = pNode;
    while (p != NULL)
    {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

// method 1 使用三个辅助指针
LinkedNode* reverse_single_linked_list_by_three_pointer(LinkedNode* pNode)
{
    LinkedNode* prev = NULL;
    LinkedNode* curr = pNode;
    LinkedNode* next = NULL;

    while (curr != NULL)
    {
        // 1.先保存后一个节点
        next = curr->next;
        // 2.打断当前节点，使其指向前一个
        curr->next = prev;
        // 3.prev指针向后移
        prev = curr;
        // 4.curr指针向后移
        curr = next;
    }
    
    return prev;
}

// 使用头插法来逆序链表
LinkedNode* reverse_single_linked_list_by_headInsert(LinkedNode* head)
{
    LinkedNode* tmpHeadNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    tmpHeadNode->next = NULL;

    LinkedNode* curr = head;
    LinkedNode* next = NULL;

    while (curr != NULL)
    {
        // 1.保存下一个节点
        next = curr->next;

        // 2.头插法
        curr->next = tmpHeadNode->next;
        tmpHeadNode->next = curr;

        // 3.重新赋值curr
        curr = next;
    }

    return tmpHeadNode->next;
}

int main()
{
    LinkedNode* pNode = initSingleLinkedList();
    printSingleLinkedList(pNode);

    LinkedNode* p = reverse_single_linked_list_by_three_pointer(pNode);
    printSingleLinkedList(p);

    LinkedNode* p1 = reverse_single_linked_list_by_headInsert(p);
    printSingleLinkedList(p1);

    destorySingleLinkedList(pNode);
    return 0;
}
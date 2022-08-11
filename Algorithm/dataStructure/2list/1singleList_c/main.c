#include <stdio.h>
#include "list_c.h"


int main()
{
    Node *head = createList();
    insertList(head,1);
    insertList(head,4);
    insertList(head,3);
    insertList(head,3);
    insertList(head,6);
    insertList(head,5);
    traverseList(head);
    printf("\n");
    int len = lenList(head);
    printf("%d\n",len);
//    Node *pfind = searchList(head,3);
//    if(pfind != NULL)
//    {
//        deleteList(head,pfind);
//    }
//    traverseList(head);
//    putchar(10);
    bubblesortList(head);
    traverseList(head);
    putchar(10);
    reverseList(head);
    traverseList(head);
    putchar(10);
    destroyList(head);
}


#if 0
void selectsort(int *arr,int n)
{
    for(int i = 0;i < n-1;i++)
    {
        int k = i;
        for(int j = i+1;j < n;j++)
        {
            if(arr[k] > arr[j])
            {
                k = j;
            }
        }
        if(k != i)
        {
            arr[k] ^= arr[i];
            arr[i] ^= arr[k];
            arr[k] ^= arr[i];
        }
    }
}

int main()
{
    int arr[10]={3,2,5,7,1,0,9,4,8,6};
    for(int i = 0;i < 10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    selectsort(arr,10);
    for(int i = 0;i < 10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
#endif

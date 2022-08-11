#include <stdio.h>
#include "sort_all.h"
#include <stdlib.h>

void disarr(int *arr,int n)
{
    for(int i = 0;i < n;i++)
    {
        printf("%d ",arr[i]);
    }
    putchar(10);
}

int compare(const void *pa,const void *pb)
{
    return *(int *)pa - *(int *)pb;
}
int main()
{
    int arr[] = {50,13,27,45,1,3,5,7,9,2,4,6,8,10,100,200};
    int n = sizeof(arr)/sizeof(*arr);
    printf("n = %d\n",n);
    disarr(arr,n);
    qsort(arr,n,sizeof(*arr),compare);
    disarr(arr,n);

    int find = 7;
//    int index = binarysearch_iteration(arr,0,n-1,find);
    int index = binarysearch_recursive(arr,0,n-1,find);
    printf("%d index is %d\n",find,index);

    return 0;
}

int main02()
{
//    int a[5] = {1,3,5,7,9};
//    int b[7] = {2,4,6,8,10,100,200};
//    int c[10];
//    mergetwoorderedarray(a,5,b,5,c,10);
    //disarr(c,10);
//    int arr[] = {1,3,5,7,9,2,4,6,8,10,100,200};
    int arr[] = {50,13,27,45,1,3,5,7,9,2,4,6,8,10,100,200};
    int n = sizeof(arr)/sizeof(*arr);
    int tmp[48]={0};
    //merge_twoorderedpart_in_array(arr,tmp,0,4,11);
//    disarr(arr,n);
    disarr(arr,n);
    mergesort(arr,tmp,0,n-1);
    disarr(arr,n);
}

int main01()
{
    int arr[] = {1,3,5,7,9,2,4,6,8,10};
    int n = sizeof(arr)/sizeof(arr[0]);
    disarr(arr,sizeof(arr)/sizeof(arr[0]));
    //bubblesort(arr,sizeof(arr)/sizeof(*arr));
    //disarr(arr,n);
//    insertsort(arr,n);
//    disarr(arr,n);
//    shellsort(arr,n);
//    disarr(arr,n);
//    selectsort(arr,n);
//    disarr(arr,n);
//    quicksort(arr,0,9);
//    disarr(arr,n);

    return 0;
}

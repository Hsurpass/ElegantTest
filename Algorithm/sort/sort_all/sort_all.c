#include"sort_all.h"
#include <stdio.h>
#include <stdlib.h>

void bubblesort(int *arr,int n)
{
    int flag = 1;
    for(int i = 0;i < n-1;i++)
    {
        flag = 1;
        for(int j = 0;j < n-1-i;j++)
        {
            if(arr[j] > arr[j+1])
            {
                arr[j] ^= arr[j+1];
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
                flag = 0;
            }
        }
        if(flag)
        {
            break;
        }
    }
}

void insertsort(int *arr, int n)
{
    int i,j,t;
    for(i = 1;i < n;i++)
    {
        t = arr[i];
        for(j = i;j - 1 >= 0 && t < arr[j-1];j--)
        {
            //            if(t < arr[j-1])
            //            {
            arr[j] = arr[j-1];
            //            }
            //            else {
            //                break;
            //            }
        }
        arr[j] = t;
    }
}
void shellsort(int *arr, int n)
{
    int i,j,t;
    int gap = n/2;
    while(gap >= 1)
    {
        for(i = gap;i < n;i++)
        {
            t = arr[i];
            for(j = i;j-gap >= 0 && t < arr[j-gap];j-=gap)
            {
                arr[j] = arr[j-gap];
            }
            arr[j] = t;
        }
        gap = gap/2;
    }
}

void selectsort(int *arr, int n)
{
    for(int i=0;i < n-1;i++)
    {
        int k = i;
        for(int j = i+1;j < n;j++)
        {
            if(arr[j] < arr[k])
            {
                k = j;
            }
        }
        if(k != i)
        {
            arr[i] ^= arr[k];
            arr[k] ^= arr[i];
            arr[i] ^= arr[k];
        }
    }
}
void quicksort(int *arr, int low ,int high)
{
    if(low < high)
    {
        int pivot = arr[low],l = low,h = high;
        while (l < h)
        {
            while (l < h && arr[h] >= pivot) //大而移动，小而赋值
            {
                h--;
            }
            arr[l] = arr[h];
            while (l < h && arr[l] <= pivot) //小而移动，大而赋值
            {
                l++;
            }
            arr[h] = arr[l];
        }
        arr[h] = pivot;
        quicksort(arr,low,h-1);
        quicksort(arr,h+1,high);
    }
}

void mergetwoorderedarray(int *a,int an,int *b,int bn,int *c,int cn)
{
    int i=0,j=0,k=0;
    while (i != an && j != bn)
    {
        if(a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else {
            c[k++] = b[j++];
        }
    }
    if(i == an)
    {
        while (j != bn) {
            c[k++] = b[j++];
        }
    }
    else {
        while (i != an) {
            c[k++] = a[i++];
        }
    }
}
void merge_twoorderedpart_in_array(int *arr,int *tmp,int start,int mid,int end)
{
    int i = start,j = mid+1,k = start;

    while ((i != mid+1) && (j != end+1))
    {
        if(arr[i] < arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else {
            tmp[k++] = arr[j++];
        }
    }
    if(i == mid+1)
    {
        while (j != end+1) {
            tmp[k++] = arr[j++];
        }
    }
    else {
        while (i != mid+1) {
            tmp[k++] = arr[i++];
        }
    }

    while (start <= end) {
        arr[start] = tmp[start];
        start++;
    }
}

void mergesort(int *arr,int *tmp,int start,int end)
{
    if(start < end)
    {
        int mid = (start+end)/2;
        mergesort(arr,tmp,start,mid);
        mergesort(arr,tmp,mid+1,end);
        merge_twoorderedpart_in_array(arr,tmp,start,mid,end);
    }
}

int binarysearch_iteration(int *arr,int low,int high,int find)
{
    int mid = 0;
    while (low <= high)
    {
        mid = (low+high)/2;
        if(arr[mid] == find)
        {
            return mid;
        }
        else if (find < arr[mid]) {
            high = mid-1;
        }else {
            low = mid+1;
        }
    }
    return -1;
}
int binarysearch_recursive(int *arr,int low,int high,int find)
{
    int mid = 0;
    if(low <= high)
    {
        mid = (low+high)/2;
        if(arr[mid] == find)
        {
            return mid;
        }
        else if (find < arr[mid])
        {
            return binarysearch_recursive(arr,low,mid-1,find);
        }
        else {
            return binarysearch_recursive(arr,mid+1,high,find);
        }
    }
    return -1;
}

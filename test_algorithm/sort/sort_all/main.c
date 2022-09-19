#include <stdio.h>
#include <stdlib.h>
#include "sort_all.h"

void printArr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar(10);
}

int compare(const void *pa, const void *pb)
{
    return *(int *)pa - *(int *)pb;
}

void test_qsort_and_binary_search()
{
    int arr[] = {50, 13, 27, 45, 1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 100, 200};
    int n = sizeof(arr) / sizeof(*arr);
    printf("n = %d\n", n);
    printArr(arr, n);
    qsort(arr, n, sizeof(*arr), compare);
    printArr(arr, n);

    int find = 7;
    // int index = binarysearch_iteration(arr,0,n-1,find);
    int index = binarySearch_recursive(arr, 0, n - 1, find);
    printf("%d index is %d\n", find, index);
}

void test_mergeTwoOrderedArray()
{
    int a[5] = {1, 3, 5, 7, 9};
    int b[7] = {2, 4, 6, 8, 10, 100, 200};
    
    // int c[10];
    // mergeTwoOrderedArray(a, 4, b, 4, c, 10);
    int an=sizeof(a)/sizeof(a[0]), bn = sizeof(b)/sizeof(b[0]);
    const int cn = an + bn;
    int c[12];
    mergeTwoOrderedArray(a, an, b, bn, c, cn);
    printArr(c, cn);
}

void test_merge_twoOrderedPart_in_array()
{
    int arr[] = {1, 3, 5, 7, 9, 300, 2, 4, 6, 8, 10, 100, 200};
    int n = sizeof(arr) / sizeof(*arr);
    int tmp[48] = {0};

    merge_twoOrderedPart_in_array(arr, tmp, 0, 5, n-1);
    printArr(arr, n);
}

int test_mergeSort()
{
    int arr[] = {50, 13, 27, 45, 1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 100, 200};
    int n = sizeof(arr) / sizeof(*arr);
    int tmp[48] = {0};

    printArr(arr, n);
    mergeSort(arr, tmp, 0, n - 1);
    printArr(arr, n);
}

/*
    二叉堆
                        1
                    /       \
                  3          5
              7      9     2   4
            6   8  10
*/

int main()
{
    //           0  1  2  3  4  5  6  7  8  9
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArr(arr, sizeof(arr) / sizeof(arr[0]));

    // bubbleSort(arr, sizeof(arr) / sizeof(*arr));
    // printArr(arr, n);

    // insertsort(arr, n);
    // printArr(arr, n);

    // shellsort(arr, n);
    // printArr(arr, n);

    // selectsort(arr, n);
    // printArr(arr, n);

    // quickSort(arr, 0, 9);
    // printArr(arr, n);

    // heapSort(arr, n);
    // printArr(arr, n);

    // test_mergeTwoOrderedArray();
    // test_merge_twoOrderedPart_in_array();
    // test_mergeSort();

    test_qsort_and_binary_search();

    return 0;
}

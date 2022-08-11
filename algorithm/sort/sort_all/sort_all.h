#ifndef SORT_ALL_H
#define SORT_ALL_H

void bubblesort(int *arr,int n);
void insertsort(int *arr, int n);
void shellsort(int *arr, int n);
void selectsort(int *arr, int n);
void quicksort(int *arr, int low ,int high);
void mergetwoorderedarray(int *a, int an, int *b, int bn, int *c, int cn);
void merge_twoorderedpart_in_array(int *arr,int *tmp,int start,int mid,int end);
void mergesort(int *arr, int *tmp, int start, int end);

int binarysearch_iteration(int *arr,int low,int high,int find);
int binarysearch_recursive(int *arr,int low,int high,int find);

#endif // SORT_ALL_H

#ifndef SORT_ALL_H
#define SORT_ALL_H

void bubbleSort(int *arr, int n);
void insertSort(int *arr, int n);
void shellSort(int *arr, int n);
void selectSort(int *arr, int n);
void quickSort(int *arr, int low, int high);
void mergeTwoOrderedArray(int *a, int an, int *b, int bn, int *c, int cn);
void merge_twoOrderedPart_in_array(int *arr, int *tmp, int start, int mid, int end);
void mergeSort(int *arr, int *tmp, int start, int end);
void heapSort(int *arr, int n);

int binarySearch_iteration(int *arr, int low, int high, int find);
int binarySearch_recursive(int *arr, int low, int high, int find);

#endif // SORT_ALL_H

#include <iostream>

using namespace std;

void mergeTwoOrderedArray(int* a, int an, int* b, int bn, int* c, int cn)
{
    int i = 0, j = 0, k = 0;
    while (i <= an && j <= bn) {
        if (a[i] < b[j]) {
            c[k++] = a[i++];
        }
        else {
            c[k++] = b[j++];
        }
    }

    while (i <= an) // 如果a数组里有元素，放到数组末尾
    {
        c[k++] = a[i++];
    }
    while (j <= bn) // 如果b数组里有元素，放到数组末尾
    {
        c[k++] = b[j++];
    }
}

void merge_twoOrderedPart_in_array(int* arr, int* tmp, int start, int mid, int end)
{
    int i = start; // 左半区第一个未排序的元素
    int j = mid + 1; // 右半区第一个未排序的元素
    int k = start; // 临时数组起始下标

    // 合并左右半区数组元素到临时数组
    // 0 <= 0 && 1 <= 1
    while ((i <= mid) && (j <= end)) {
        if (arr[i] < arr[j]) // 左半区元素更小
        {
            tmp[k++] = arr[i++];
        }
        else // 右半区元素更小
        {
            tmp[k++] = arr[j++];
        }
    }

    // 合并左半区剩余元素
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    // 合并右半区剩余元素
    while (j <= end) {
        tmp[k++] = arr[j++];
    }

    // 拷贝回原数组
    while (start <= end) {
        arr[start] = tmp[start];
        start++;
    }
}

/*
    最好、最坏、平均时间复杂度都为O(logn). 稳定性:稳定
    归并排序是一个外排序，需要申请额外空间
    实现逻辑:
        1.采用分治的思想，先把一个数组分成一个个只包含一个元素的小数组
        2.再把小数组进行归并。直至左半区和右半区合成一个大数组
*/
void mergeSort(int* arr, int* tmp, int start, int end)
{
    // 如果只有一个元素那么就不需要继续划分
    // 只有一个元素的区域，本来就是有序的，只需要归并即可
    if (start < end) // 0 < 1       // 【递归结束条件】
    {
        // 找中间点
        int mid = (start + end) / 2; // start=0, end=1, mid=0, (0 + 1)/2 = 0
        // 递归划分左半区
        mergeSort(arr, tmp, start, mid); // mergeSort(arr, tmp, 0, 0)
        // 递归划分右半区
        mergeSort(arr, tmp, mid + 1, end); // mergeSort(arr, tmp, 1, 1)
        // 合并已排好序的左右半区
        merge_twoOrderedPart_in_array(arr, tmp, start, mid, end);
    }
}

int main()
{

    return 0;
}
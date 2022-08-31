#include "sort_all.h"
#include <stdio.h>
#include <stdlib.h>


/*
    最好时间复杂度：O(n), 最坏、平均时间复杂度:O(n2). 稳定性:不稳定。
    逻辑：
        1.相邻数组两两比较。如果大于就交换。
        2.外层循环需要循环n-1次。
        3.内层循环需要循环n-1-i次。(每一趟比较完，要减去末尾元素)
        4.直至不能两两比较。
*/
void bubbleSort(int *arr, int n)
{
    int flag = 1;
    for (int i = 0; i < n - 1; i++)
    {
        flag = 1;   //冒泡的改进，若在一趟中没有发生逆序，则该序列已有序
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                arr[j] ^= arr[j + 1];
                arr[j + 1] ^= arr[j];
                arr[j] ^= arr[j + 1];
                flag = 0;
            }
        }
        if (flag)
        {
            break;
        }
    }
}

/*
    最好时间复杂度：O(n), 最坏、平均时间复杂度:O(n2). 稳定性:稳定。
    实现逻辑:
        将第一个元素作为已排序序列，第2~n个元素作为未排序序列。
        从未排序序列中每次取一个和排序序列中的元素相比较，如果比要插入的元素大则往后移，知道找到要插入的位置。
*/
void insertSort(int *arr, int n)
{
    int i, j, t;
    for (i = 1; i < n; i++)
    {
        t = arr[i]; // 要插入的元素
        for (j = i; j - 1 >= 0 && arr[j - 1] > t; j--)  // 如果前一个元素比要插入元素大，则往后移
        {
            //            if(t < arr[j-1])
            //            {
            arr[j] = arr[j - 1];
            //            }
            //            else {
            //                break;
            //            }
        }
        arr[j] = t; // 插入
    }
}

/*
    最好、最坏、平均时间复杂度:O(logn). O(n1.3) 稳定性:不稳定。
    希尔排序的基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，
                        待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序。
    
*/
void shellSort(int *arr, int n)
{
    int i, j, t;
    int gap = n / 2;    // 分组
    while (gap >= 1)
    {
        // 把距离为gap的编为一个组，扫描所有组
        for (i = gap; i < n; i++)
        {
            t = arr[i];
            // 对距离为gap的元素组进行插入排序
            for (j = i; j - gap >= 0 && arr[j - gap] > t; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = t;
        }
        gap = gap / 2;
    }
}

/*
    最好、最坏、平均时间复杂度都为O(n2). 稳定性:不稳定
    实现逻辑:
        第一趟: 在1~n的范围内查找最小元素，和第一个元素(0)交换
        第二趟: 在2~n的范围内查找最小元素，和第二个元素(1)交换
        第n趟:  在i~n的范围内查找最小元素，和第i-1个元素交换
*/
void selectSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int k = i;  // 初始值
        for (int j = i + 1; j < n; j++) // 查找最小值
        {
            if (arr[j] < arr[k])
            {
                k = j;
            }
        }

        if (k != i) // 交换最小值
        {
            arr[i] ^= arr[k];
            arr[k] ^= arr[i];
            arr[i] ^= arr[k];
        }
    }
}

/*
    最好、平均时间复杂度都为O(logn), 最坏为O(n2). 稳定性:不稳定

*/
void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[low], l = low, h = high;
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
        quickSort(arr, low, h - 1);
        quickSort(arr, h + 1, high);
    }
}

void mergeTwoOrderedArray(int *a, int an, int *b, int bn, int *c, int cn)
{
    int i = 0, j = 0, k = 0;
    while (i != an && j != bn)
    {
        if (a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else
        {
            c[k++] = b[j++];
        }
    }
    if (i == an)
    {
        while (j != bn)
        {
            c[k++] = b[j++];
        }
    }
    else
    {
        while (i != an)
        {
            c[k++] = a[i++];
        }
    }
}
void merge_twoOrderedPart_in_array(int *arr, int *tmp, int start, int mid, int end)
{
    int i = start, j = mid + 1, k = start;

    while ((i != mid + 1) && (j != end + 1))
    {
        if (arr[i] < arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
    }
    if (i == mid + 1)
    {
        while (j != end + 1)
        {
            tmp[k++] = arr[j++];
        }
    }
    else
    {
        while (i != mid + 1)
        {
            tmp[k++] = arr[i++];
        }
    }

    while (start <= end)
    {
        arr[start] = tmp[start];
        start++;
    }
}

void mergeSort(int *arr, int *tmp, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(arr, tmp, start, mid);
        mergeSort(arr, tmp, mid + 1, end);
        merge_twoOrderedPart_in_array(arr, tmp, start, mid, end);
    }
}

/*
    最好、最坏、平均时间复杂度都是O(logn). 稳定性:不稳定
    二叉堆：
        大顶堆：每个节点都大于其左孩子和右孩子
        小顶堆：每个节点都小于其左孩子和右孩子

    1.创建堆(底层容器：vector) 把数组变成完全二叉树
    2.交换堆顶和堆底元素(交换数组第一个和最后一个)
    3.begin ~ end-1 ---> 重新调整堆

    堆的调整：
        对于一颗完全二叉树，某个节点的左孩子是2i+1,右孩子是2i+2
        起始构建堆的时候可以从[length/2 - 1](最后一个父节点/一个非叶子节点)那个节点开始。
        中间调整堆时，从end-1到0依次遍历节点和其左右孩子比较并交换，重复此步骤至排好序。
*/

void swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void buildHeap(int *arr, int i, int len)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < len && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < len && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr, i, largest);
        buildHeap(arr, largest, len);
    }
}

void heapSort(int *arr, int n)
{
    // 构造一个二叉堆
    for (int i = (n / 2 - 1); i >= 0; --i)
    {
        buildHeap(arr, i, n);
    }

    int len = n;
    // 交换堆顶和末尾的节点，再重新构造堆
    for (int i = len - 1; i > 0; i--)
    {
        swap(arr, 0, i);
        --len;
        buildHeap(arr, 0, len); // 从堆顶开始调整堆
    }
}

int binarySearch_iteration(int *arr, int low, int high, int find)
{
    int mid = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == find)
        {
            return mid;
        }
        else if (find < arr[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int binarySearch_recursive(int *arr, int low, int high, int find)
{
    int mid = 0;
    if (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == find)
        {
            return mid;
        }
        else if (find < arr[mid])
        {
            return binarySearch_recursive(arr, low, mid - 1, find);
        }
        else
        {
            return binarySearch_recursive(arr, mid + 1, high, find);
        }
    }
    return -1;
}

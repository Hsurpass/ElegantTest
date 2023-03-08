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
        flag = 1; //冒泡的改进，若在一趟中没有发生逆序，则该序列已有序
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
        t = arr[i];                                    // 要插入的元素
        for (j = i; j - 1 >= 0 && arr[j - 1] > t; j--) // 如果前一个元素比要插入元素大，则往后移
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
    最好、最坏、平均时间复杂度:O(logn). O(n1.3).O(n1.5) 稳定性:不稳定。
    希尔排序的基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，
                        待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序。
    希尔排序是插入排序的一种优化。
    先分组再进行插入排序，不断减小gap值(除以2)直至gap为1。为1的时候就是直接插入排序了。
*/
void shellSort(int *arr, int n)
{
    int i, j, t;
    int gap = n / 2; // 分组
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
        int k = i;                      // 初始值
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
    最差情况是：每次选基准值都是最小值或者最大值。
    实现逻辑:
        1.先在数组中选中一个基准值。
        2.分组，把小于等于基准值的都放到左边，把大于基准值的都放到右边。
        3.再对每个子组重复进行1,2步操作。
*/

int partitionIndex(int *arr, int low, int high)
{
    int pivot = arr[low], l = low, h = high;
    while (l < h) // 相等的时候把pivot赋值
    {
        // 一定要有l<h这个条件，否则相遇之后还会h--，l++而造成交换元素
        while (/**/ l < h && /**/ arr[h] >= pivot) //大而移动，小而赋值
        {
            h--;
        }
        arr[l] = arr[h];
        while (/**/ l < h && /**/ arr[l] <= pivot) //小而移动，大而赋值
        {
            l++;
        }
        arr[h] = arr[l];
    }
    arr[h] = pivot;

    return l;
}

void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
#if 0
        int pivot = arr[low], l = low, h = high;
        while (l < h) // 相等的时候把pivot赋值
        {
            // 一定要有l<h这个条件，否则相遇之后还会h--，l++而造成交换元素
            while (/**/ l < h && /**/ arr[h] >= pivot) //大而移动，小而赋值
            {
                h--;
            }
            arr[l] = arr[h];
            while (/**/ l < h && /**/ arr[l] <= pivot) //小而移动，大而赋值
            {
                l++;
            }
            arr[h] = arr[l];
        }
        arr[h] = pivot;
#endif
#if 1
        int h = partitionIndex(arr, low, high);
#endif
        quickSort(arr, low, h - 1);
        quickSort(arr, h + 1, high);
    }
}

void mergeTwoOrderedArray(int *a, int an, int *b, int bn, int *c, int cn)
{
    int i = 0, j = 0, k = 0;
    while (i <= an && j <= bn)
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

    while (i <= an) // 如果a数组里有元素，放到数组末尾
    {
        c[k++] = a[i++];
    }
    while (j <= bn) // 如果b数组里有元素，放到数组末尾
    {
        c[k++] = b[j++];
    }
}

void merge_twoOrderedPart_in_array(int *arr, int *tmp, int start, int mid, int end)
{
    int i = start;   // 左半区第一个未排序的元素
    int j = mid + 1; // 右半区第一个未排序的元素
    int k = start;   // 临时数组起始下标

    // 合并左右半区数组元素到临时数组
    // 0 <= 0 && 1 <= 1
    while ((i <= mid) && (j <= end))
    {
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
    while (i <= mid)
    {
        tmp[k++] = arr[i++];
    }
    // 合并右半区剩余元素
    while (j <= end)
    {
        tmp[k++] = arr[j++];
    }

    // 拷贝回原数组
    while (start <= end)
    {
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
void mergeSort(int *arr, int *tmp, int start, int end)
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

/*
    最好、最坏、平均时间复杂度都是O(logn). 稳定性:不稳定
    二叉堆：
        大顶堆：每个节点都大于其左孩子和右孩子
        小顶堆：每个节点都小于其左孩子和右孩子

    1.创建堆(底层容器：vector) 把数组变成完全二叉树，建堆过程其实也是结点下沉的过程。
    2.交换堆顶和堆底元素(交换数组第一个和最后一个)
    3.begin ~ end-1 ---> 重新调整堆

    堆的调整：
        对于一颗完全二叉树，某个节点的左孩子是2i+1,右孩子是2i+2
        起始构建堆的时候可以从[(length-1)/2](最后一个非叶子节点)那个节点开始。
        中间调整堆时，从end-1到0依次遍历节点和其左右孩子比较并交换，重复此步骤至排好序。
*/

void swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void downAdjust(int *arr, int i, int len)
{
    int left = 2 * i + 1;   // 左孩子
    int right = 2 * i + 2;  // 右孩子
    int largest = i;    // 要交换的下标

    // 大顶堆：下沉：根节点和左右孩子比较，选择**较大**的那个进行交换。
    // left<len 的作用是防止数组越界，因为2i+1、2i+2的节点有可能超过了数组长度
    if (left < len && arr[left] > arr[largest]) 
    {
        largest = left;
    }
    if (right < len && arr[right] > arr[largest])   // 左右孩子都要比较，选较小的那个
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr, i, largest);
        downAdjust(arr, largest, len);
    }
}

void buildHeap(int* arr, int n)
{
    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        downAdjust(arr, i, n);
    }
}

void heapSort(int *arr, int n)
{
    // 构造一个二叉堆
    // 从最后一个非叶子结点开始调整，调整倒数第二个非叶子结点，调整倒数第三个非叶子结点 ... 直到根节点。
    // 一颗含有n个结点的完全二叉树，如果从0开始编号，那么编号**大于**(n-1)/2的结点均没有孩子结点(即叶子结点)，(n-1)/2号结点为最后一个非叶子结点。
    // 建堆的过程其实也是结点下沉的过程。
    buildHeap(arr, n);

    int len = n;
    // 交换堆顶和末尾的节点，再重新构造堆
    for (int i = len - 1; i > 0; i--)
    {
        swap(arr, 0, i);    // 堆顶元素和最后一个元素交换
        // --len;
        downAdjust(arr, 0, i); // 从堆顶开始调整堆
    }
}

/*
    二分查找: 复杂度O(logn)
    前提是序列必须是有序的。
*/
int binarySearch_iteration(int *arr, int low, int high, int find)
{
    int mid = 0;
    // 循环结束条件  当high>low时表示没查找到，
    // 一定要有等号，让high往前移；没等号也会少比一次
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
    // return low;  // 如何找到插入元素的位置？只需要返回low那个位置
    return -1;
}

int binarySearch_recursive(int *arr, int low, int high, int find)
{
    int mid = 0;
    if (low <= high)    // 递归结束条件
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

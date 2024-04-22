#include <iostream>

using namespace std;

/*
    最好、平均时间复杂度都为O(nlogn), 最坏为O(n2). 稳定性:不稳定
    最差情况是：每次选基准值都是最小值或者最大值。
    基准值的选取：
        1.一般选择数组中的第一个元素，适用于随机序列，对有序序列效果不太理想。
        2.三数取中：选择数组的第一个、中间一个和最后一个，然后选取数据值居中的那个元素。
    实现逻辑:
        1.先在数组中选中一个基准值。
        2.分组，把小于等于基准值的都放到左边，把大于基准值的都放到右边。
        3.再对每个子组重复进行1,2步操作。
*/

int partitionIndex(int* arr, int low, int high)
{
    int pivot = arr[low], l = low, h = high;
    while (l < h) // 相等的时候把pivot赋值
    {
        // 一定要有l<h这个条件，否则相遇之后还会h--，l++而造成交换元素
        // 一定要有等号，数据交换完后l、h要前进一步，否则不停的交换元素陷入死循环。
        while (/**/ l < h && /**/ arr[h] >= pivot) // 大而移动，小而赋值
        {
            h--;
        }
        arr[l] = arr[h];
        while (/**/ l < h && /**/ arr[l] <= pivot) // 小而移动，大而赋值
        {
            l++;
        }
        arr[h] = arr[l];
    }
    arr[h] = pivot;

    return l;
}

void quickSort(int* arr, int low, int high)
{
    if (low < high) {
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

int main()
{

    return 0;
}
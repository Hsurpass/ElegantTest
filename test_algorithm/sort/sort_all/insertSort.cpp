#include <iostream>

using namespace std;

/*
    最好时间复杂度：O(n), 最坏、平均时间复杂度:O(n2). 稳定性:稳定。
    实现逻辑:
        将第一个元素作为已排序序列，第2~n个元素作为未排序序列。
        从未排序序列中每次取第一个元素和排序序列中的元素从后往前比较，如果比要插入的元素大则往后移，直到找到要插入的位置。
*/
void insertSort(int* arr, int n)
{
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = arr[i];                                    // 要插入的元素
        for (j = i; j - 1 >= 0 && arr[j - 1] > t; j--) // 如果前一个元素比要插入元素大，则往后移，空出插入位置
        {
            // if(t < arr[j-1])
            // {
            arr[j] = arr[j - 1];
            // }
            // else {
            //      break;
            // }
        }
        arr[j] = t; // 插入
    }
}

int main()
{

    return 0;
}
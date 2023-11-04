#include <iostream>

using namespace std;

/*
    最好、最坏、平均时间复杂度:O(logn). O(n1.3).O(n1.5) 稳定性:不稳定。
    希尔排序的基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，
                        待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序。
    希尔排序是插入排序的一种优化。
    先分组再进行插入排序，不断减小gap值(除以2)直至gap为1。为1的时候就是直接插入排序了。
*/
void shellSort(int* arr, int n)
{
    int i, j, t;
    int gap = n / 2; // 分组
    while (gap >= 1) {
        // 把距离为gap的编为一个组，扫描所有组
        for (i = gap; i < n; i++) {
            t = arr[i];
            // 对距离为gap的元素组进行插入排序
            for (j = i; j - gap >= 0 && arr[j - gap] > t; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = t;
        }
        gap = gap / 2;
    }
}

int main()
{

    return 0;
}
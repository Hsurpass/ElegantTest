#include <iostream>

using namespace std;

/*
    无序区选择一个最小值和无序区中的第一个元素交换，然后无序区长度减1，有序区长度增1。
    最好、最坏、平均时间复杂度都为O(n2). 稳定性:不稳定
    实现逻辑:
        第一趟: 在1~n的范围内查找最小元素，和第一个元素(0)交换
        第二趟: 在2~n的范围内查找最小元素，和第二个元素(1)交换
        第n趟:  在i~n的范围内查找最小元素，和第i-1个元素交换
*/
void selectSort(int* arr, int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min = i; // 初始值
        for (int j = i + 1; j < n; j++) // 查找最小值
        {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (min != i) // 交换最小值
        {
            arr[i] ^= arr[min];
            arr[min] ^= arr[i];
            arr[i] ^= arr[min];
        }
    }
}

int main()
{

    return 0;
}
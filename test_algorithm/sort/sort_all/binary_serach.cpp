#include <iostream>

using namespace std;

/*
    二分查找: 复杂度O(logn)
    前提是序列必须是有序的。
*/
int binarySearch_iteration(int* arr, int low, int high, int find)
{
    int mid = 0;
    // 循环结束条件  当high>low时表示没查找到，
    // 一定要有等号，让high往前移；没等号也会少比一次
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == find) {
            return mid;
        }
        else if (find < arr[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    // return low;  // 如何找到插入元素的位置？只需要返回low那个位置
    return -1;
}

int binarySearch_recursive(int* arr, int low, int high, int find)
{
    int mid = 0;
    if (low <= high) // 递归结束条件
    {
        mid = (low + high) / 2;
        if (arr[mid] == find) {
            return mid;
        }
        else if (find < arr[mid]) {
            return binarySearch_recursive(arr, low, mid - 1, find);
        }
        else {
            return binarySearch_recursive(arr, mid + 1, high, find);
        }
    }
    return low;
    // return -1;
}

int main()
{

    return 0;
}
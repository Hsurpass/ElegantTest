#include <iostream>

using namespace std;

/*
    最好时间复杂度：O(n), 最坏、平均时间复杂度:O(n2). 稳定性:不稳定。
    逻辑：
        1.相邻元素两两比较。如果大于就交换。
        2.外层循环需要循环n-1次。
        3.内层循环需要循环n-1-i次。(每一趟比较完，要减去末尾元素)
        4.直至不能两两比较。
*/
void bubbleSort(int* arr, int n)
{
    int flag = 1;
    for (int i = 0; i < n - 1; i++) {
        flag = 1; // 冒泡的改进，若在一趟中没有发生逆序，则该序列已有序
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                arr[j] ^= arr[j + 1];
                arr[j + 1] ^= arr[j];
                arr[j] ^= arr[j + 1];
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
    }
}

int main()
{

    return 0;
}
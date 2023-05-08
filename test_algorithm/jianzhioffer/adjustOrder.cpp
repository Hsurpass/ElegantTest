// 调整整数数组的顺序，使得能被3整除的数位于不能被3整除的数的前面
#include <iostream>

using namespace std;

void adjustOrder(int *arr, int n)
{
    int i = 0, j = n - 1;
    while (i < j)
    {

        if ((arr[i] % 3) == 0)
        {
            i++;
        }
        else
        {
            std::swap(arr[i], arr[j]);
            j--;
        }
    }
}

int main()
{
    int arr[] = {1, 3, 5, 6, 7, 12, 15, 8, 4, 21};
    adjustOrder(arr, sizeof(arr) / sizeof(int));
    for (auto &i : arr)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

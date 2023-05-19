#include <iostream>

using namespace std;

void mergeTwoOrderedList_withTmpArray(int *arr1, int m, int *arr2, int n, int *arr3)
{
    int i = 0, j = 0, k = 0;

    while (i < m && j < n)
    {
        if (arr1[i] < arr2[j])
        {
            arr3[k++] = arr1[i++];
        }
        else
        {
            arr3[k++] = arr2[j++];
        }
    }

    while (i < m)
    {
        arr3[k++] = arr1[i++];
    }
    while (j < n)
    {
        arr3[k++] = arr2[j++];
    }
}

void mergeTwoOrderedList_withoutTmpArray(int *arr1, int m, int *arr2, int n)
{
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0)
    {
        if (arr1[i] > arr2[j])
        {
            arr1[k--] = arr1[i--];
        }
        else
        {
            arr1[k--] = arr2[j--];
        }
    }

    while (j >= 0)
    {
        arr1[k--] = arr2[j--];
    }
}

void test_mergeTwoOrderedList_withoutTmpArray()
{
    int m = 5, n = 6;
    int arr1[m + n] = {1, 3, 5, 7, 9};
    int arr2[n] = {2, 4, 6, 8, 10, 12};

    mergeTwoOrderedList_withoutTmpArray(arr1, m, arr2, n);
    for(auto &i:arr1)
    {
        cout << i << " ";
    }
    cout << endl;
}

void test_mergeTwoOrderedList_withTmpArray()
{
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10};
    int m = sizeof(arr1) / sizeof(int);
    int n = sizeof(arr2) / sizeof(int);
    int len = m + n;
    int arr3[len] = {0};

    mergeTwoOrderedList_withTmpArray(arr1, m, arr2, n, arr3);
    for (auto &i : arr3)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    // test_mergeTwoOrderedList_withTmpArray();
    test_mergeTwoOrderedList_withoutTmpArray();

    return 0;
}
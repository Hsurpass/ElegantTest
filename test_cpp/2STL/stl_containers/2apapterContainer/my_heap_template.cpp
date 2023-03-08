#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

#include "../../../basicClass/A.h"

using namespace std;

void printVector(vector<int> &v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

template<typename T>
void printArr(T *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar(10);
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

template<typename T>
void swap(T *arr, int i, int j)
{
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

template<typename T, bool reverse>
void downAdjust_iterate(T *arr, int i, int len) // i为要调整的节点，len为数组长度
{
    while (i < len)
    {
        int left = 2 * i + 1;  // 左孩子
        int right = 2 * i + 2; // 右孩子
        int largest = i;       // 要交换的下标

        // 大顶堆：下沉：根节点和左右孩子比较，选择**较大**的那个进行交换。
        // left<len 的作用是防止数组越界，因为2i+1、2i+2的节点有可能超过了数组长度
        if (left < len && Comp<T, reverse>()(arr[largest], arr[left]) ) // 如果左子树存在且a[largest]小于左孩子
        {
            largest = left;
        }
        if (right < len && Comp<T, reverse>()(arr[largest], arr[right]) ) // 如果右子树存在且a[largest]小于右孩子
        {
            largest = right;
        }

        if (largest != i) // 递归结束条件
        {
            swap(arr, i, largest);
            i = largest;
        }
        else //(largest == i) 循环结束条件
        {
            break;
        }
    }
}

template<typename T, bool reverse>
void downAdjust(T *arr, int i, int len)
{
    int left = 2 * i + 1;  // 左孩子
    int right = 2 * i + 2; // 右孩子
    int largest = i;       // 要交换的下标

    // 大顶堆：下沉：根节点和左右孩子比较，选择**较大**的那个进行交换。
    // left<len 的作用是防止数组越界，因为2i+1、2i+2的节点有可能超过了数组长度
    if (left < len && Comp<T, reverse>()(arr[largest], arr[left]))
    {
        largest = left;
    }
    if (right < len && Comp<T, reverse>()(arr[largest], arr[right]) ) // 左右孩子都要比较，选较小的那个
    {
        largest = right;
    }

    if (largest != i) // 递归结束条件
    {
        swap(arr, i, largest);
        downAdjust<int, reverse>(arr, largest, len);
    }
}

template<typename T, bool reverse>
void buildHeap(T *arr, int n)
{
    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        downAdjust<int, reverse>(arr, i, n);
    }
}

// 交换堆顶和末尾的节点，再重新调整堆
// i为节点编号
template<typename T, bool reverse>
void popHeap(T *arr, int n)
{
    swap(arr, 0, n);       // 堆顶元素和最后一个元素交换
    downAdjust<int, reverse>(arr, 0, n); // 从堆顶开始调整堆
    // downAdjust_iterate<int, reverse>(arr, 0, n); // 从堆顶开始调整堆
}

// 节点上浮
// 小顶堆：子节点小于父节点进行交换。
// 大顶堆：子节点大于父节点进行交换。
template<typename T, bool reverse>
void upAdjust(T* arr, int child)
{
    int parent = (child - 1) / 2;   // 找到父节点
    while (parent >= 0)  // 防止父节点小于0
    {
        if(Comp<T, reverse>()(arr[parent], arr[child]) )    // 大顶堆上浮：如果父节点比子节点小则交换
        {
            swap(arr, child, parent);
            child = parent;
            parent = (child - 1) / 2;   // 找到父节点
        }
        else
        {
            break;
        }
    }
    
}

// 从最后一个元素开始调整。
template<typename T, bool reverse>
void pushHeap(T* arr, int n)
{
    upAdjust<int, reverse>(arr, n-1);
}

template<typename T, bool reverse>
void heapSort(T *arr, int n)
{
    // 构造一个二叉堆
    // 从最后一个非叶子结点开始调整，调整倒数第二个非叶子结点，调整倒数第三个非叶子结点 ... 直到根节点。
    // 一颗含有n个结点的完全二叉树，如果从0开始编号，那么编号**大于**(n-1)/2的结点均没有孩子结点(即叶子结点)，(n-1)/2号结点为最后一个非叶子结点。
    // 建堆的过程其实也是结点下沉的过程。
    buildHeap<int, reverse>(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        // 交换堆顶和末尾的节点，再重新调整堆
        popHeap<int, reverse>(arr, i);
    }
}

void test_heapsort()
{
    //           0  1  2  3  4  5  6  7  8  9
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArr(arr, sizeof(arr) / sizeof(arr[0]));

    // heapSort<int, false>(arr, n);
    heapSort<int, true>(arr, n);
    
    printArr(arr, n);
}

/*
    建堆：(n-1)/2 --> (5-1)/2 = 2 -->从2号结点开始调整直到根节点
    0  1  2  3  4
    10 20 30 5 15
            10       buildheap       30     popheap         15              20
        20      30  ---------->   20    10 --------->    20    10  -->    15   10
      5   15                     5  15                  5  30            5  30

            20      pushheap     20             99 
         15    10   ------->   99  10   -->   20   10
        5  99                 5  15         5  15
*/
void test_heap02()
{
    int myints[5] = {10, 20, 30, 5, 15};
    std::vector<int> v(myints, myints + 5);
    int n = v.size();

    buildHeap<int, false>(&v[0], n); //建堆
    std::cout << "initial max heap   : " << v.front() << '\n';  // 30
    printVector(v); // 30 20 10 5 15

    popHeap<int, false>(&v[0], n-1);
    printVector(v); // 20 15 10 5 30
    v.pop_back();
    std::cout << "max heap after pop : " << v.front() << '\n';  // 20

    v.push_back(99);
    printVector(v); // 20 15 10 5 99
    pushHeap<int, false>(&v[0], n);
    printVector(v); // 99 20 10 5 15
    std::cout << "max heap after push: " << v.front() << '\n';  // 99

    heapSort<int, false>(&v[0], n);     // 5 10 15 20 99

    std::cout << "final sorted range :";
    for (unsigned i = 0; i < v.size(); i++)
        std::cout << ' ' << v[i];

    std::cout << '\n';
}

int main()
{
    // test_heapsort();
    test_heap02();

    return 0;
}
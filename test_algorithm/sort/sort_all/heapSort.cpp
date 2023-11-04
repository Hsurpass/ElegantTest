#include <iostream>

using namespace std;

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

void swap(int* arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void downAdjust(int* arr, int i, int len)
{
    int left = 2 * i + 1; // 左孩子
    int right = 2 * i + 2; // 右孩子
    int largest = i; // 要交换的下标

    // 大顶堆：下沉：根节点和左右孩子比较，选择**较大**的那个进行交换。
    // left<len 的作用是防止数组越界，因为2i+1、2i+2的节点有可能超过了数组长度
    if (left < len && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < len && arr[right] > arr[largest]) // 左右孩子都要比较，选较小的那个
    {
        largest = right;
    }

    if (largest != i) {
        swap(arr, i, largest);
        downAdjust(arr, largest, len);
    }
}

void buildHeap(int* arr, int n)
{
    for (int i = (n - 1) / 2; i >= 0; --i) {
        downAdjust(arr, i, n);
    }
}

void heapSort(int* arr, int n)
{
    // 构造一个二叉堆
    // 从最后一个非叶子结点开始调整，调整倒数第二个非叶子结点，调整倒数第三个非叶子结点 ... 直到根节点。
    // 一颗含有n个结点的完全二叉树，如果从0开始编号，那么编号**大于**(n-1)/2的结点均没有孩子结点(即叶子结点)，(n-1)/2号结点为最后一个非叶子结点。
    // 建堆的过程其实也是结点下沉的过程。
    buildHeap(arr, n);

    int len = n;
    // 交换堆顶和末尾的节点，再重新构造堆
    for (int i = len - 1; i > 0; i--) {
        swap(arr, 0, i); // 堆顶元素和最后一个元素交换
        // --len;
        downAdjust(arr, 0, i); // 从堆顶开始调整堆
    }
}

int main()
{

    return 0;
}
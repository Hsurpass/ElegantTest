#include "my_heap_template.h"

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

    popHeap<int, false>(&v[0], n);
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
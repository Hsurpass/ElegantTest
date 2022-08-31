#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void test_priQueue()
{
    int arr[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    priority_queue<int> pq(arr, arr + 10);

    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
}

void printVector(vector<int> &v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

/*
                        1
                    /       \
                  3          5
              7      9     2   4
            6   8  10
*/
void test_heap01()
{
    int arr[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    vector<int> vi(arr, arr + 10);
    printVector(vi);

    make_heap(vi.begin(), vi.end());
    printVector(vi);

    vi.push_back(100);
    printVector(vi);

    make_heap(vi.begin(), vi.end());
    printVector(vi);
    cout << "-----------------" << endl;

    while (vi.size() != 0)
    {
        pop_heap(vi.begin(), vi.end());
        cout << "node: " << vi.back() << endl;
        vi.pop_back();
        // printVector(vi);
        // cout << "------------------" << endl;
    }

    // pop_heap:交换首尾元素，并没有真正的弹出back()元素。交换后重新构建堆
    // pop_heap(vi.begin(),vi.end());
    // printVector(vi);
    // pop_heap(vi.begin(),vi.end());
    // printVector(vi);
    // pop_heap(vi.begin(),vi.end());
    // printVector(vi);
    // pop_heap(vi.begin(),vi.end());
    // printVector(vi);

    // sort_heap(vi.begin(), vi.end(), less<int>());
    // printVector(vi); // 1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 100
}

void test_heap02()
{
    int myints[] = {10, 20, 30, 5, 15};
    std::vector<int> v(myints, myints + 5);

    std::make_heap(v.begin(), v.end());
    std::cout << "initial max heap   : " << v.front() << '\n';  // 30

    std::pop_heap(v.begin(), v.end());
    v.pop_back();
    std::cout << "max heap after pop : " << v.front() << '\n';  // 20

    v.push_back(99);
    std::push_heap(v.begin(), v.end());
    std::cout << "max heap after push: " << v.front() << '\n';  // 99

    std::sort_heap(v.begin(), v.end());     // 5 10 15 20 99

    std::cout << "final sorted range :";
    for (unsigned i = 0; i < v.size(); i++)
        std::cout << ' ' << v[i];

    std::cout << '\n';
}

int main()
{
    // test_heap01();
    test_heap02();
}

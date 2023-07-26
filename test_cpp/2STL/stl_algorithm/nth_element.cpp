#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

void test_nth_element_basic()
{
    std::vector<int> nums = {7, 2, 10, 4, 1, 9, 5};

    // Partially sort the vector so that the third element is in its final sorted position
    // 对vector进行部分排序(不是严格有序的)，使第三个位置的元素处于其最终排序位置，
    // 也就是说第n个位置之前的元素都小于第n个位置上的元素，第n个位置之后的元素都大于第n个位置上的元素，排序的时候n位置上的元素是会发生变化的。
    std::nth_element(nums.begin(), nums.begin() + 2, nums.end());

    for (auto i : nums) { // 1 2 4 7 10 9 5
        cout << i << " ";
    }
    cout << endl;
}

void test_nth_element_sort()
{
    vector<int> points = {10, 30, 50, 20, 40, 60, 80};
    vector<int> indices(points.size());
    std::iota(indices.begin(), indices.end(), 0);
    for (auto i : indices) {
        cout << i << " ";
    }
    cout << endl;

    int mid = ((points.size() - 1) / 2);
    // std::nth_element(indices.begin(), indices.begin() + mid, indices.end(), [&](int l, int r) {
    //     return points[l] < points[r];
    // });

    int* p = indices.data();
    std::nth_element(p, p + mid, p + points.size(), [&](int l, int r) {
        return points[l] < points[r];
    });

    for (auto i : indices) {
        cout << i << " ";
    }
    cout << endl;
    for (auto i : indices) {
        cout << points[i] << " ";
    }
    cout << endl;
}

int main()
{
    // test_nth_element_basic();
    test_nth_element_sort();

    return 0;
}
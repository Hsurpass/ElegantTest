#include <iostream>

using namespace std;

// 使用递归方法翻转数组

// 0 1 2 3 4
// 7,5,6,3,8  k=5
//   a   k
//       k-1
//   0 1 2 3
//   k a
void recur(int a[], int k)
{
    int tmp;
    if (k > 1) {
        recur(a + 1, k - 2);
        // cout << "a[k-1]: " << a[k-1] << endl; // a的地址在不断变化
        tmp = a[0];
        a[0] = a[k - 1];
        a[k - 1] = tmp;

        // for(int i = 0; i < k;i++){
        //     cout << a[i] << " ";
        // }
        // cout << endl;
    }
}

int main()
{
    int a[5] = {7, 5, 6, 3, 8};
    recur(a, 5);
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;

    int a1[6] = {1, 2, 3, 4, 5, 6};
    recur(a1, 6);
    for (auto i : a1) {
        cout << i << " ";
    }
    cout << endl;
}
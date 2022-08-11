#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void rotateTest1()
{
    vector<int> v;

    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    cout << *(v.begin() + 3) << endl;

    // 0 1 2 3 4 5 6 7 8 9 
    // 以3为中心翻转序列
    // 3 4 5 6 7 8 9 0 1 2 
    std::rotate(v.begin(), v.begin() + 3, v.end());

    for (vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

void rotateTest2()
{
    vector<int> v;

    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    cout << *(v.begin() + 3) << endl;

    // 0 1 2 3 4 5 6 7 8 9 
    // 以3为中心翻转序列
    // 3 4 5 6 7 8 9 0 1 2 
    std::rotate(v.begin(), v.begin() + 3, v.end());
    // 4 5 6 7 8 9 3 0 1 2
    std::rotate(v.begin(), v.begin() + 1, v.begin() + (v.size() - 3));

    for (vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

int main()
{
    // rotateTest1();
    rotateTest2();

    return 0;
}
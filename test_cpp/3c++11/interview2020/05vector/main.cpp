#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int arr[5] = {10,11,12,13,14};
    vector<int> v;
    v.reserve(20);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.insert(v.end(),arr,arr+5);
    cout << v.size() << endl;
    cout << v.capacity() << endl;

    return 0;
}

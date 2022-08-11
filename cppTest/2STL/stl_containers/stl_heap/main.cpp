#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int arr[10]= {1,3,5,7,9,2,4,6,8,10};
    priority_queue<int> pq(arr,arr+10);

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
}

#if 0
void disvector(vector<int> &v)
{
    for(auto i:v)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    int arr[10]= {1,3,5,7,9,2,4,6,8,10};
    vector<int> vi(arr,arr+10);
    disvector(vi);

    make_heap(vi.begin(),vi.end());
    disvector(vi);
    vi.push_back(100);
    disvector(vi);
    make_heap(vi.begin(),vi.end());
    disvector(vi);
    cout<< "-----------------" << endl;
    while (vi.size() != 0) {
        pop_heap(vi.begin(),vi.end());
        cout << "node: " << vi.back() << endl;
        vi.pop_back() ;
        disvector(vi);
        cout << "------------------" << endl;
    }
//    pop_heap(vi.begin(),vi.end());
//    disvector(vi);
//    pop_heap(vi.begin(),vi.end());
//    disvector(vi);
//    pop_heap(vi.begin(),vi.end());
//    disvector(vi);
//    pop_heap(vi.begin(),vi.end());
//    disvector(vi);

//    sort_heap(vi.begin(),vi.end(),less<int>());
//    disvector(vi);

    return 0;
}
#endif

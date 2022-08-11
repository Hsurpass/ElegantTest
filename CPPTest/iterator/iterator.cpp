#include <iostream>
#include <vector>
using namespace std;


int main()
{
    const vector<int> v = {1,2,3};

    // const 容器对象只能用 const_iterator
    for (vector<int>::const_iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << *itr << " " << endl;
    }

    vector<int> v1 = {4,5,6};
    for (vector<int>::iterator itr = v1.begin(); itr != v1.end(); ++itr)
    {
        *itr = *itr * 2;
    }

    for (vector<int>::const_iterator itr = v1.begin(); itr != v1.end(); ++itr)
    {
        cout << *itr << " " << endl;
    }
    

    return 0;
}

int main01()
{
    vector<int> v;

    // 如果容器为空，则begin和end都是尾后迭代器
    if(v.begin() == v.end())
    {
        cout << "if container is empty, begin and end are end iterator" << endl;
    }

    vector<int>::iterator beginIter = v.begin();

    cout << *beginIter << endl; // segmentation fault

    return 0;
}
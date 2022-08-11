#include <iostream>
#include <queue>
#include <list>

using namespace std;

// houjie STL
// queue默认使用deque作为底层数据结构
void test01()
{
    queue<int> si;

    for (size_t i = 0; i < 10; i++)
    {
        si.push(i);
    }
    cout << si.size() << endl;

    while (!si.empty())
    {
        cout << si.front() << " ";
        si.pop();
    }
    cout << endl;
}

// queue使用list作为底层数据结构
void test02()
{
    queue<int, list<int>> si;

    for (size_t i = 0; i < 10; i++)
    {
        si.push(i);
    }
    cout << si.size() << endl;

    while (!si.empty())
    {
        cout << si.front() << " ";
        si.pop();
    }
    cout << endl;
}

int main()
{
    // test01();
    test02();
    
    return 0;
}
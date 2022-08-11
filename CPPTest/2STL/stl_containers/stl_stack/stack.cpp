#include <iostream>
#include <stack>
#include <list>
#include <vector>

using namespace std;

// houjie STL
// stack默认使用deque作为底层数据结构
void test01()
{
    stack<int> si;

    for (size_t i = 0; i < 10; i++)
    {
        si.push(i);
    }
    cout << si.size() << endl;

    while (!si.empty())
    {
        cout << si.top() << " ";
        si.pop();
    }
    cout << endl;
}

// stack使用list作为底层数据结构
void test02()
{
    stack<int, list<int>> si;

    for (size_t i = 0; i < 10; i++)
    {
        si.push(i);
    }
    cout << si.size() << endl;

    while (!si.empty())
    {
        cout << si.top() << " ";
        si.pop();
    }
    cout << endl;
}

// stack使用vector作为底层数据结构
void test03()
{
    stack<int, vector<int>> si;

    for (size_t i = 0; i < 10; i++)
    {
        si.push(i);
    }
    cout << si.size() << endl;

    while (!si.empty())
    {
        cout << si.top() << " ";
        si.pop();
    }
    cout << endl;
}

int main()
{
    // test01();
    // test02();
    test03();

    return 0;
}
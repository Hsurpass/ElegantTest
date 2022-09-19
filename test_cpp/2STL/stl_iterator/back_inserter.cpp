#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

// 只具备push_back函数的容器才能调用back_inserter(), such as: vector、list、deque

// 使用copy()的程序员需要自己保证，目标容器的大小大于等于源容器。
// 使用插入迭代器(insert iterator)向容器中插入元素。back_inserter()定义在头文件iterator中。
// 接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器，通过此迭代器赋值会调用push_back添加元素到容器。
void test_back_inserter()
{
    vector<int> vi1, vi2;
    for(int i = 0; i < 10; i++)
    {
        vi1.push_back(i);
    }
    // std::copy(vi1.begin(), vi1.end(), vi2.begin());
    std::copy(vi1.begin(), vi1.end(), back_inserter(vi2));

    for(auto &i:vi2)
    {
        cout << i << " ";
    }
    cout << endl;

}

int main()
{
    test_back_inserter();

}
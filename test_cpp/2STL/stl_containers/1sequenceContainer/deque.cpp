#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <string>
#include <memory>

#include "../../../../basicClass/A.h"

using namespace std;

void test_erase()
{
    deque<A> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(5); // size:5, 无capacity

    cout << v.size() << endl;
    cout << "==================" << endl;

    deque<A>::iterator itr;
    itr = std::find(v.begin(), v.end(), A(2)); // 自定义类使用std::find 需要自定义 operator==()
    if (itr != v.end())
    {
        cout << itr->print() << endl;
        itr = v.erase(itr); // erase 会造成迭代器失效，元素会前移, 前移会造成元素copy(call operator=())
        cout << itr->print() << endl;
    }
    else
    {
        cout << "find none" << endl;
    }

    cout << "==================" << endl;
    cout << v.size() << endl;     // 4
}

int main()
{
    test_erase();  

    return 0;
}
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

#include "../../../basicClass/A.h"

using namespace std;

template <typename T>
class comp
{
public:
    comp(bool reverse = false) : m_reverse(reverse) {}
    ~comp() {}

    bool operator()(const T& one, const T& other)
    {
        if (m_reverse)
        {
            return one > other;
        }
        else
        {
            return one < other;
        }
    }

private:
    bool m_reverse;
};

class B
{
public:
    B(int b) : m_b(b) {}

    bool operator<(const B &other) const // 必须是const成员函数
    {
        return this->m_b < other.m_b;
    }
    friend bool operator>(const B &one, const B &other) { return !(one < other); }

    int m_b;
};

// class compare
// {
// public:
//     compare(bool reverse = false) : m_reverse(reverse) {}
//     ~compare() {}

//     bool operator()(const B &one, const B &other)
//     {
//         if (m_reverse)
//         {
//             // return one.m_b > other.m_b;
//             return one > other;
//         }
//         else
//         {
//             // return one.m_b < other.m_b;
//             return one < other;
//         }
//     }

// private:
//     bool m_reverse;
// };

void test_priority_queue_withClass_functor()
{
    // std::priority_queue<B> pb;   // default:大顶堆
    // std::priority_queue<B, vector<B>, std::less<B>> pb;   // 大顶堆
    // std::priority_queue<B, vector<B>, std::greater<B>> pb;  // 小顶堆
    // std::priority_queue<B, vector<B>, std::greater<vector<B>::value_type>> pb; // 小顶堆

    // std::priority_queue<B, vector<B>, compare> pb;   // 大顶堆
    // std::priority_queue<B, vector<B>, compare> pb(compare(true));   // 小顶堆
    std::priority_queue<B, vector<B>, comp<B>> pb(comp<B>(true));   // 小顶堆

    pb.emplace(100);
    pb.emplace(500);
    pb.emplace(300);

    while (!pb.empty())
    {
        cout << pb.top().m_b << " ";
        pb.pop();
    }
    cout << endl;
}

void test_priority_queue_withClass()
{
    // std::priority_queue<A> pa;   // default:大顶堆
    // std::priority_queue<A, vector<A>, std::less<A>> pa; // 大顶堆
    std::priority_queue<A, vector<A>, std::greater<A>> pa;  // 小顶堆
    // std::priority_queue<A, vector<A>, std::greater<vector<A>::value_type> > pa;  // 小顶堆

    pa.emplace(10);
    pa.emplace(5000);
    pa.emplace(100);

    while (!pa.empty())
    {
        cout << pa.top().geta() << " ";
        pa.pop();
    }
    cout << endl;
}

void test_priority_queue()
{
    // priority_queue<int> pqi; // 大顶堆
    priority_queue<int, std::vector<int>, std::greater<int>> pqi;   // 小顶堆
    pqi.push(10);
    pqi.push(5);
    pqi.push(100);

    // 5 10 100
    while (!pqi.empty())
    {
        cout << pqi.top() << " ";
        pqi.pop();
    }
    cout << endl;
}

int main()
{
    // test_priority_queue();
    // test_priority_queue_withClass();
    test_priority_queue_withClass_functor();

    return 0;
}
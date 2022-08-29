#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <time.h>

using namespace std;

class A
{
public:
    A(int a):m_a(a) {}

    // bool operator==(const A& other) { return this->m_a == other.m_a; }
    void dis() const { cout << m_a << endl; }
// private:
    int m_a;
};

bool operator==(const A& one, const A& other) { return one.m_a == other.m_a; }

struct hash_A
{
    int operator()(const A& a) const { return a.m_a; }
};

void test_unordered_set01()
{
    unordered_set<int> si;

    clock_t timeStart = clock();

    for (size_t i = 0; i < 100000; i++)
    {
        si.insert(i);
    }

    cout << "millions-seconds:" << (clock() - timeStart) << endl;

    cout << "nums count:" << si.size() << endl;
    cout << "bucket[20] size:" << si.bucket_size(20) << endl;
    cout << "bucket count:" << si.bucket_count() << endl;
    cout << "max bucket count:" << si.max_bucket_count() << endl;
    cout << "load factor:" << si.load_factor() << endl;
    cout << "max load factor:" << si.max_load_factor() << endl;

    timeStart = clock();
    auto itr = std::find(si.begin(), si.end(), 999);
    cout << "std::find millions-seconds:" << (clock() - timeStart) << "," << *itr << endl;

    timeStart = clock();
    itr = si.find(999);
    cout << "std::find millions-seconds:" << (clock() - timeStart) << "," << *itr << endl;
    si.clear();
}

void test_unordered_set_with_class()
{
    std::unordered_set<A, hash_A> ua;
    cout << "ua.bucket_count:" << ua.bucket_count() << endl;
    ua.insert(A(2));
    ua.insert(A(3));
    ua.insert(A(1));
    ua.insert(A(4));
    cout << "ua.bucket_count:" << ua.bucket_count() << endl;

    for (auto itr = ua.begin(); itr != ua.end(); ++itr) 
    {
        itr->dis();
    }

    cout << "------------------" << endl;

    for(int i = 0;i < ua.bucket_count(); i++)
    {
        cout << "bucket[" << i << "] count:" << ua.bucket_size(i) << endl;
        for (auto itr = ua.begin(i); itr != ua.end(i); ++itr)
        {
            itr->dis();
        }
    }

    // auto itr = ua.find(A(2));
    // itr->dis();
}

int main()
{
    // test_unordered_set01();
    test_unordered_set_with_class();

    return 0;
}
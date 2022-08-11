#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <time.h>

using namespace std;

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

int main()
{
    test_unordered_set01();

    return 0;
}
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include <time.h>

using namespace std;

void test_sizeof_multiset()
{
    std::multiset<int, std::less<int>> ms;
    cout << sizeof(ms) << endl;  // 48
    cout << sizeof(std::multiset<char>) << endl; // 48

}

void test_stdFind_and_mutisetFind_elapsedTime()
{
    std::multiset<int> ms;

    clock_t timeStart = clock();
    for (size_t i = 0; i < 1000000; i++)
    {
        ms.insert(rand());
    }
    cout << "milliseconds: " << clock() - timeStart << endl;
    cout << "multiset size: " << ms.size() << endl;
    cout << "multiset max size: " << ms.max_size() << endl;

    {
        timeStart = clock();
        multiset<int>::iterator itr = std::find(ms.begin(), ms.end(), 111);
        if (itr != ms.end())
        {
            cout << "FOUND" << endl;
        }
        else{
            cout << "NOT FOUND" << endl;
        }
        cout << "std::find elapse milliseconds: " << clock() - timeStart << endl;
    }

    {
        timeStart = clock();
        multiset<int>::iterator itr = ms.find(111);
        if (itr != ms.end())
        {
            cout << "FOUND" << endl;
        }
        else{
            cout << "NOT FOUND" << endl;
        }
        cout << "multiset::find elapse milliseconds: " << clock() - timeStart << endl;
    }

    // for (multiset<int>::iterator itr = ms.begin(); itr != ms.end(); ++itr)
    // {
    //     cout << *itr << " ";
    // }
    // cout << endl;
    
    ms.clear();
}

int main()
{
    // test_sizeof_multiset();
    test_stdFind_and_mutisetFind_elapsedTime();

    return 0;
}
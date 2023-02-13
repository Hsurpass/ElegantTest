#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "../../../basicClass/A.h"

using namespace std;

void test_unordered_multimap()
{
    unordered_multimap<string, string> mss;
    mss = {
        {"Australia", "Canberra"},
        {"U.S.", "Washington"},
        {"France", "Paris"},
        // {"U.S.", "luck"}
    };
    cout << "bucket_count:" << mss.bucket_count() << endl;
    mss.insert({"U.S.", "luck"});
    cout << "bucket_count:" << mss.bucket_count() << endl;

    cout << "mss contains:" << endl;
    for (auto it = mss.begin(); it != mss.end(); ++it)
        cout << " " << it->first << ":" << it->second << endl;

    cout << endl;
    cout << "mss's buckets contain:\n";
    for (unsigned i = 0; i < mss.bucket_count(); ++i)
    {
        cout << "bucket #" << i << " contains " << mss.bucket_size(i) << ":" << endl;
        for (auto itr = mss.begin(i); itr != mss.end(i); ++itr)
            cout << " " << itr->first << ":" << itr->second << endl;
    }
}
void test_erase()
{
    unordered_multimap<A, int, hash_A> hm;

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(5, 5);
    hm.emplace(6, 6);
    hm.emplace(7, 7);
    hm.emplace(8, 8);
    hm.emplace(6, 7);

    cout << "element num:" << hm.size();                  // 10
    cout << "bucket count:" << hm.bucket_count() << endl; // 13

    // erasing by iterator
    auto itr = hm.erase(hm.begin());    
    cout << itr->first.geta() << " " << itr->second << endl;
    cout << "element num:" << hm.size();                  // 9
    cout << "bucket count:" << hm.bucket_count() << endl; // 13

    // erasing by key
    int eraseNum = hm.erase(6); 
    cout << "eraseNum:" << eraseNum;    // 2
    cout << "element num:" << hm.size();                  // 7
    cout << "bucket count:" << hm.bucket_count() << endl; // 13

    // erasing by range
    auto it = hm.erase(hm.find(3), hm.end());
    if(it == hm.end()) {cout << "it is end" << endl; }
    else { cout << it->first.geta() << " " << it->second << endl; }
    cout << "element num:" << hm.size();                  // 3
    cout << "bucket count:" << hm.bucket_count() << endl; // 13

    for(auto &x:hm)
    {
        cout << x.first.geta() << " " << x.second << endl;
    }

}

void test_insert()
{
    unordered_multimap<A, int, hash_A> hm;

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(4, 4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);

    cout << "element num:" << hm.size();                    // 6
    cout << "bucket count:" << hm.bucket_count() << endl;   // 13
    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; // 1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; // 1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; // 1
    cout << "bucket[3] size:" << hm.bucket_size(3) << endl; // 1
    cout << "bucket[4] size:" << hm.bucket_size(4) << endl; // 2
    cout << "bucket[5] size:" << hm.bucket_size(5) << endl; // 0
}

void test_equal_range()
{
    unordered_multimap<A, int, hash_A> hm;

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(5, 5);
    hm.emplace(6, 6);
    hm.emplace(7, 7);
    hm.emplace(8, 8);
    hm.emplace(6, 7);

    cout << "element num:" << hm.size();                  // 10
    cout << "bucket count:" << hm.bucket_count() << endl; // 13

    auto r = hm.equal_range(6);
    // auto r = hm.equal_range(8);
    // auto r = hm.equal_range(9);
    if (r.first != hm.end())
    {
        cout << r.first->first.geta() << "," << r.first->second << endl;
    }
    if (r.second != hm.end())       // 左闭右开区间，无序容器末尾不一定指向哪
    {
        cout << r.second->first.geta() << "," << r.second->second << endl;
    }

    for (auto itr = r.first; itr != r.second; ++itr)
    {
        std::cout << itr->first.geta() << " " << itr->second << endl; 
    }

    for_each(r.first, r.second,
             [](unordered_multimap<A, int, hash_A>::value_type &x)
             { std::cout << x.first.geta() << " " << x.second << endl; });
}

void test_equal_range_with_string()
{
    typedef std::unordered_multimap<std::string, std::string> stringmap;
    stringmap myumm = {
        {"orange", "FL"},
        {"strawberry", "LA"},
        {"strawberry", "OK"},
        {"pumpkin", "NH"}};

    // std::cout << "Entries with strawberry:";
    auto range = myumm.equal_range("strawberry");

    if (range.first != myumm.end())
    {
        cout << range.first->first << "," << range.first->second << endl;
    }
    if (range.second != myumm.end())
    {
        cout << range.second->first << "," << range.second->second << endl;
    }
    for_each(
        range.first,
        range.second,
        [](stringmap::value_type &x)
        { std::cout << x.first << " " << x.second; });
}

int main()
{
    // test_unordered_multimap();
    // test_insert();
    // test_equal_range();
    // test_equal_range_with_string();
    test_erase();

    return 0;
}
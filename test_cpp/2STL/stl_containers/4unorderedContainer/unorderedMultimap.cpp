#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "../../../../basicClass/A.h"

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

void test_insert()
{
    unordered_multimap<A, int, hash_A> hm;

    hm.emplace(0,0);
    hm.emplace(1,1);
    hm.emplace(2,2);
    hm.emplace(3,3);
    hm.emplace(4,4);
    hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);
    // hm.emplace(4,4);

    cout << "element num:" << hm.size();    // 6
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; //1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; //1
    cout << "bucket[3] size:" << hm.bucket_size(3) << endl; //1
    cout << "bucket[4] size:" << hm.bucket_size(4) << endl; //2
    cout << "bucket[5] size:" << hm.bucket_size(5) << endl; //0
}

int main()
{
    // test_unordered_multimap();
    test_insert();

    return 0;
}
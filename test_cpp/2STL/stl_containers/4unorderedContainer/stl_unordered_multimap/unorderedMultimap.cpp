#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>

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

int main()
{
    test_unordered_multimap();

    return 0;
}
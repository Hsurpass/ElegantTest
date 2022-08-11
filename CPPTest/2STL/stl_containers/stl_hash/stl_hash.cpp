#include <iostream>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <hash_fun.h>
#include <hashtable.h>
#include <string.h>
#include <string>

// #include <tr1/hashtable.h>
#include <hash_map>
#include <hash_set>

using namespace std;

struct eqstr
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) == 0;
    }
};

static void printBase_hashtable(__gnu_cxx::hashtable<const char*, 
              const char*, 
              hash<const char*>, 
              _Identity<const char*>, 
              eqstr>& ht)
{
    cout << "empty:" << ht.empty() << endl;
    cout << "size:" << ht.size() << endl;
    cout << "max size:" << ht.max_size() << endl;
    cout << "bucket count:" << ht.bucket_count() << endl;
    cout << "max bucket count:" << ht.max_bucket_count() << endl;
    // cout << "load factor:" << ht.load_factor() << endl;
    // cout << "max load factor:" << ht.max_load_factor() << endl;
}

void test_hashset_with_constchar()
{
    __gnu_cxx::hashtable<const char*, 
              const char*, 
              hash<const char*>, 
              _Identity<const char*>, 
              eqstr> ht(50, hash<const char*>(), eqstr());

    ht.insert_unique("kiwi");
    ht.insert_unique("plum");
    ht.insert_unique("apple");

    printBase_hashtable(ht);    
}

void test_hashset_with_string()
{
    __gnu_cxx::hashtable<string, string, hash<string>, 
    _Identity<string>, equal_to<string>> sht(50, hash<string>(), equal_to<string>());
    
    cout << "empty:" << sht.empty() << endl; // 0
    cout << "size:" << sht.size() << endl;   // 53
    cout << "max size:" << sht.max_size() << endl;   // 
    cout << "bucket count:" << sht.bucket_count() << endl;
    cout << "max bucket count:" << sht.max_bucket_count() << endl;
}

void test_hashtable_with_KV()
{
    __gnu_cxx::hashtable<pair<string, int>, string, hash<string>, 
    _Select1st<pair<string, int> >, equal_to<string> > 
    siht(100, hash<string>(), equal_to<string>());

    siht.insert_unique(make_pair(string("jjhou"), 95) );
    siht.insert_unique(make_pair(string("sabrina"), 90) );
    siht.insert_unique(make_pair(string("mjchen"), 85) );

    cout << siht.size() << endl;    // 3
    // cout << siht.bucket_size(1) << endl;    // c++ 11
    cout << siht.bucket_count() << endl;    // 193
    
    for (auto itr = siht.begin(); itr != siht.end(); ++itr)
    {
        cout << itr->first << ":" << itr->second << endl;
    }
    cout << endl;

    for (int i = 0; i < siht.bucket_count(); i++)
    {
        // for (auto itr = siht.begin(i); itr != siht.end(); i++)   // 2.9没有
        // {
        //     /* code */
        // }
    }
    

    cout << siht.find(string("jjhou"))->second << endl;
    cout << siht.find(string("sabrina"))->second << endl;
    cout << siht.find(string("mjchen"))->second << endl;

}

void test_hashtable_with_multiKV()
{
    __gnu_cxx::hashtable<pair<string, int>, string, hash<string>, 
    _Select1st<pair<string, int> >, equal_to<string> > 
    siht(100, hash<string>(), equal_to<string>());

    siht.insert_equal(make_pair(string("jjhou"), 95) );
    siht.insert_equal(make_pair(string("sabrina"), 90) );
    siht.insert_equal(make_pair(string("sabrina"), 100) );
    siht.insert_equal(make_pair(string("mjchen"), 85) );

    cout << siht.size() << endl;    // 4
    cout << siht.count("jjhou") << endl;    // 1
    cout << siht.count("sabrina") << endl;    // 2
    cout << siht.count("mjchen") << endl;    // 1
    // cout << siht.bucket_size(1) << endl;    // c++ 11
    cout << siht.bucket_count() << endl;    // 193
    
    for (auto itr = siht.begin(); itr != siht.end(); ++itr)
    {
        cout << itr->first << ":" << itr->second << endl;
    }
    cout << endl;

    for (int i = 0; i < siht.bucket_count(); i++)
    {
        // for (auto itr = siht.begin(i); itr != siht.end(); i++)   // 2.9没有
        // {
        //     /* code */
        // }
    }
    
    // siht.bucket("jjhou");   // c++11
    cout << siht.find(string("jjhou"))->second << endl;
    cout << siht.find(string("sabrina"))->second << endl;
    cout << siht.find(string("sabrina"))->second << endl;
    cout << siht.find(string("mjchen"))->second << endl;

}

int main()
{
    // test_hashset_with_constchar();
    // test_hashset_with_string();
    // test_hashtable_with_KV();
    test_hashtable_with_multiKV();

    return 0;
}

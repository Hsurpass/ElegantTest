#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string.h>
#include <string>
#include <utility>
#include "../../../basicClass/A.h"

using namespace std;

template<typename T>
struct MyEqual
{};

template<>
struct MyEqual<const char*>
{
    bool operator()(const char* one, const char* other) const
    {
        cout << "bool operator()(const char* one, const char* other)" << endl;
        return strcmp(one, other) == 0;
    }
};

void test_unordered_map_const_char()
{
    unordered_map<const char*, int, hash<const char*>, MyEqual<const char*> > hm;
    hm["monday"] = 100;
    hm["tuesday"] = 200;
    hm["wednesday"] = 300;
    hm["thursday"] = 500;
    hm["friday"] = 600;
    hm["saturday"] = 1000;
    hm["sunday"] = 500;
    hm["friday"] = 700;

    cout << "size:" << hm.size() << endl;   // 7
    cout << "max_size:" << hm.max_size() << endl;   // 7

    cout << "-----------operator[]:----------------" << endl;
    cout << "hm[\"friday\"]:" << hm["friday"] << endl;
    cout << "hm[\"abc\"]:" << hm["abc"] << endl;
    cout << "size:" << hm.size() << endl;   // 8

    cout << "-----------bucket_count:------max_bucket_count----------" << endl;
    cout << "bucket_count:" << hm.bucket_count() << endl;  // 13 桶的容量(数组的容量)
    cout << "max_bucket_count:" << hm.max_bucket_count() << endl;  // 13 桶的容量(数组的容量)

    cout << "-----------load_factor:----------------" << endl;
    cout << "load_factor:" << hm.load_factor() << endl;

    cout << "-----------max_load_factor:----------------" << endl;
    cout << "max_load_factor:" << hm.max_load_factor() << endl;

    cout << "------------iterator:---------------" << endl;
    for (auto& item : hm) {
        cout << item.first << ":" << item.second << endl;
    }
    cout << "-----------bucket_size:-----begin(i):-----end(i):------" << endl;
    for (int i = 0; i < hm.bucket_count(); i++) {
        int bucket_size = hm.bucket_size(i);
        cout << "bucket " << i << ": " << bucket_size << endl;
        for (auto local_itr = hm.begin(i); local_itr != hm.end(i); ++local_itr) {
            cout << "   " << local_itr->first << ":" << local_itr->second << endl;
        }
    }

    cout << "---------------------swap------------------" << endl;
    unordered_map<const char*, int, hash<const char*>, MyEqual<const char*> > hm1;
    hm1.swap(hm);
    cout << "size:" << hm.size() << endl;   // 0
    cout << "size:" << hm1.size() << endl;  // 8

    cout << "--------------------count----------------------" << endl;
    cout << "count:" << hm1.count("abc") << endl;   // 1

    cout << "-------------clear:----------------" << endl;
    hm.clear();
    cout << "size:" << hm.size() << endl;   // 0    彻底清空
    hm1.clear();
    cout << "size:" << hm1.size() << endl;   // 0    彻底清空
}

void test_insert_A_int()
{
    unordered_map<A, int, hash_A> hm;
    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    cout << "element num:" << hm.size();    // 5
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; //1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; //1
    cout << "bucket[3] size:" << hm.bucket_size(3) << endl; //1
    cout << "bucket[4] size:" << hm.bucket_size(4) << endl; //1
    cout << "bucket[5] size:" << hm.bucket_size(5) << endl; //1
}

void test_insert_int_A()
{
    unordered_map<int, A> hm;
    hm.emplace(0, 0);
    hm.emplace_hint(hm.begin(), 1, 1);  // 无论hint传入的是什么，值都会插入到合适的位置。
    cout << "element num:" << hm.size();    // 2
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; //1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; //0

    hm.insert({2, 2});
    hm.insert(make_pair<int, A>(3, 3));
    hm.insert(hm.begin(), make_pair(4, 4));  // 无论hint传入的是什么，值都会插入到合适的位置。
    cout << "element num:" << hm.size();    // 5
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; //1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(3) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(4) << endl; //0
}

void test_reserve()
{
    unordered_map<A, int, hash_A> hm;
    // hm.reserve(6);

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    cout << "element num:" << hm.size();    // 3
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    // hm.reserve(6);
    // hm.reserve(50);

    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(4, 4);

    cout << "element num:" << hm.size();    // 5
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; //1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; //1
    cout << "bucket[3] size:" << hm.bucket_size(3) << endl; //1
    cout << "bucket[4] size:" << hm.bucket_size(4) << endl; //1
    cout << "bucket[5] size:" << hm.bucket_size(5) << endl; //1
}

void test_erase()
{}

// operator[]
void test_operator_square_bracket()
{
    unordered_map<A, int, hash_A> hm;
    hm[0];  // 构造+移动
    cout << "hm[0]:" << hm[0] << endl;
    hm[0] = 1;  // operator==()
    cout << "hm[0]:" << hm[0] << endl;
}

void test_modify_max_load_factor()
{
    unordered_map<A, int, hash_A> hm;

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(5, 5);

    cout << "element num:" << hm.size();    // 6
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "load_factor:" << hm.load_factor() << endl;
    cout << "max_load_factor:" << hm.max_load_factor() << endl;

    hm.max_load_factor(hm.max_load_factor() / 2);
    hm.emplace(6, 6);
    hm.emplace(7, 7);
    hm.emplace(8, 8);

    cout << "element num:" << hm.size();    // 6
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "load_factor:" << hm.load_factor() << endl;
    cout << "max_load_factor:" << hm.max_load_factor() << endl;

    cout << "bucket[0] size:" << hm.bucket_size(0) << endl; //1
    cout << "bucket[1] size:" << hm.bucket_size(1) << endl; //1
    cout << "bucket[2] size:" << hm.bucket_size(2) << endl; //1
    cout << "bucket[3] size:" << hm.bucket_size(3) << endl; //1
    cout << "bucket[4] size:" << hm.bucket_size(4) << endl; //1
    cout << "bucket[5] size:" << hm.bucket_size(5) << endl; //0
}

void test_hashtable_linklist_to_rbtree()
{}

void test_rehash()
{
    unordered_map<A, int, hash_A> hm;
    //通过调用rehash来在哈希表中保留一定数量的桶，我们避免了容器扩展可能导致的多次rehash。
    hm.rehash(20);

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(5, 5);
    hm.emplace(6, 6);
    hm.emplace(7, 7);
    hm.emplace(8, 8);

    cout << "element num:" << hm.size(); // 6
    cout << "bucket count:" << hm.bucket_count() << endl; // 13
    cout << "load_factor:" << hm.load_factor() << endl;
    cout << "max_load_factor:" << hm.max_load_factor() << endl;
}

void test_equal_range()
{
    unordered_map<A, int, hash_A> hm;

    hm.emplace(0, 0);
    hm.emplace(1, 1);
    hm.emplace(2, 2);
    hm.emplace(3, 3);
    hm.emplace(4, 4);
    hm.emplace(5, 5);
    hm.emplace(6, 6);
    hm.emplace(7, 7);
    hm.emplace(8, 8);

    auto r = hm.equal_range(6);
    // auto r = hm.equal_range(9);
    if (r.first != hm.end()) {
        cout << r.first->first.geta() << "," << r.first->second << endl;
    }
    if (r.second != hm.end()) {
        cout << r.second->first.geta() << "," << r.second->second << endl;
    }
}

// 自定义哈希函数
struct pair_hash
{
    std::size_t operator()(const std::pair<std::string, std::string>& p) const
    {
        auto hash1 = std::hash<std::string>{}(p.first);
        auto hash2 = std::hash<std::string>{}(p.second);
        return hash1 ^ (hash2 << 1); // 组合两个字符串的哈希值
    }
};

struct pair_hash1
{
    std::size_t operator()(const std::pair<std::string, std::string>& p) const
    {
        auto hash1 = std::hash<std::string>{}(p.first);
        auto hash2 = std::hash<std::string>{}(p.second);
        // 更复杂的组合方式，减少碰撞概率
        return hash1 ^ (hash2 * 31); // 31 是一个常见的用于混合哈希的质数
    }
};

void test_pair_as_key()
{
    // std::unordered_map<std::pair<std::string, std::string>, int, pair_hash> map;
    std::unordered_map<std::pair<std::string, std::string>, int, pair_hash1> map;
    std::unordered_map<std::string, int> firstMap;
    std::unordered_map<std::string, int> secondMap;
    std::unordered_map<std::string, int> kmap;

    // 插入一些值
    map[{"first", "second"}] = 1;
    map[{"third", "fourth"}] = 2;
    map[{"fifth", "sixth"}] = 3;

    std::cout << map[{"third", "fourth"}] << std::endl;
    std::cout << map.at({"fourth", "third"}) << std::endl;

    for (const auto& pair : map) {
        std::cout << "(" << pair.first.first << ", " << pair.first.second << ") = " << pair.second << std::endl;
    }

    auto pair1 = std::make_pair(1, 2);
    auto pair2 = std::make_pair(1, 2);
    if (pair1 == pair2) {
        std::cout << "pair1 == pair2" << std::endl;
    }
    else {
        std::cout << "pair1 != pair2" << std::endl;
    }

    // 分别存储 first 和 second 的映射
    for (const auto& entry : map) {
        firstMap[entry.first.first] = entry.second;
        secondMap[entry.first.second] = entry.second;
        kmap[entry.first.first] = entry.second;
        kmap[entry.first.second] = entry.second;
    }

    std::cout << firstMap["third"] << std::endl;
    if (firstMap.find("second") == firstMap.end()) {
        cout << "firstMap not find key" << endl;
    }
    // std::cout << firstMap.at("second") << std::endl;
    for (const auto& kv : firstMap) {
        std::cout << "(" << kv.first << "," << kv.second << ")" << std::endl;
    }

    for (const auto& kv : secondMap) {
        std::cout << "(" << kv.first << "," << kv.second << ")" << std::endl;
    }
    cout << "-----------------------------------" << endl;
    for (const auto& kv : kmap) {
        std::cout << "(" << kv.first << "," << kv.second << ")" << std::endl;
    }
}

int main()
{
    // test_unordered_map_const_char();
    // test_insert_int_A();
    // test_insert_A_int();
    // test_reserve();
    // test_operator_square_bracket();
    // test_modify_max_load_factor();
    // test_rehash();
    // test_equal_range();
    test_pair_as_key();

    return 0;
}
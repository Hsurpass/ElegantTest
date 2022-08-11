#include <iostream>
#include <bits/stl_tree.h>
#include <algorithm>
#include <functional>

using namespace std;

void test_sizeof_rbTree()
{
    _Rb_tree<int, int, std::_Identity<int>, std::less<int>> rbTree;
    cout << sizeof(rbTree) << endl; // 48

    cout << sizeof(_Rb_tree<int, int, std::_Identity<int>, std::less<int>>) << endl;    // 48
    cout << sizeof(_Rb_tree<char, char, std::_Identity<char>, std::less<char>>) << endl;// 48
}

void test_rbTree_insert_unique_and_insert_equal()
{
    _Rb_tree<int, int, std::_Identity<int>, std::less<int>> rbTree;
    cout << rbTree.empty() << endl; // 1
    cout << rbTree.size() << endl;  // 0
    
    rbTree._M_insert_unique(3);
    rbTree._M_insert_unique(8);
    rbTree._M_insert_unique(5);
    rbTree._M_insert_unique(9);
    rbTree._M_insert_unique(13);
    rbTree._M_insert_unique(5);
    cout << rbTree.empty() << endl; // 0
    cout << rbTree.size() << endl;  // 5
    cout << rbTree.count(5) << endl;// 1

    rbTree._M_insert_equal(5);
    rbTree._M_insert_equal(5);
    cout << rbTree.size() << endl;  // 7
    cout << rbTree.count(5) << endl;// 3

}

int main()
{
    // test_sizeof_rbTree();
    test_rbTree_insert_unique_and_insert_equal();

}
#include <iostream>
#include <list>
#include <string>
#include <memory>   // 内含std::allocator
//欲使用std::allocator 以外的allocator，得自行#include<ext/...>
#include <ext/array_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/debug_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/bitmap_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/new_allocator.h>

using namespace std;

template<typename T>
void printList(std::list<T>& tmpList)
{
    for (auto &value : tmpList)
    {
        cout << value << " ";
    }
    cout << endl;
}


// houjie STL 7.分配器之测试
void test_list_with_special_allocator()
{
    list<string, allocator<string>> c1;
    list<string, __gnu_cxx::malloc_allocator<string>> c2;
    list<string, __gnu_cxx::new_allocator<string>> c3;
    list<string, __gnu_cxx::__pool_alloc<string>> c4;
    list<string, __gnu_cxx::__mt_alloc<string>> c5;
    list<string, __gnu_cxx::bitmap_allocator<string>> c6;
    // list<string, __gnu_cxx::array_allocator<string>> c7;
    // list<string, __gnu_cxx::debug_allocator<string>> c8;

    c1.push_back("abc");
    printList(c1);
    c2.push_back("abc");
    cout << *c2.begin() << endl;
    c3.push_back("abc");
    cout << *c3.begin() << endl;
    c4.push_back("abc");
    cout << *c4.begin() << endl;
    c5.push_back("abc");
    cout << *c5.begin() << endl;
    c6.push_back("abc");
    cout << *c6.begin() << endl;
    // c7.push_back("abc");
    // cout << *c7.begin() << endl;
    // c8.push_back("abc");
    // cout << *c8.begin() << endl;
    
}

// test all allocators's allocate() & deallocate()
void test_allocate_and_deallocate()
{
    int *p = NULL;
    std::allocator<int> alloc1;
    p = alloc1.allocate(1);
    *p = 123;
    cout << *p << endl;
    alloc1.deallocate(p, 1);

    __gnu_cxx::malloc_allocator<int> alloc2;
    p = alloc2.allocate(1);
    alloc2.deallocate(p, 1);

    __gnu_cxx::new_allocator<int> alloc3;
    p = alloc3.allocate(1);
    alloc3.deallocate(p, 1);

    __gnu_cxx::__pool_alloc<int> alloc4;
    p = alloc4.allocate(2);
    *p = 123;
    cout << *p << endl;
    alloc4.deallocate(p, 2);

    __gnu_cxx::__mt_alloc<int> alloc5;
    p = alloc5.allocate(1);
    alloc5.deallocate(p, 1);

    __gnu_cxx::bitmap_allocator<int> alloc6;
    p = alloc6.allocate(3);
    *p = 123;
    cout << *p << endl;
    alloc6.deallocate(p, 3);
}

int main()
{
    test_list_with_special_allocator();
    test_allocate_and_deallocate();

    return 0;
}
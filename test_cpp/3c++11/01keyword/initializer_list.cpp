#include <initializer_list>
#include <list>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

void test_initializer_list01()
{
    vector<int> vi = {1,2,3,4,5};
    list<int> li = {1,2,3,4,5};
    
    map<int,string> mis =
    {
        {1,"c"}, {2,"c++"},
        {3,"java"},{4,"scala"},{5,"python"}
    };
    mis.insert({6,"ruby"});
    
    for(auto &is: mis)
    {
        cout << is.first << ":" << is.second << endl;
    } 
    
}

template <typename T>
class myarr
{ 
private:
    vector<T> _arr;
public:
    myarr() 
    {
        cout << "called myarr()" << endl;
    } 

    myarr(const initializer_list<T>& il)
    {
        cout << "called myarr(const initializer_list<T>& il)" << endl;
        for (auto x : il)
            _arr.push_back(x);
    }
};

void test_initializer_list02()
{
    myarr<int> ma;
    myarr<int> ma2 = {1, 2, 3, 4, 5};
}

class A 
{
public:
    A(int a, int b)
    {
        cout << "A(int a, int b), a=" << a << ", b=" << b << endl;
    }

#if 1
    A(initializer_list<int> initList)
    {
        cout << "A(initializer_list<int> initList)" << endl;
        for (auto &i:initList)
        {
            cout << i << " ";
        }
        cout << endl;
    }
#endif

};

// from houjie initializer_list<>
void test_initializer_list03()
{
    A a1(1, 2);
    A a2{3, 4}; // 如果没有initializer_list的构造函数，则会匹配到A(int, int)
    A a3{5, 6, 7};  // 如果没有initializer_list的构造函数，则编译报错
    A a4 = {7, 8};

}

int main(int argc, char *argv[])
{
    // test_initializer_list01();
    // test_initializer_list02();
    test_initializer_list03();

    return 0;
}

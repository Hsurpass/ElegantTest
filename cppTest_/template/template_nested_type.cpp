#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;


// effective c++ 条款42
template<typename T>
void print(T& v)
{
    // for (T::iterator itr = v.begin(); itr != v.end(); ++itr)
    for (typename T::iterator itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

void test_nested_typename()
{
    vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);

    print(vi);
}

int main()
{
    test_nested_typename();
    
    return 0;
}
#include <iostream>
#include <stdio.h>
//#define NDEBUG
#include <assert.h>
using namespace std;

template<typename T,typename U>
int mybit_copy(T &a,U &b)
{
    static_assert(sizeof(a) == sizeof(b),"parameters must have same width");

}

int main()
{
    int a;float b;
    mybit_copy(a,b);
    double c;
    mybit_copy(a,c);

}

int main01()
{
    assert((/*sizeof(int) == 8)*/false) && "only workfor int for 32 bit");
/*    static_assert(sizeof(long) != sizeof(long long),
                "only work for long == long long");*/
    cout << "--------------" << endl;
    return 0;
}

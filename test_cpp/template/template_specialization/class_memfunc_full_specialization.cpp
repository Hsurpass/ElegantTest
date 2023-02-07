#include <iostream>
#include <cstring>
#include <cstdlib>
#include <typeinfo>

using namespace std;

template <typename T>
class Compare
{
public:
    Compare(T x, T y)
    {
        cout << "Compare(T x, T y)" << endl;
        _x = x;
        _y = y;
    }
    Compare(const Compare<T> &another)
    {
        _x = another._x;
        _y = another._y;
    }
    
    T max()
    {
        return _x > _y ? _x : _y;
    }

private:
    T _x;
    T _y;
};

template<>
const char* Compare<const char *>::max()
{
    if (strcmp(_x, _y) > 0)
        return _x;
    else
        return _y;
}

void test_memfunc_full_specialization()
{
    Compare<string> cs("china", "nzhsoft");
    cout << cs.max() << endl;

    Compare<const char *> cs2("nzhsoft", "china");
    cout << cs2.max() << endl;
}

int main()
{   
    test_memfunc_full_specialization();

    return 0;
}
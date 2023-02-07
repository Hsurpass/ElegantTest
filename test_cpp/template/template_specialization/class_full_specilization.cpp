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

#if 1
// class Compare    // error
template <>
class Compare<const char *>
{
public:
    Compare(const char *x, const char *y)
    {
        cout << "Compare(const char *x, const char *y)" << endl;
        _x = x;
        _y = y;
    }
    Compare(const Compare<const char *> &another)
    {
        _x = another._x;
        _y = another._y;
    }

    const char *max();

private:
    const char *_x;
    const char *_y;
};

// const char* Compare::max()   // error
const char* Compare<const char *>::max()
{
    if (strcmp(_x, _y) > 0)
        return _x;
    else
        return _y;
}
#endif

void test_class_full_specialization()
{
    Compare<string> cs("china", "nzhsoft");
    cout << cs.max() << endl;

    Compare<const char *> cs2("nzhsoft", "china");
    cout << cs2.max() << endl;
}

int main()
{   
    test_class_full_specialization();

    return 0;
}
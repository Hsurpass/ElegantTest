#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
    // int operator[](int index)
    // {
    //     // return (*this)[index];
    //     return static_cast<const A>(*this)[index];  // const函数只能const对象来调用
    // }

    // int operator[](int index)
    // {
    //     return static_cast<const A>(*this)[index];  // const函数只能const对象来调用
    // }

    // int operator[](int index) const
    // {
    //     return m_vi[index];
    // }

    // effective c++ 条款3
    // int operator[](int index)
    int& operator[](int index)
    {
        // return static_cast<const A&>(*this)[index];  // const函数只能const对象来调用
        return const_cast<int&>(static_cast<const A&>(*this)[index]);  // const函数只能const对象来调用
    }

    const int& operator[](int index) const
    {
        return m_vi[index];
    }

    void set(int i)
    {
        m_vi.push_back(i);
    }

private:
    std::vector<int> m_vi;
};

void test_non_const_call_const()
{
    A a;
    for (size_t i = 0; i < 10; i++)
    {
        a.set(i);
    }

    cout << a[3] << endl;
}

void test_const()
{
    const double pi = 3.14;
    const double *ptr = &pi;
    cout << *ptr << endl;

    double tmp = 12;
    ptr = &tmp;
    cout << *ptr << endl;
}

int main()
{
    // test_const();
    test_non_const_call_const();

    return 0;
}
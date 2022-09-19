#include <iostream>

using namespace std;

int& get(int* array, int index)
{
    return array[index];
}
void test01()
{
    // c++ primer 练习6.32
    int ia[10];
    for (size_t i = 0; i != 10; i++)
    {
        get(ia, i) = i;
    }

    for (size_t i = 0; i < 10; i++)
    {
        cout << ia[i] << " ";
    }
    cout << endl;
}

int main()
{
    test01();

    return 0;
}
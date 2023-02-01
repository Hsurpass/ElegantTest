#include <iostream>

using namespace std;

class A{
public:
    A(int a, int b, int c):ra(a), cb(b)
    {
    }

private:
    int &ra;
    const int cb;
    static const int sci = 10;
};

int main()
{

    return 0;
}
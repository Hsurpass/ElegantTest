#include <iostream>

using namespace std;

int main()
{
    std::size_t a = 10;
    int b = -1;
    cout << (unsigned int)b << endl;
    if(a < b)
    {
        cout << "a < b" << endl;
    }
    else {
        cout << "a > b" << endl;
    }
    return 0;
}

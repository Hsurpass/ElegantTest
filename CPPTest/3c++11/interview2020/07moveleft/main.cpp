#include <iostream>

using namespace std;

int main()
{
    unsigned int a = 0xFF;
    unsigned int b = a << 33;
//    cout << b << endl;
    printf("b:%x\n",b);
    return 0;
}

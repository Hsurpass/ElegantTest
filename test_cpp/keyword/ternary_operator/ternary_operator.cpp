#include <iostream>

using namespace std;

int main()
{
    int a = 10;
    int b = 20;
    
    a < b ? a : b = 100;
    std::cout << "ret=" << a << std::endl;  // 10

    (a < b ? a : b) = 100;
    cout << "ret=" << a << endl;    // 100  C++返回的是变量本身，可以作为左值使用。
}
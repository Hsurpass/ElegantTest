#include <iostream>
#include <thread>

using namespace std;

int main()
{
    cout << "hardware_concurrency:" << thread::hardware_concurrency() << endl;
}
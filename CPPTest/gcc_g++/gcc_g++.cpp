// g++ -D DEBUG -D TEST gcc_g++.cpp

#include <iostream>

using namespace std;

int main()
{
    #ifdef DEBUG
        cout << "DEBUG LOG" << endl;
    #endif

    #ifdef TEST
        cout << "TEST" << endl;
    #endif

    cout << "gcc_g++" << endl;

    return 0;
}
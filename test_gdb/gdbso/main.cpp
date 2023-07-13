#pragma once

// #include <iostream>
#include "hello.h"
// using namespace std;

// g++ -g -fPIC -shared hello.cpp -I. -o libhello.so
// g++ -g main.cpp -I. -L. -lhello -o main

int main()
{
    hello();

    return 0;
}

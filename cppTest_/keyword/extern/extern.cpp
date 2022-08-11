#include <iostream>
#include "a.h"
using namespace std;

extern int a;
extern double b;

int main()
{
	a = 100;
	double b = 6.567;

	cout << "a:" << a <<endl;
	cout << "b:" << b <<endl;

	return 0;
}

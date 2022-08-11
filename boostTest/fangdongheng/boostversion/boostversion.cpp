#include <boost/version.hpp>
#include <iostream>
#include <boost/timer.hpp>
using namespace std;

int main()
{
	cout << "boost version: " << BOOST_VERSION << endl;
	cout << "boost libs version: " BOOST_LIB_VERSION << endl;
	boost::timer t;
	cout << t.elapsed_max() / 3600 << "h"<< endl;
	cout << t.elapsed_min() << "s" << endl;
	return 0;
}
#define BOOST_THREAD_VERSION 4
#include <boost/thread.hpp>
//#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
//#include <thread>
using namespace std;
using namespace boost;

void func()
{

}
int main()
{
    //this_thread::sleep_for(boost::chrono::seconds(3));
    //boost::thread t(&func);
    //t.join();
    //unsigned int n = std::thread::hardware_concurrency();

    unsigned int n = boost::thread::hardware_concurrency();
    cout << n << endl;
    cout << boost::thread::physical_concurrency() << endl;
    cout << "over " << endl;
    return 0;
}
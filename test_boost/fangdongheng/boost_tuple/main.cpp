//#pragma pack(8)
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <vector>
using namespace std;
using namespace boost;
int main03()
{
    int a = 10, b = 20;
    //tie(a, b) = tie(b, a);
    tie(a, b) = make_tuple(b, a);

    cout << a << b << endl;
    return 0;
}
struct demo
{
    int a;
    double b;
    vector<string> v;
};
int main()
{
    //vector<int> v;
    vector<string> v;
    cout << sizeof(int) << endl;
    cout << sizeof(double) << endl;

    cout << sizeof(v) << endl;
    cout << sizeof(demo) << endl;
    typedef boost::tuple<int, double, vector<string>> mytuple;
    cout << sizeof(mytuple) << endl;
    return 0;
}
int main01()
{
    //boost::tuple<int, char> mytuple(10,'s');
    boost::tuple<int, char> mytuple = make_tuple(10, 's');

    boost::get<0>(mytuple) = 200;
    cout << boost::get<0>(mytuple) << " "<< boost::get<1>(mytuple) << endl;
    return 0;
}
#include <iostream>
#include <functional>
#include <typeinfo>
#include <math.h>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

//class big_class
//{
//public:
//    big_class():x(0) {}
//    void print()
//    {
//        cout << "big_class:" << ++x <<endl;
//    }
//private:
//    int x;
//};
//template<typename T>
//void print(T &x)
//{
//    for(int i = 0;i < 2;++i)
//    {

//    }
//}
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
    typedef std::tuple<int, double, vector<string>> mytuple;
    cout << sizeof(mytuple) << endl;
    return 0;
}
int main06()
{
//    map<int,int> m;
//    map<int,string> m;
//    cout << sizeof(m) << endl;

}

int main05()
{
//    vector<int> v(10,2);
//    auto rw = std::ref(v);
    int a = 10;
//    decltype(a) v = a;
    decltype((a)) v = a;
    cout << "a: " << a << endl;
    cout << "v: " << v << endl;
    v = 100;
    cout << "a: " << a << endl;
    cout << "v: " << v << endl;

}

int main04()
{
    double x = 4.0;
    cout << sqrt(ref(x)) << endl;
}

int main03()
{
    double x = 2.71828;
    auto crw = cref(x);
    auto rw = ref(x);
    cout << typeid(crw).name() << endl;
    cout << typeid(rw).name() << endl;

    string str;
    auto rws = ref(str);
    cout << typeid(rws).name() << endl;
}

int main02()
{
    int x = 10;
    reference_wrapper<int> rw(x);
    cout << rw << endl;
    (int &)rw = 100;
    cout << rw<< endl;
    cout << x << endl;
    cout << "-----------------------" << endl;
    reference_wrapper<int> rw2(rw);
    cout << rw2.get() << endl;
    cout <<"----------------------" << endl;
    string str;
    reference_wrapper<string> rws(str);
    rws.get() = "hello";
    cout << "str:" << str << endl;
    cout << rws.get() << endl;
    cout << rws.get().size() << endl;
    cout << str.size() << endl;

}

int main01()
{
    int a(10),b(20),c(30);
    std::reference_wrapper<int> refs[] = {a,b,c};
    for(int &x : refs)
    {
        cout << x <<endl;
    }
    return 0;
}

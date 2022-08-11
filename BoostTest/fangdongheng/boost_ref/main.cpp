#include <boost/ref.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class big_class
{
public:
    big_class() :x(0) {}
    void print()
    {
        cout << "big_class:" << ++x << endl;
    }
private:
    int x;
};
template<typename T>
void print(T x)
{
    for (int i = 0; i < 2; ++i)
    {
        unwrap_ref(x).print();
    }
}
int main()
{
    big_class c;
    auto rw = boost::ref(c);
    c.print();  //1
    print(c);  //value_copy 2 3
    print(rw);  //传递的是reference_wrapper对象，相当于传引用; 2 3
    print(c);   //4 5
    c.print();

    return 0;
}

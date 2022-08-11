#include <iostream>
#include <functional>
#include <memory>
using namespace std;
using namespace std::placeholders;

class A
{
public:
    static print(const int& a,const int& b) {
        cout << a << "," << b << endl;
    }

};
int main()
{
    int *pa = new int(1);
    int *pb = new int(2);
//    int a = 1;
//    int b = 2;
//    A aa;

    {
        shared_ptr<int> spa(pa);
        shared_ptr<int> spb(pb);
        cout << *spa << endl;
        cout << *spb << endl;
    }

//    auto f = bind(&A::print,_1,_2);
    function<void(const int&,const int&)> f = bind(&A::print,_1,_2);
//    f(a,b);
//    f(*pa,*pb);

    return 0;
}

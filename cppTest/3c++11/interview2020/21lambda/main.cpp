#include <iostream>
#include <typeinfo>
using namespace std;

auto adder(){
    auto sum= 0;
    return[=](int value)mutable{
        sum += value;
        return sum;
    };
//    cout << "sum: " << sum << endl;
}

int main()
{
//    auto f = adder();
//    cout << f(1) << endl;
    auto f = adder();
    for(int i=0; i<101; i++){
    cout<<f(i)<<endl;
    }
}

int main02()
{
    int x = 10;int y = 20;
    //    auto foo = [&](){
    //        x = 100;
    //        y = 200;
    //        cout << x << " " <<y << endl;
    //    };
    auto foo = [=]()mutable{
        x = 100;
        y = 200;
        cout << x << " " <<y << endl;
    };
    foo();
    cout << x << " "<< y << endl;
    foo();
}

int main01()
{
    auto local = [](){};
    cout << typeid(local).name() << endl;
    return 0;
}

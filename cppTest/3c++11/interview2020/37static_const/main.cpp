#include <iostream>

using namespace std;
class A
{
public:
    A(){}
    const static int dis();
//    {
//        cout<<i<<endl;
//        return i;
//    }
private:
//    const static int i = 100;
    const static int i= 100;
};

//const int A::i  = 100;
const int A::dis()
{
    cout<<i<<endl;
    return i;
}
int main()
{
    A::dis();

    return 0;
}

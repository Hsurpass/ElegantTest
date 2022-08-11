#include <iostream>
#include <map>


using namespace std;
class A
{
public:
    A(){}
    A(int a):m_a(a) {}
private:
    int m_a;
};
int main()
{
    map<int,A> m;
    m[1] = A(10);   //如果m[1]有值，则返回其引用;如果没值，则返回一个A()。如果没有默认构造函数A(){}，编译会报错。
//    m.insert(make_pair(1,A()));

    return 0;
}

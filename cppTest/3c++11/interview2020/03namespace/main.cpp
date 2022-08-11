#include <iostream>

using namespace std;
namespace A {
    struct X{};
    struct B{};
    void f(int){std::cout << "namespace A" << std::endl;}
    void g(X){std::cout << "namespace A" << std::endl;}
}
namespace B {
    void g(A::X x)
    {
        g(x);
    }
}
int main()
{
    A::X x;
    B::g(x);
    return 0;
}

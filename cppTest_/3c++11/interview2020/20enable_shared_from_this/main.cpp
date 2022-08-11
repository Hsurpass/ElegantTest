#include <iostream>
#include <memory>
#include <typeinfo>
using namespace std;

class self_shared:public enable_shared_from_this<self_shared>
{
public:
    self_shared(int n = 0):x(n) {}
    void print()
    {
        cout << "self_shared,x: " << x << endl;
        this->shared_from_this();
    }
    int x;
};

int main02()
{
    self_shared ss;
    auto p = ss.shared_from_this();
    p->x = 99;
    p->print();
}
int main()
{
    auto sp = make_shared<self_shared>(1000);
//    cout << decltype(sp) << endl;
//    decltype(sp) x;
    cout<< typeid(sp).name() << endl;
    cout << sp.use_count() << endl;
    sp->print();
//    const auto &p = sp->shared_from_this();
//    auto &&p = std::move(sp->shared_from_this());
    auto p = sp->shared_from_this();
    cout<< typeid(p).name() << endl;
    cout << p.use_count() << endl;
    cout << sp.use_count() <<endl;

    p->x = 100;
    p->print();
    sp->print();
    return 0;
}

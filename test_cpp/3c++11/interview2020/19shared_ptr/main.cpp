#include <iostream>
#include <memory>
using namespace std;

int main()
{
    int *p = new int(10);
    shared_ptr<int> sp(p);
    shared_ptr<int> sp1(sp);
    shared_ptr<int> sp2(sp);

    shared_ptr<int> sp3 = std::move(sp);
    cout << "sp use_count: " << sp.use_count() << endl;
    cout << "sp3 use_count: " << sp3.use_count() << endl;
    cout << *sp3 <<endl;
//    sp = shared_ptr<int>(new int(100));
    sp = make_shared<int>(200);
    cout << *sp << endl;
    cout << "sp use_count: " << sp.use_count() << endl;
}

int main01()
{
    int *p = new int(10);
    shared_ptr<int> sp(p);
    shared_ptr<int> sp1(sp);
    shared_ptr<int> sp2(sp);

    cout << "sp use_count: " << sp.use_count() << endl;
    sp.reset(new int(20));//sp.reset();
    cout << "sp use_count: " << sp.use_count() << endl;
    cout << "sp1 use_count: " << sp1.use_count() << endl;
    cout<< *sp << endl;
//    if(sp == nullptr)
    if(!sp)
    {
        cout << "sp is null" << endl;
    }
    return 0;
}

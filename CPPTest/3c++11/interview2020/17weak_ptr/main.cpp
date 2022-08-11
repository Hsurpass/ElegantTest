#include <iostream>
#include <memory>

using namespace std;


int main03()
{
    shared_ptr<int> obj(new int(10));

    weak_ptr<int> wobj(obj);
    obj.reset(new int(20));
    cout << *obj << endl;
    cout << obj.use_count() << endl;
    shared_ptr<int> tmp = wobj.lock();
    cout << tmp.use_count() << endl;
    if(wobj.expired())
    {
        cout << "wobj is expired" << endl;
    }

//    cout << *tmp << endl;

}

int main02()
{
    int *p = new int(10);
    shared_ptr<int> sp(p);
    shared_ptr<int> sp1(sp);
    shared_ptr<int> sp2(sp);

    weak_ptr<int> wp(sp);
    cout << "wp use_count: " << wp.use_count() << endl;
//    wp.reset();
//    cout << "wp use_count: " << wp.use_count() << endl;
//    cout << "sp use_count: " << sp.use_count() << endl;
//    cout << *sp << endl;
//    cout << *sp1 << endl;
//    cout << *sp2 << endl;

    if(wp.expired())
    {
        cout << "wp is expired" << endl;
    }
    shared_ptr<int> tmp = wp.lock();
    cout << "wp use_count: " << wp.use_count() << endl;
    cout << "sp use_count: " << sp.use_count() << endl;
    cout << "-------------" << endl;
    wp.reset();
    shared_ptr<int> tmp1 = wp.lock();
    cout << "wp use_count: " << wp.use_count() << endl;
    cout << "sp use_count: " << sp.use_count() << endl;
    if(tmp1 == nullptr)
    {
        cout << "tmp1 == nullptr" << endl;
    }
}

#if 1
class son;
typedef shared_ptr<son> sonptr;
typedef weak_ptr<son> weaksonptr;
class parent
{
public:
    parent() {cout << "parent()" << endl;}
    ~parent() {cout << "~parent()" << endl;}
    sonptr sson;
//    weaksonptr wsson;
};
typedef shared_ptr<parent> parentptr;
typedef weak_ptr<parent> wparentptr;
class son
{
public:
    son() {cout << "son()" << endl;}
    ~son() {cout<< "~son()" << endl;}
//    parentptr father;
    wparentptr wfather;
};
int main()
{
    {
//        sonptr s(new son);
        parentptr p(new parent);
        sonptr s(new son);
        p->sson = s;
        s->wfather = p;
        cout << p.use_count() << endl;
        cout << s.use_count() << endl;
    }
//    cout << p.use_count() << endl;
//    cout << s.use_count() << endl;
    return 0;
}
#endif

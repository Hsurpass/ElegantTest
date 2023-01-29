#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Copy
{
public:
    Copy(int i = 10) : _i(new int(i))
    {
        cout << "Copy(int i), i=" << i << "," << this << endl;
    }
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << " Copy(const Copy & another), another._i=" << *another._i << "," << this << endl;
    }
    void dis()
    {
        cout << *_i << endl;
    }
    ~Copy()
    {
        delete _i;
        cout << "~Copy()" << this << endl;
    }
    int *_i;
};
typedef std::shared_ptr<Copy> copyPtr;

void test_vector_shared_ptr_moveConstructor()
{
    copyPtr cp(new Copy(110));
    cout << cp.use_count() << endl; // 1

    vector<copyPtr> vcp;
    vcp.push_back(std::move(cp)); // 调用shared_ptr 的 move constructor， 引用计数不变化
    cout << cp.use_count() << endl; // 0
    vcp.push_back(make_shared<Copy>(11));
    vcp.push_back(make_shared<Copy>(22));

    cout << "----------------------------" << endl;
    cout << vcp.size() << endl; // 3

    // 1,110
    // 1,11
    // 1,12
    for (auto &p : vcp)
    {
        cout << p.use_count() << "," << *p->_i << endl;
    }
}

void test_vector_shared_ptr()
{
    copyPtr cp(new Copy(110));
    cp->dis();
    copyPtr p1(new Copy(11));
    copyPtr p2(new Copy(12));

    cout << cp.use_count() << endl; // 1
    cout << p1.use_count() << endl; // 1
    cout << p2.use_count() << endl; // 1

    vector<copyPtr> vcp;
    vcp.push_back(cp); // 调用shared_ptr 的 copy constructor， 引用计数加一
    vcp.push_back(p1);
    vcp.push_back(p2);

    cout << "----------------------------" << endl;
    cout << vcp.size() << endl; // 3

    // 2,110
    // 2,11
    // 2,12
    for (auto &p : vcp)
    {
        cout << p.use_count() << "," << *p->_i << endl;
    }
}

void test_shared_ptr_stdMove()
{
    shared_ptr<Copy> sp(new Copy(11));
    shared_ptr<Copy> sp1(sp);
    shared_ptr<Copy> sp2(sp);

    cout << sp.use_count() << endl;  // 3
    cout << sp1.use_count() << endl; // 3
    cout << sp2.use_count() << endl; // 3

    cout << "------------------------------" << endl;
    shared_ptr<Copy> stmp = move(sp);   // std::move会把引用计数和资源都转移

    cout << stmp.use_count() << endl; // 3
    cout << sp.use_count() << endl;   // 0
    cout << sp1.use_count() << endl;  // 3
    cout << sp2.use_count() << endl;  // 3

    if (sp == NULL)
    {
        cout << "sp == NULL" << endl; // sp == NULL
    }
    if (sp1 != NULL)
    {
        cout << "sp1 != NULL" << endl; // sp1 != NULL
        cout << *sp1->_i << endl;      // 11
    }
}

void test_shared_ptr_unique()
{
    shared_ptr<Copy> sp(new Copy(11));
    cout << sp.use_count() << endl; // 1

    if (sp.unique())
    {
        cout << "unique" << endl;
    }

    shared_ptr<Copy> ssp(sp);
    cout << sp.use_count() << endl;  // 2
    cout << ssp.use_count() << endl; // 2

    if (sp.unique())
    {
        cout << "unique" << endl;
    }
    else
    {
        cout << "no unique" << endl;
    }
}

void test_shared_ptr_swap()
{
    shared_ptr<Copy> sc = make_shared<Copy>(100);
    shared_ptr<Copy> other = make_shared<Copy>(200);
    sc = other;                        // sc ~Copy()
    sc->dis();                         // 200
    cout << other.use_count() << endl; // 2

    shared_ptr<Copy> another = make_shared<Copy>(300);
    cout << another.use_count() << endl; // 1
#if 0
    other = another;
    cout << another.use_count() << endl;  // 2
    cout << other.use_count() << endl;    // 2
    cout << sc.use_count() << endl;       // 1
    other->dis(); // 300
#endif
#if 1
    other.swap(another);    //交换的是other,不关sc的事，原来是sc和other指向200，现在是sc和another指向200
    cout << another.use_count() << endl; // 2
    cout << other.use_count() << endl;   // 1
    cout << sc.use_count() << endl;      // 2
    another->dis();                      // 200
    other->dis();                        // 300
    sc->dis();                           // 200
#endif
}

void test_shared_ptr_one_assign_other()
{
    {
        shared_ptr<Copy> sc = make_shared<Copy>(100);
        shared_ptr<Copy> sc1 = sc;
        cout << sc1.use_count() << endl; // 2
        shared_ptr<Copy> other = make_shared<Copy>(111);
        shared_ptr<Copy> other1 = other;
        shared_ptr<Copy> other2 = other;
        cout << other.use_count() << other1.use_count() << other2.use_count() << endl; // 3 3 3

        sc = other; // sc 引用计数减一，托管新资源，新资源引用计数加一。
        cout << sc1.use_count() << endl;   // 1
        sc1->dis();                        // 100
        cout << sc.use_count() << endl;    // 4
        sc->dis();                         // 111
        cout << other.use_count() << endl; // 4
    }
    cout << "----------------" << endl;
}

void test_shared_ptr_reset_self()
{
    shared_ptr<Copy> sc = make_shared<Copy>(100);
    cout << sc.use_count() << endl; // 1
    shared_ptr<Copy> sc1 = sc;
    shared_ptr<Copy> sc2 = sc;
    cout << sc.use_count() << endl; // 3
    cout << sc.get() << endl;

    sc.reset(new Copy(*sc));
    cout << sc.use_count() << endl;  // 1
    sc->dis();                       // 100
    cout << sc.get() << endl;

    cout << sc1.use_count() << endl; // 2
    cout << sc2.use_count() << endl; // 2
    sc1->dis();                      // 100
}

void func_reset(shared_ptr<int> tmp)
{
    cout << tmp.use_count() << endl; // 2
    tmp.reset();
    cout << tmp.use_count() << endl; // 0

    // cout << *tmp << endl; // core dump
}

void test_shared_ptr_reset02()
{
    int *p = new int(1000);

    shared_ptr<int> ssp(p);
    cout << ssp.use_count() << endl; // 1

    func_reset(ssp);

    cout << ssp.use_count() << endl; // 1
    int *pp = ssp.get();
    cout << *pp << endl; // 1000
}

void test_shared_ptr_reset01()
{

    cout << "######################" << endl;
    {
        shared_ptr<Copy> sp(new Copy(10));
        shared_ptr<Copy> sp2(sp);
        shared_ptr<Copy> sp3(sp);
        cout << sp.use_count() << endl; // 3
        sp.reset(); // 引用计数减一，同时放弃托管
        // sp.reset();sp.reset();sp.reset();   // 多次reset也只是对自己的引用计数减一
        // sp2.reset();
        // sp3.reset();

        cout << sp.use_count() << endl; // 0
        // cout << *sp->_i << endl;            // core dump
        cout << sp2.use_count() << endl; // 2
        cout << sp3.use_count() << endl; // 2
        cout << "++++++++++++++++++++" << endl;
    }
    cout << "---------------" << endl;
}

void test_shared_ptr_get()
{
    shared_ptr<Copy> sc(new Copy(10));
    cout << sc.use_count() << endl; // 1

    Copy *pp = sc.get();
    cout << *pp->_i << endl; // 10

    cout << sc.use_count() << endl; // 1
}

void test_shared_ptr_refCount03()
{
    int *p = new int(10);
    shared_ptr<int> sp(p);
    cout << sp.use_count() << endl; // 1 

    delete p;
    // cout << *sp << endl;            // crash
    cout << sp.use_count() << endl; // 1 托管的指针被释放了而引用计数还在
    cout << "-----------------------" << endl;
}

void test_shared_ptr_refCount02()
{
    int *p = new int(10);
    {
        shared_ptr<int> sp(p);

        cout << *sp << endl;            // 10
        cout << sp.use_count() << endl; // 1    p被释放
    }
    shared_ptr<int> sp1(p);
    cout << sp1.use_count() << endl; // 1
} // core dump

void func(shared_ptr<int> tmp)
{
    cout << *tmp << endl;            // 10
    cout << tmp.use_count() << endl; // 3
}

void test_shared_ptr_refCount01()
{
    shared_ptr<int> sp(new int(10));

    cout << *sp << endl;            // 10
    cout << sp.use_count() << endl; // 1

    shared_ptr<int> sp1(sp);
    cout << *sp1 << endl;            // 10
    cout << sp1.use_count() << endl; // 2
    cout << sp.use_count() << endl;  // 2
    cout << "===============" << endl;

    func(sp1);

    cout << "===============" << endl;
    cout << sp1.use_count() << endl; // 2
    cout << sp.use_count() << endl;  // 2
}

int main()
{
    // test_shared_ptr_refCount01();
    // test_shared_ptr_refCount02();
    // test_shared_ptr_refCount03();
    // test_shared_ptr_get();
    // test_shared_ptr_reset01();
    // test_shared_ptr_reset02();
    // test_shared_ptr_unique();
    // test_shared_ptr_stdMove();
    // test_vector_shared_ptr();
    // test_vector_shared_ptr_moveConstructor();
    // test_shared_ptr_reset_self();
    // test_shared_ptr_one_assign_other();
    test_shared_ptr_swap();

    return 0;
}
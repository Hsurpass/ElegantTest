#include <iostream>
#include <memory>

using namespace std;

class B;
class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }
    A(int i)
    {
        cout << "A(int i)" << endl;
        m_i = i;
    }
    A(const A& another) : m_i(another.m_i)
    {
        cout << "A(const A& another)" << endl;
    }
    A(A&& another) : m_i(another.m_i)
    {
        cout << "A(A&& another)" << endl;
    }

    ~A()
    {
        cout << "~A()" << endl;
    }

    std::weak_ptr<B> m_b;
    // std::shared_ptr<B> m_b;
    int m_i;
};

class B
{
public:
    B()
    {
        cout << "B()" << endl;
    }
    ~B()
    {
        cout << "~B()" << endl;
    }

    std::shared_ptr<A> m_a;
};

void test_circular_reference()
{
    std::shared_ptr<A> sha(new A());
    std::shared_ptr<B> shb(new B());

    cout << sha.use_count() << endl; // 1
    cout << shb.use_count() << endl; // 1

    sha->m_b = shb;
    shb->m_a = sha;

    cout << sha.use_count() << endl; // 2
    cout << shb.use_count() << endl; // 1
}

// expired 过期的
void test_weak_ptr_reset_lock_expired()
{
    std::shared_ptr<A> sp1;
    std::weak_ptr<A> wp;

    sp1 = std::make_shared<A>(333);
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl; // 0 1 1 true 333
    wp = sp1;
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl; // 1 0 1 true 333

    sp1.reset(new A(222));
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl; // 0 1 1 true 222
    wp = sp1;
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl; // 1 0 1 true 222
}

void test_weak_ptr_lock_nullptr()
{
    std::shared_ptr<A> sp1;
    std::weak_ptr<A> wp;
    cout << boolalpha;

    sp1 = std::make_shared<A>(111);
    cout << sp1.use_count() << sp1.unique() << endl; // 1 true

    wp = sp1;
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 1 true false

    {
        shared_ptr<A> sp2 = wp.lock();                                                 // operator()=
        cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 2 false false
        cout << sp2.use_count() << sp2.unique() << wp.expired() << endl; // 2 false false
    }

    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 1 true false

    cout << "--------------------------------" << endl;
    sp1 = nullptr;
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 0 false true
}

void test_weak_ptr_lock()
{
    std::shared_ptr<A> sp1, sp2;
    std::weak_ptr<A> wp;
    cout << boolalpha;

    sp1 = std::make_shared<A>(111);
    cout << sp1.use_count() << sp1.unique() << endl; // 1 true

    wp = sp1;
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 1 true false
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl; // 0 false false

    sp2 = wp.lock();                                                 // operator()=
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 2 false false
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl; // 2 false false

    sp1.reset(); // __shared_ptr().swap(*this);  就不指向数据了
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 0 false false
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl; // 1 true false

    sp2.reset();
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl; // 0 false true
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl; // 0 false true

    std::shared_ptr<A> sp3 = wp.lock();
    cout << sp3.use_count() << sp3.unique() << endl; // 0 false
}

void test_weak_ptr_reset()
{
    std::shared_ptr<A> sha(new A(30));
    weak_ptr<A> wp(sha);

    std::cout << "1. wp " << (wp.expired() ? "is" : "is not") << " expired\n"; // is not expired
    cout << "m_i:" << sha->m_i << ", sha.use_count:" << sha.use_count() << ", wp.use_count:" << wp.use_count()
         << endl; //  30 1 1

    wp.reset(); // __weak_ptr().swap(*this);  不监控任何对象

    std::cout << "2. wp " << (wp.expired() ? "is" : "is not") << " expired\n"; // is expired
    cout << "m_i:" << sha->m_i << ", sha.use_count:" << sha.use_count() << ", wp.use_count:" << wp.use_count()
         << endl; // 30 1 0
}

// weak_ptr只会交换监控的对象，不会交换shared_ptr的资源
void test_weak_ptr_swap()
{
    shared_ptr<A> sha1(new A(10));
    shared_ptr<A> sha2(new A(20));

    weak_ptr<A> wp1(sha1);
    weak_ptr<A> wp2(sha2);

    wp1.swap(wp2);

    cout << wp1.lock()->m_i << endl; // 20
    cout << wp2.lock()->m_i << endl; // 10
}

void test_weak_ptr_constructor()
{
    shared_ptr<A> sha(new A());

    weak_ptr<A> wp1(sha); // from shared_ptr
    weak_ptr<A> wp2 = sha; // from shared_ptr
    weak_ptr<A> wp3(wp1); // copy constructor
    weak_ptr<A> wp4(wp2); // copy constructor

    weak_ptr<A> wp5; // default constructor
    weak_ptr<A> wp6(wp5); // copy constructor

    cout << sha.use_count() << endl; // 1
    cout << wp1.use_count() << endl; // 1
    cout << wp2.use_count() << endl; // 1
    cout << wp3.use_count() << endl; // 1
    cout << wp4.use_count() << endl; // 1

    cout << wp5.use_count() << endl; // 0
    cout << wp6.use_count() << endl; // 0
}

void test_weak_ptr_weak_count()
{
    weak_ptr<A> wpa;

    {
        shared_ptr<A> spa = make_shared<A>();
        wpa = spa; // weak_count=1 use_count=1
        if (wpa.expired()) {
            cout << "spa is expired" << endl;
        }
    } // weak_count=1 use_count=0    // 使用make_shared构造的shared_ptr, 离开作用域时，只是调用析构，但是内存还没被释放。
    cout << "----------------------" << endl;
    if (wpa.expired()) {
        cout << "spa is expired" << endl;
        shared_ptr<A> spa1 = wpa.lock();
        if (spa1) {
            cout << "spa1 is true" << endl;
        }
        else {
            cout << "spa1 is null" << endl;
        }
    }
}

class C; // 前向声明

class D
{
public:
    std::shared_ptr<C> ptrc;
    ~D()
    {
        std::cout << "D destroyed" << std::endl;
    }
};

class C
{
public:
    std::shared_ptr<D> ptrd;
    ~C()
    {
        std::cout << "C destroyed" << std::endl;
    }
};

void test_circle_ref()
{
    std::shared_ptr<C> c = std::make_shared<C>();
    std::shared_ptr<D> d = std::make_shared<D>();
    std::cout << "c usecount: " << c.use_count() << std::endl;
    std::cout << "d usecount: " << d.use_count() << std::endl;

    c->ptrd = d;
    d->ptrc = c;
    std::cout << "c usecount: " << c.use_count() << std::endl;
    std::cout << "d usecount: " << d.use_count() << std::endl;
}

int main()
{
    // test_circular_reference();
    // test_weak_ptr_constructor();
    // test_weak_ptr_swap();
    // test_weak_ptr_reset();
    // test_weak_ptr_lock();
    // test_weak_ptr_reset_lock_expired();
    // test_weak_ptr_lock_nullptr();
    // test_weak_ptr_weak_count();
    test_circle_ref();

    return 0;
}
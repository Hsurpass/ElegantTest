#include <iostream>
#include <memory>

using namespace std;

class B;
class A 
{
public:
    A() { cout << "A()" << endl; }
    A(int i) { cout << "A(int i)" << endl; m_i = i; }
    A(const A& another):m_i(another.m_i) { cout << "A(const A& another)" << endl; }
    A(A&& another):m_i(another.m_i) { cout << "A(A&& another)" << endl; }

    ~A() { cout << "~A()" << endl; }

    std::weak_ptr<B> m_b;
    // std::shared_ptr<B> m_b;
    int m_i;
};

class B
{
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }

    std::shared_ptr<A> m_a;
};

void test_circular_reference()
{
    std::shared_ptr<A> sha(new A());
    std::shared_ptr<B> shb(new B());

    cout << sha.use_count() << endl;    // 1
    cout << shb.use_count() << endl;    // 1

    sha->m_b = shb;
    shb->m_a = sha;

    cout << sha.use_count() << endl;    // 2
    cout << shb.use_count() << endl;    // 1
}

// expired 过期的
void test_weak_ptr_reset_lock_expired()
{
    std::shared_ptr<A> sp1;
    std::weak_ptr<A> wp;

    sp1 = std::make_shared<A>(333);
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl;   // 0 1 1 true 333
    wp = sp1;
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl;   // 1 0 1 true 333

    sp1.reset(new A(222));
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl;   // 0 1 1 true 222
    wp = sp1;
    cout << wp.use_count() << wp.expired() << sp1.use_count() << sp1.unique() << sp1->m_i << endl;   // 1 0 1 true 222

}

void test_weak_ptr_lock()
{
    std::shared_ptr<A> sp1, sp2;
    std::weak_ptr<A> wp;
    cout << boolalpha;

    sp1 = std::make_shared<A>(111);
    cout << sp1.use_count() << sp1.unique() << endl;   // 1 true
    
    wp = sp1;
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl;   // 1 true false
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl;   // 0 false false

    sp2 = wp.lock();    // operator()=
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl;   // 2 false false
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl;   // 2 false false

    sp1.reset();    // __shared_ptr().swap(*this);  就不指向数据了
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl;   // 0 false false
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl;   // 1 true false

    sp2.reset();
    cout << sp1.use_count() << sp1.unique() << wp.expired() << endl;   // 0 false true
    cout << sp2.use_count() << sp2.unique() << wp.expired() << endl;   // 0 false true

    std::shared_ptr<A> sp3 = wp.lock();
    cout << sp3.use_count() << sp3.unique() << endl;    // 0 false

}

void test_weak_ptr_reset()
{
    std::shared_ptr<A> sha(new A(30));
    weak_ptr<A> wp(sha);

    std::cout << "1. wp " << (wp.expired() ? "is" : "is not") << " expired\n";
    cout << "m_i:" << sha->m_i << ", sha.use_count:" << sha.use_count() << ", wp.use_count:" << wp.use_count() << endl;

    wp.reset();

    std::cout << "2. wp " << (wp.expired() ? "is" : "is not") << " expired\n";
    cout << "m_i:" << sha->m_i << ", sha.use_count:" << sha.use_count() << ", wp.use_count:" << wp.use_count() << endl;
    
}

// weak_ptr只会交换监控的对象，不会交换shared_ptr的资源
void test_weak_ptr_swap()
{
    shared_ptr<A> sha1(new A(10));
    shared_ptr<A> sha2(new A(20));

    weak_ptr<A> wp1(sha1);
    weak_ptr<A> wp2(sha2);

    wp1.swap(wp2);

    cout << wp1.lock()->m_i << endl;  // 20
    cout << wp2.lock()->m_i << endl;  // 10

}

void test_weak_ptr_constructor()
{
    shared_ptr<A> sha(new A());

    weak_ptr<A> wp1(sha);
    weak_ptr<A> wp2 = sha;
    weak_ptr<A> wp3(wp1);
    weak_ptr<A> wp4(wp2);

    cout << sha.use_count() << endl;    // 1
    cout << wp1.use_count() << endl;    // 1
    cout << wp2.use_count() << endl;    // 1
    cout << wp3.use_count() << endl;    // 1
    cout << wp4.use_count() << endl;    // 1

}

int main()
{
    // test_circular_reference();
    // test_weak_ptr_constructor();
    // test_weak_ptr_swap();
    // test_weak_ptr_reset();
    test_weak_ptr_lock();
    // test_weak_ptr_reset_lock_expired();

    return 0;
}
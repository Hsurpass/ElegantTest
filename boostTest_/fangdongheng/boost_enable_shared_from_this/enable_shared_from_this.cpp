#include <iostream>
#include <functional>
#include <memory>
#include <list>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/smart_ptr.hpp>
//#include <boost/asio/steady_timer.hpp>
//#include <boost/thread.hpp>
//#include <boost/chrono.hpp>

using namespace std;

using msgCallback = std::function<void()>;

class A {
public:
    A() {
        cout << "A::A()" << endl;
    }
    ~A() { 
        cout << "A::~A()" << endl; 
    }
    void output() {
        cout << "A::output()" << endl;
    }
};

class B {
public:
    B() {
        cout << "B::B()" << endl;
    }
    ~B() {
        cout << "B::~B()" << endl;
    }
    void setCallback(const msgCallback& cb) {
        if (m_cb == nullptr)
            m_cb = cb;
    }
    void resetCallback() {
        m_cb = nullptr;
    }
private:
    //msgCallback m_cb;
    msgCallback m_cb;

};
int main()
{
    //shared_ptr<B> spb = make_shared<B>();
    {
        shared_ptr<B> spb = make_shared<B>();
        shared_ptr<A> spa = make_shared<A>();   //use_count:1

        list<shared_ptr<A>> lst;
        lst.push_back(spa);     //use_count:2
        cout << "count1: " << spa.use_count() << endl;
        {
            std::function<void()> f = std::bind(&A::output, spa/*.get()*/);   //use_count:3
            spb->setCallback(f);    //use_count:4
            cout << "count2: " << spa.use_count() << endl;
        }   //use_count:3
        cout << "count3: " << spa.use_count() << endl;

        if (!lst.empty())
            lst.erase(lst.begin());     //use_count:2
        cout << "count4: " << spa.use_count() << endl;
    }   //use_count:1

    //期望spa在lst.erase后就析构
    //结果spb->m_cb还具有spa的一份引用，导致A不能按预期析构

    system("pause");
    return 0;
}


#if 0
class A
{
public:
    A(int &a) :m_a(a){
        m_a = 100;
    }
//private:
    int &m_a;
};
int main()
{
    int tmp = 10;
    A a1(tmp);
    cout << tmp << endl;
    while (true)
    {

    }
    return 0;
}
#endif
#if 0

class self_shared :public boost::enable_shared_from_this<self_shared>
{
public:
    self_shared(int n):x(n){ cout << "self_shared()" << endl; }
    ~self_shared(){ cout << "~self_shared()" << endl; }
    void print()
    {
        cout << "x: " << x << endl;
    }
//private:
    int x;

};


int main_error()
{
    self_shared ss(100);
    auto p = ss.shared_from_this();//error 
    cout << p.use_count() << endl;

}
int main01()
{
    auto p = boost::make_shared<self_shared>(10);
    p->print();
    cout << p.use_count() << endl;
    cout << "----------------------" << endl;

    /*auto p1 = p->shared_from_this();
    p1->x = 100;
    p1->print();
    p->print();*/
    cout << (p->shared_from_this()).use_count() << endl;

    cout << "----------------------" << endl;
    cout << p.use_count() << endl;
    //cout << p1.use_count() << endl;

    while (true)
    {

    }

    return 0;
}

#endif
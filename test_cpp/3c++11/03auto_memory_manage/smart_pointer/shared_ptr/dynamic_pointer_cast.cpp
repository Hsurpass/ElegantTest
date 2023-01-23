#include <iostream>
#include <memory>

using namespace std;

class IDATA
{
public:
    IDATA() { cout << "IDATA(), this:" << this << endl; }
    virtual ~IDATA() { cout << "~IDATA(), this:" << this << endl; }
    virtual int getdata() { cout << "IDATA::getdata, this:" << this << endl; return 0; };
};

class USERINFO : public IDATA
{
public:
    USERINFO(int i = 10) : m_data(i)
    {
        cout << "USERINFO(int i = 10), this:" << this << endl;
    }
    ~USERINFO() { cout << "~USERINFO(), this:" << this << endl; }
    virtual int getdata() { cout << "USERINFO::getdata(), m_data: " << m_data << endl; return m_data; }

    int m_data;
};

class D
{
public:
    int m_d;
};

/*
template<class D, class B>
shared_ptr<D> dynamic_cast_pointer(const shared_ptr<B>& r)
该函数不会抛出任何异常（noexcept）。若执行成功（ 前提：shared_ptr<B>对象 r 已经指向了一个D对象），则返回 shared_ptr<D> 共享资源的所有权，否则返回一个空对象。
*/

void test_dynamic_pointer_cast01()
{
    shared_ptr<IDATA> idataptr(new IDATA);
    shared_ptr<USERINFO> userinfoptr(new USERINFO(20));
    cout << idataptr.use_count() << endl;   // 1
    cout << userinfoptr.use_count() << endl;// 1
    idataptr->getdata();    // IDATA::getdata
    userinfoptr->getdata(); // 20

    idataptr = userinfoptr;    // 释放旧的，托管新的
    cout << idataptr.use_count() << endl;   // 2
    cout << userinfoptr.use_count() << endl;// 2
    idataptr->getdata();    // 20
    userinfoptr->getdata(); // 20

    // idataptr = static_pointer_cast<IDATA>(userinfoptr);    // 释放旧的，托管新的
    // idataptr = dynamic_pointer_cast<IDATA>(userinfoptr);    // 释放旧的，托管新的
    cout << "----------------------------" << endl;
    //    cout << dynamic_cast<USERINFO>(idataptr) << endl;
    shared_ptr<USERINFO> userinfoptr2 = dynamic_pointer_cast<USERINFO>(idataptr);   // 下转
    cout << idataptr.use_count() << endl;       // 3
    cout << userinfoptr.use_count() << endl;    // 3
    cout << userinfoptr2.use_count() << endl;   // 3
    idataptr->getdata();    // 20
    userinfoptr->getdata(); // 20
    userinfoptr2->getdata();// 20
}

void test_dynamic_pointer_cast02()
{
    shared_ptr<IDATA> iptr(new USERINFO(100));
    cout << iptr.use_count() << endl;   // 1
    cout << iptr->getdata() << endl;    // 100
    shared_ptr<USERINFO> uptr = dynamic_pointer_cast<USERINFO>(iptr);
    if(uptr)
    {
        cout << "dynamic_pointer_cast success" << endl;
    }
    else
    {
        cout << "dynamic_pointer_cast failed" << endl;
    }
    cout << uptr.use_count() << endl;   // 2
    cout << uptr->getdata() << endl;    // 100
    cout << "--------------------" << endl;

    shared_ptr<D> dptr = dynamic_pointer_cast<D>(iptr);
    if(dptr)
    {
        cout << "dynamic_pointer_cast success" << endl;
    }
    else
    {
        cout << "dynamic_pointer_cast failed" << endl;
    }
    cout << dptr.use_count() << endl;   // 0

}

int main()
{
    // test_dynamic_pointer_cast01();
    test_dynamic_pointer_cast02();

    return 0;
}

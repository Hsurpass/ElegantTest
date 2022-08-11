#include <iostream>
#include <memory>

using namespace std;

class IDATA
{
public:
    IDATA() { cout << "IDATA()" << endl; }
    virtual ~IDATA() { cout << "~IDATA()" << endl; }
    virtual int getdata() { cout << "IDATA::getdata" << endl; };
};

class USERINFO : public IDATA
{
public:
    USERINFO(int i = 10) : m_data(i)
    {
        cout << "USERINFO(int i = 10)" << endl;
    }
    ~USERINFO() { cout << "~USERINFO()" << endl; }
    virtual int getdata() { return m_data; }

    int m_data;
};

class D
{
public:
    int m_d;
};

void test_dynamic_pointer_cast01()
{
    shared_ptr<IDATA> idataptr(new IDATA);
    shared_ptr<USERINFO> userinfoptr(new USERINFO(20));
    cout << userinfoptr->m_data << endl;    // 20
    idataptr = userinfoptr;    // 释放旧的，托管新的
    // idataptr = static_pointer_cast<IDATA>(userinfoptr);    // 释放旧的，托管新的
    // idataptr = dynamic_pointer_cast<IDATA>(userinfoptr);    // 释放旧的，托管新的
    cout << "----------------------------" << endl;
    //    cout << dynamic_cast<USERINFO>(idataptr) << endl;
    shared_ptr<USERINFO> userinfoptr2 = dynamic_pointer_cast<USERINFO>(idataptr);
    cout << userinfoptr2->m_data << endl;

}

void test_dynamic_pointer_cast02()
{
    shared_ptr<IDATA> iptr(new USERINFO(100));
    cout << iptr.use_count() << endl;
    cout << iptr->getdata() << endl; 
    shared_ptr<USERINFO> uptr = dynamic_pointer_cast<USERINFO>(iptr);
    if(uptr)
    {
        cout << "dynamic_pointer_cast success" << endl;
    }
    else
    {
        cout << "dynamic_pointer_cast failed" << endl;
    }
    cout << uptr.use_count() << endl;
    cout << uptr->getdata() << endl; 
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
    cout << dptr.use_count() << endl; 

}

int main()
{
    test_dynamic_pointer_cast01();
    // test_dynamic_pointer_cast02();

    return 0;
}

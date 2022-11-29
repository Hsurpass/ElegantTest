#include <iostream>

using namespace std;

class Phone
{
public:
    virtual int cost() = 0;
    virtual ~Phone(){}
};

class IPhone:public Phone
{
public:
    int cost() { return 8000; }
};

// 要保证装饰完了，原功能还能使用，所以要继承自Phone,保证原有接口能访问
// 一辆车装饰完了不能开了就搞笑了
class BaseDecorator : public Phone
{
public:
    BaseDecorator(Phone* phone):m_phone(phone){}
    int cost() { cout << "BaseDecorator" << endl; }
protected:
    Phone* m_phone;
};

class PhoneScreen : public BaseDecorator
{
public:
    PhoneScreen(Phone* phone):BaseDecorator(phone){}
    int cost() { return m_phone->cost() + 200;}
};
class PhoneShell : public BaseDecorator
{
public:
    PhoneShell(Phone* phone):BaseDecorator(phone){}
    int cost() { return m_phone->cost() + 20; }   
};

void test_decorator01()
{
    Phone* phone = new IPhone();
    cout << phone->cost() << endl;

    PhoneScreen* ps = new PhoneScreen(phone);
    cout << ps->cost() << endl;
    
    PhoneShell* pshell = new PhoneShell(phone);
    cout << pshell->cost() << endl;
    delete pshell;
    delete ps;
    delete phone;

    Phone* allphone = new PhoneScreen(new PhoneShell(new IPhone()));
    cout << allphone->cost() << endl;
    
}

int main()
{
    test_decorator01();

    return 0;
}
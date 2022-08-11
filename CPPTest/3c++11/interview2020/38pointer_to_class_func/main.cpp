#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Student
{
public:
    Student(string n, int nu):name(n),num(nu){}
    void dis()
    {
        cout<<"name:"<<name<<" num:"<<num<<endl;
    }
    //private:
    string name;
    int num;
};

class A
{
public:
    A() {}
    //private:
    static void dis();
    //private:
    static int m_a;
};
int A::m_a = 100;
void A::dis()
{
    cout << m_a << endl;
}

class Widget
{
public:
    Widget()
    {
        pf[0] = f;
        pf[1] = g;
        pf[2] = h;
        pf[3] = i;
    }
    int getCount()
    {
        return cnt;
    }
    void select(int val, int sec)
    {
        if(sec<0 && sec>3) return ;
//        (this->*pf[sec])(val);
        (this->*(pf[sec]))(val);
    }
private:
    void f(int val ){cout<<"void f()"<<val<<endl;}
    void g(int val ){cout<<"void g()"<<val<<endl;}
    void h(int val ){cout<<"void h()"<<val<<endl;}
    void i(int val ){cout<<"void i()"<<val<<endl;}
    enum {cnt =4};
    void (Widget::*pf[4])(int);
};

class implementation
{
public:
    implementation(int v = 10):value(v) {

    }
    void setvalue(int v)
    {
        value = v;
    }
    int getvalue() const
    {
        return value;
    }
private:
    int value;
};

class delegte
{
public:
    delegte():pi(new implementation) {}
    ~delegte() {
        delete pi;
    }
    void setvalue(int v)
    {
        pi->setvalue(v);
    }
    int getvalue()const
    {
        return pi->getvalue();
    }
private:
    implementation* pi;
};
int main()
{
    delegte *pd = new delegte;
    pd->setvalue(100);

    cout  << pd->getvalue() << endl;
    return 0;
}
int main03()
{
    Widget w;
    //0 基本功能， 1 有特技 2 有魔法 3 开挂
    w.select(100,2);
    return 0;
}


int main02()
{
    //    int *pa = &A::m_a;
    //    cout << *pa << endl;

    //    void (*pfunc)() = &A::dis;
    //    pfunc();

    //    auto f = bind(&A::m_a,_1);
    //    cout <<  << endl;
    //    auto f = bind(&A::dis);
    //    f();
    //    cout << f() << endl;
    return 0;
}

int main01()
{
    Student s("zhangsan",23);
    Student s2("lisi",25);

    //    string Student::*pn = &Student::name;
    //    void (Student::*pfunc)(void) = &Student::dis;

    //    cout << s.*pn << endl;
    //    cout << s2.*pn << endl;

    Student *ps = new Student("zhaosi",33);
    //    cout << ps->*pn << endl;

    //    (s.*pfunc)();
    //    (s2.*pfunc)();
    //    (ps->*pfunc)();

    //    auto f = bind(&Student::dis,ps);
    //    f();
    //    auto f1 = bind(&Student::dis,_1);
    //    f1(s);
    //    f1(&s2);
    //    f1(ps);
    auto f2 = bind(&Student::num,_1);
    //    cout << f2(ps) << endl;
    cout << f2(Student("test",300)) << endl;

    return 0;
}

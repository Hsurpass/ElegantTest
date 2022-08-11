#include <iostream>
#include <typeinfo>

using namespace std;

class A
{
public:
    virtual ~A(){} // 若无此虚函数， 则称运行时信息不成立
};
class B:public A{
};
class C:public A{
};
void func(A *pa)
{
    cout<<typeid(pa).name()<<endl;
    cout<<typeid(*pa).name()<<endl;
}
void func(A &ra)
{
    cout<<typeid(ra).name()<<endl;
}
int main(int argc, char *argv[])
{
    B b; C c;
    A *pa = &b;
//     cout<<typeid(b).name()<<endl;
//     cout<<typeid(&b).name()<<endl;
//     cout<<typeid(pa).name()<<endl;
//     cout<<typeid(*pa).name()<<endl;

//     A &ra = b;
//     cout<<typeid(b).name()<<endl;
//     cout<<typeid(ra).name()<<endl;
//    func(&c);
//    func(&b);
    func(c);
    func(b);
    return 0;
}

#if 0
class Shape
{
public:

    Shape(int x,int y)
        :_x(x),_y(y){}
    void draw()
    {
        cout<<"draw Shap ";
        cout<<"start ("<<_x<<","<<_y<<") "<<endl;
    }
    //private:
protected:
    int _x;
    int _y;
};
class Circle: public Shape
{
public:
    Circle(int x, int y,int r)
        :Shape(x,y),_r(r){}
    void draw()
    {
        cout<<"draw Circle ";
        cout<<"start ("<<_x<<","<<_y<<") ";
        cout<<"raduis r = "<<_r<<endl;
    }
private:
    int _r;
};
int main()
{
    Shape s(3,5);
    s.draw();
    Circle c(1,2,4);
    c.draw();
    //子类对象赋给父类对象
    //    s = c;
    //    s.draw();

    //    //子类对象赋给父类引用
    //    Shape &rs = c;
    //    rs.draw();
    //    //子类对象地址赋给父类指针
    //    Shape *ps = &c;
    //    ps->draw();

    //    c = static_cast<Circle>(s);
    Circle *ci = static_cast<Circle*>(&s);
    ci->draw();



    return 0;
}
#endif

#if 0
class A
{
public:
    A()
    {
        cout<<this<<endl;
        cout<<typeid(this).name()<<endl;
    }

    int a;
};
class B:public A
{
public:
    B()
    {
        cout<<this<<endl;
        cout<<typeid(this).name()<<endl;
    }
    int b;
};
class C:public B
{
public:
    C()
    {
        cout<<this<<endl;
        cout<<typeid(this).name()<<endl;
    }
    void func()
    {
        cout<<&a<<endl;
        cout<<&b<<endl;
        cout<<&c<<endl;
    }
    int c;
};
int main()
{
    C c;
    cout<<"&c "<<&c<<endl;
    cout<<"*************"<<endl;
    c.func();
    return 0;
}
#endif

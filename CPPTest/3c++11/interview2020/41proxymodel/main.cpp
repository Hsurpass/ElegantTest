#include <iostream>
#include <unistd.h>
using namespace std;

class ccapplicationprotocol
{
public:
    ccapplicationprotocol() {cout << "ccapplicationprotocol()" << endl;}
    virtual ~ccapplicationprotocol() {cout << "~ccapplicationprotocol()" << endl;}
    virtual bool lauched() = 0;
};
class application:public ccapplicationprotocol
{
public:
    application()
    {
        cout << "application(),this: "<<this << endl;
        pap = this;
    }
    ~application() {cout << "~application()" << endl;}
//    bool lauched()
//    {
//        cout << "application-->start run" << endl;
//    }
    void run()
    {
        lauched();
    }
    static application* getinstance(){return pap;}
//    static application* pap;
private:
    static application* pap;
};
application* application::pap = 0;
//class delegate:private application
class delegate:public application
{
public:
    delegate() {
        cout << "delegate(),this:" << this << endl;
    }
    ~delegate() {cout << "~delegate()" << endl;}
    bool lauched()
    {
        cout << "delegate-->start run" << endl;
    }
};
class A
{
public:
    A() {}
private:
    static int*p;
    static int a;
};
int main()
{
//    cout << sizeof(ccapplicationprotocol) << endl;
//    cout << sizeof(application) << endl;
//    cout << sizeof(delegate) << endl;
//    cout << sizeof(A) << endl;
//    delegate de;
//    de.application::lauched();
//    de.getinstance()->run();
    return 0;
}
int main01()
{
//    ccapplicationprotocol cca;
//    ccapplicationprotocol *pcca;
//    ccapplicationprotocol *pcca = new ccapplicationprotocol;
//    ccapplicationprotocol *pcca = new delegate;
//    application ap;
//    application *pap;
//    application *pap = new application;
//    application *pap = new delegate;

    delegate app;
//    cout << app.pap << endl;
//    application *pap =  &app;
//    application *pap =  (application*)&app;
//    pap->run();
//    app.run();
    application::getinstance()->run();
    return 0;
}
#if 0
class Text
{
public:
    Text() {}
    void showtext()
    {
        cout << "good text" << endl;
    }
};
class Image
{
public:
    Image() {}
    virtual void showpicture() = 0;
};
class bigimage:public Image
{
public:
    bigimage() {
        sleep(3);

     }
    void showpicture()
    {
        cout << "show picture" << endl;
    }

};
class proxyimage:public Image
{
public:
    proxyimage():bi(NULL) {}
    void showpicture()
    {
        if(NULL == bi)
        {
            bi = new bigimage;
        }

        bi->showpicture();
    }
private:
    bigimage* bi;
};
class Doc
{
public:
    Doc():t(new Text),pi(new proxyimage) {}
    void showtextandpic()
    {
        t->showtext();
        pi->showpicture();
    }
    ~Doc(){
        delete t;
        delete pi;
    }
private:
    Text *t;
    proxyimage *pi;
};
int main()
{
    Doc d;
    d.showtextandpic();
    return 0;
}
#endif

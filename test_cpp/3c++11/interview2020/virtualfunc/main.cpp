#include <iostream>

using namespace std;

class singlecore
{
public:
    virtual void work() = 0;
    virtual ~singlecore(){}
};
class singlecoreA:public singlecore
{
public:
    void work()
    {
        cout << "run singlecoreA" << endl;
    }

};

class singlecoreB:public singlecore
{
public:
    void work()
    {
        cout << "run singlecoreB" << endl;
    }

};
class factor
{
public:
    virtual singlecore* createproduct() = 0;
    virtual ~factor(){}

};
class factorA:public factor
{
public:
    singlecore* createproduct()
    {
        return new singlecoreA;
    }

};
class factorB:public factor
{
public:
    singlecore* createproduct()
    {
        return new singlecoreB;
    }

};
int main()
{
    factor *fac = new factorA;
    singlecore* pa = fac->createproduct();
    pa->work();

    factor *facb = new factorB;
    singlecore* pb = facb->createproduct();
    pb->work();
    return 0;
}

#if 0
class factor
{
public:
    factor() {cout << "factor() {}" << endl;}
    virtual ~factor() {cout << "~factor() {}" << endl;}
    virtual void work() = 0;
};

class coreA:public factor
{
public:
    coreA() {cout << "coreA()" << endl;}
    ~coreA() {cout << "~coreA()" << endl;}
    void work()
    {
        cout << "run coreA" << endl;
    }
};

int main()
{

    factor *pf = new coreA;
    pf->work();
    delete pf;

    return 0;
}

#endif

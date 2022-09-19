#include "a.h"


A::A()
{
    pconfa = Conf::getInstance();
    cout << pconfa->getip() << endl;
    cout << pconfa->getport() << endl;
}
A::~A()
{
//    delete pconfa;
//    pconfa = NULL;
}

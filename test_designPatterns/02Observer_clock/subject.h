#ifndef SUBJECT_H
#define SUBJECT_H
#include <iostream>
#include <list>
#include "observer.h"
using namespace std;

class Subject
{
public:
    Subject();
    void RegisterObserver(Observer* ob);
    void RemoveObserver(Observer* ob);
    virtual void notify() = 0;
protected:
    list<Observer*> observerlist;
};

#endif // SUBJECT_H

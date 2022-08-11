#ifndef AMERICATIME_H
#define AMERICATIME_H
#include "observer.h"

class Americatime:public Observer
{
public:
//    Americatime();
    void update(int hour,int minute,int second);
    void dis();
private:
    int _hour;
    int _minute;
    int _second;
};

#endif // AMERICATIME_H

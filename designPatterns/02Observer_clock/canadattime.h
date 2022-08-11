#ifndef CANADATTIME_H
#define CANADATTIME_H
#include "observer.h"

class CanadatTime:public Observer
{
public:
    CanadatTime();
    void update(int hour,int minute,int second);
    void dis();
private:
    int _hour;
    int _minute;
    int _second;
};

#endif // CANADATTIME_H

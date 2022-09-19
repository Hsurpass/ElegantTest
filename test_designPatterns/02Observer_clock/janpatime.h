#ifndef JANPATIME_H
#define JANPATIME_H
#include "observer.h"

class JanpaTime:public Observer
{
public:
    JanpaTime();
    void update(int hour,int minute,int second);
    void dis();
private:
    int _hour;
    int _minute;
    int _second;
};

#endif // JANPATIME_H

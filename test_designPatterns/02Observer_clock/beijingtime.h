#ifndef BEIJINGTIME_H
#define BEIJINGTIME_H
#include "subject.h"

class BeijingTime:public Subject
{
public:
    BeijingTime();
    void notify();
    void settimer(int hour,int minute,int second);
    void dis();
private:
    int _hour;
    int _minute;
    int _second;
};

#endif // BEIJINGTIME_H

#include "beijingtime.h"

BeijingTime::BeijingTime():Subject()
{

}
void BeijingTime::notify()
{
    list<Observer*>::iterator itr = observerlist.begin();
    for(;itr != observerlist.end();++itr)
    {
        (*itr)->update(_hour,_minute,_second);
        (*itr)->dis();
    }
}
void BeijingTime::settimer(int hour,int minute,int second)
{
    _hour = hour;
    _minute = minute;
    _second = second;
    notify();
}
void BeijingTime::dis()
{
    cout << "BeijingTime" << _hour <<":" << _minute <<":" << _second << endl;
}

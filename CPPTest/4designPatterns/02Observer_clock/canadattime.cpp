#include "canadattime.h"
#include <iostream>
using namespace std;
CanadatTime::CanadatTime():Observer()
{

}
void CanadatTime::update(int hour,int minute,int second)
{
    _hour = hour + 200;
    _minute = minute + 200;
    _second = second + 200;
}
void CanadatTime::dis()
{
    cout << "CanadatTime" << _hour <<":" <<_minute <<":" <<_second << endl;
}

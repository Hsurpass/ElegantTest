#include "janpatime.h"
#include <iostream>
using namespace std;
JanpaTime::JanpaTime():Observer()
{

}
void JanpaTime::update(int hour,int minute,int second)
{
    _hour = hour + 300;
    _minute = minute + 300;
    _second = second + 300;
}
void JanpaTime::dis()
{
    cout << "JanpaTime" << _hour  <<":"<<_minute<<":" <<_second << endl;
}

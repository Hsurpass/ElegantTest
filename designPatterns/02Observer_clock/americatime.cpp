#include "americatime.h"
#include <iostream>
using namespace std;

//Americatime::Americatime():Observer()
//{

//}
void Americatime::update(int hour,int minute,int second)
{
    _hour = hour + 100;
    _minute = minute + 100;
    _second = second + 100;
}
void Americatime::dis()
{
    cout << "Americatime" << _hour << ":" <<_minute << ":" <<_second << endl;
}

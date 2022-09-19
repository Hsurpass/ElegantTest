#include <iostream>
#include "beijingtime.h"
#include "americatime.h"
#include "canadattime.h"
#include "janpatime.h"

using namespace std;

int main()
{
    BeijingTime bjtime;
    Americatime ustime;
    CanadatTime canatime;
    JanpaTime japantime;
//    BeijingTime *bjtime = new BeijingTime;
//    Americatime * ustime = new Americatime;

//    bjtime->RegisterObserver(ustime);
    bjtime.RegisterObserver(&ustime);
    bjtime.RegisterObserver(&canatime);
    bjtime.RegisterObserver(&japantime);

    bjtime.settimer(10,10,10);
    bjtime.dis();

    return 0;
}

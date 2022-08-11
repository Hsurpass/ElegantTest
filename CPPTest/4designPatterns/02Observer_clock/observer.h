#ifndef OBSERVER_H
#define OBSERVER_H


class Observer
{
public:
//    Observer();
    virtual void update(int hour,int minute,int second) = 0;
    virtual void dis() = 0;
};

#endif // OBSERVER_H

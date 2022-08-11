#include <iostream>
#include <list>

using namespace std;
class observer
{
public:
    virtual void update(int hour,int minutes,int seconds) = 0;
};
class subject
{
public:
    virtual void registobject(observer* p)=0;
    virtual void removeobject(observer *p)=0;
    virtual void notify() = 0;

protected:
    list<observer*> lo;
};
class beijingtime:public subject
{
public:
    beijingtime() {}
    void registobject(observer* p)
    {
        lo.push_back(p);
    }
    void removeobject(observer *p)
    {
        lo.remove(p);
    }
    void notify()
    {
        for(list<observer*>::iterator itr = lo.begin();itr != lo.end();++itr)
        {
            (*itr)->update(m_hour,m_minutes,m_seconds);
        }
    }
    void settime(int hour,int minutes,int seconds)
    {
        m_hour = hour;
        m_minutes = minutes;
        m_seconds = seconds;
        dis();
        notify();
    }
    void dis()
    {
        cout << "beijing time: " << m_hour <<"/" <<m_minutes << "/"<< m_seconds << endl;
    }
private:
    int m_hour;
    int m_minutes;
    int m_seconds;
};

class americatime:public observer
{
public:
    americatime() {}
    void update(int hour,int minutes,int seconds)
    {
        m_hour = hour + 10;
        m_minutes = minutes + 10;
        m_seconds = seconds + 10;
        dis();
    }
    void dis()
    {
        cout << "america time: " << m_hour <<"/" <<m_minutes << "/"<< m_seconds << endl;
    }
private:
    int m_hour;
    int m_minutes;
    int m_seconds;
};

class japantime:public observer
{
public:
    japantime() {}
    void update(int hour,int minutes,int seconds)
    {
        m_hour = hour + 20;
        m_minutes = minutes + 20;
        m_seconds = seconds + 20;
        dis();
    }
    void dis()
    {
        cout << "japan time: " << m_hour <<"/" <<m_minutes << "/"<< m_seconds << endl;
    }
private:
    int m_hour;
    int m_minutes;
    int m_seconds;
};

int main()
{
    beijingtime bt;
    americatime at;
    japantime jt;
    bt.registobject(&at);
    bt.registobject(&jt);
    bt.settime(1,2,3);
    cout << "----------------" << endl;
    bt.removeobject(&at);
    bt.settime(4,5,6);

    return 0;
}

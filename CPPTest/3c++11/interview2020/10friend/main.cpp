#include <iostream>
#include <memory>
using namespace std;

class Watch;
/**
* 定义 Time 类
* 数据成员： m_iHour， m_iMinute， m_iSecond
* 成员函数： 构造函数
* 友元类： Watch
*/
class Time
{
    // 友元类
    friend class Watch;
public:
    Time(){}
    Time(int hour, int min, int sec)
    {
        m_iHour = hour;
        m_iMinute = min;
        m_iSecond = sec;
    }
    void dis()
    {
        cout << "sizeof(m_sw): " << sizeof(m_sw) << endl;
        cout << "sizeof(m_ww): " << sizeof(m_ww) <<endl;
    }
public:
    int m_iHour;
    int m_iMinute;
    int m_iSecond;
//    Watch *w;
    shared_ptr<Watch> m_sw;
    weak_ptr<Watch> m_ww;
};
/**
* 定义 Watch 类
* 数据成员： m_tTime
* 成员函数： 构造函数
* display 用于显示时间
*/
class Watch
{
public:
    Watch(Time t):m_tTime(t){}
    void display()
    {
        cout << m_tTime.m_iHour << endl;
        cout << m_tTime.m_iMinute << endl;
        cout << m_tTime.m_iSecond << endl;
    }
public:
    Time m_tTime;
};
int main()
{
    cout << sizeof(Time) << endl;
    Time t;
    t.dis();
    cout <<sizeof(shared_ptr<Watch>) << endl;
    cout <<sizeof(shared_ptr<Time>) << endl;
    cout <<sizeof(shared_ptr<int>) << endl;
    cout <<sizeof(shared_ptr<double>) << endl;
}
int main01()
{
    Time t(6, 30, 20);
    Watch w(t);
    w.display();

    return 0;
}

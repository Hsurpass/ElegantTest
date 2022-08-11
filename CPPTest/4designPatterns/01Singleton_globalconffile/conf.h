#ifndef CONF_H
#define CONF_H
#include <iostream>

using namespace std;
class Conf
{
public:
    static Conf* getInstance();
    static void releaseInstance();

    inline string getip(){return ip;}
    inline string getport(){return port;}
private:
    static Conf* _ins;
    void init();
    Conf();
    ~Conf();

    string ip;
    string port;
};

#endif // CONF_H

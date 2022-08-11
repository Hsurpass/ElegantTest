#include "conf.h"
#include <fstream>
Conf* Conf::_ins = nullptr;
Conf::Conf()
{

}
Conf::~Conf()
{

}
Conf* Conf::getInstance()
{
    if(_ins == nullptr)
    {
        _ins = new Conf;
        _ins->init();
    }
    return _ins;
}
void Conf::releaseInstance()
{
    if(_ins != nullptr)
    {
        delete _ins;
        _ins = NULL;
    }
}
void Conf::init()
{
    fstream fs;
    fs.open("ip.conf",ios::in | ios::out);
    if(!fs)
    {
        cout << "open error" << endl;
    }
    fs >> ip;
    fs >> port;
    fs.close();
}

#include "c.h"
#include "conf.h"

C::C()
{
    Conf* pconfc = Conf::getInstance();
    cout << pconfc->getip() << endl;
    cout << pconfc->getport() << endl;
}

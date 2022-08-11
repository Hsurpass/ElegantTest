#include "b.h"
#include "conf.h"

B::B()
{
    Conf* pconfb = Conf::getInstance();
    cout << pconfb->getip() << endl;
    cout << pconfb->getport() << endl;
}

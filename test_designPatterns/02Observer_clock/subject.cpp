#include "subject.h"

Subject::Subject()
{

}
void Subject::RegisterObserver(Observer* ob)
{
    observerlist.push_back(ob);
}
void Subject::RemoveObserver(Observer* ob)
{
    observerlist.remove(ob);
}

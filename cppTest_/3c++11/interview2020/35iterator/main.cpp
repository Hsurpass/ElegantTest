#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    ostream_iterator<int> outitr(cout,"\n");
    *outitr = 33;
    outitr++;
    *outitr = 44;
    outitr++;
    *outitr = -10;
    outitr++;

    return 0;
}

int main01()
{
    list<int> li = {1,2,3,4,5,6,7,8,9,10};

    list<int>::iterator itr = li.begin();
//    itr = std::next(itr,9);
//    itr = std::next(itr,-10);
//    cout << std::distance(li.begin(),itr) << endl;
//    cout << std::distance(li.begin(),li.end()) << endl;

//    std::advance(itr,5);
//    std::advance(itr,-1);

//    itr = std::prev(itr,100);
//    itr = prev(itr,-100);
//    itr = prev(li.end());

//    cout << std::distance(li.begin(),itr) << endl;
    copy(li.begin(),li.end(),ostream_iterator<int>(cout," "));
    cout << endl;
    cout << "---------------------" << endl;
    if(itr == li.end())
    {
        cout <<"itr == end" << endl;
    }
    else
    {
        cout << *itr << endl;
    }


    return 0;
}

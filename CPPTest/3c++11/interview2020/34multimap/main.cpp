#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    multimap<char,int> mymm;
    mymm.insert(pair<char,int>('a',10));
    mymm.insert(pair<char,int>('b',20));
    mymm.insert(pair<char,int>('b',30));
    mymm.insert(pair<char,int>('b',40));
    mymm.insert(pair<char,int>('d',50));
    mymm.insert(pair<char,int>('d',60));
    mymm.insert(pair<char,int>('f',60));

    multimap<char,int>::iterator lowitr,upperitr;
    pair<multimap<char,int>::iterator,multimap<char,int>::iterator> equalitr;
//    lowitr = mymm.lower_bound('b');
//    upperitr = mymm.upper_bound('b');
//    equalitr = mymm.equal_range('c');

//    upperitr = mymm.upper_bound('d');
//    if(upperitr == mymm.end())
//    {
//        cout << "upperitr == end" << endl;
//    }

//    equalitr = mymm.equal_range('d');
//    equalitr = mymm.equal_range('f');
//    if(equalitr.first == mymm.end())
//    {
//        cout << "equalitr.first == mymm.end" << endl;
//    }
//    if(equalitr.second == mymm.end())
//    {
//        cout << "equalitr.second == mymm.end" << endl;
//    }
//    equalitr = mymm.equal_range('c');

    lowitr = mymm.lower_bound('c');
    upperitr = mymm.upper_bound('c');

    cout << lowitr->first << ":" << lowitr->second << endl;
    cout << upperitr->first << ":" << upperitr->second << endl;
//    cout << equalitr.first->first << ":" << equalitr.first->second << endl;
//    cout << equalitr.second->first << ":" << equalitr.second->second << endl;

//    cout << mymm.count('b') << endl;
//    cout << mymm.count('d') << endl;
//    cout << mymm.count('f') << endl;
    return 0;
}

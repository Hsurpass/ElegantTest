#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>

void test_unordered_map01()
{
    unordered_map<const char *,int, hash<const char *>> hm;
    hm["monday"] = 100;
    hm["tuesday"] = 200;
    hm["wednesday"] = 300;
    hm["thursday"] = 500;
    hm["friday"] = 600;
    hm["saturday"] = 1000;
    hm["sunday"] = 500;
    cout<<"sunday=>"<<hm["sunday"]<<endl;
    for(auto &item: hm)
    {
        cout<<item.first<<":" << item.second << endl;
    }
}

int main()
{
    test_unordered_map01();
    
    return 0;
}
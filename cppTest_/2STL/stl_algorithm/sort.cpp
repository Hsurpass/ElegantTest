#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// C++ primer 14.8.2
void test_sort_pointer()
{
    string s1("m");
    string s2("a");
    string s3("n");

    vector<string*> vsp;
    vsp.push_back(&s1);
    vsp.push_back(&s2);
    vsp.push_back(&s3);

    std::sort(vsp.begin(), vsp.end(), [](string* a, string* b){ return a < b; });
    for (size_t i = 0; i < vsp.size(); i++)
    {
        cout << *vsp[i] << " ";
    }
    cout << endl;

    std::sort(vsp.begin(), vsp.end(), less<string*>());
    for (size_t i = 0; i < vsp.size(); i++)
    {
        cout << *vsp[i] << " ";
    }
    cout << endl;

}

int main()
{
    test_sort_pointer();

    return 0;
}
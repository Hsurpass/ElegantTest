#include <iostream>
#include <memory>
#include <string>

using namespace std;
void func(auto_ptr<int> ap2)
{
    cout << "func " << *ap2 << endl;
}
int main()
{
    int * p = new int(10);

    auto_ptr<int> ap(p);
    auto_ptr<int> ap1(p);
//    auto_ptr<int> ap2;
//    ap2 = ap;
    func(ap);
    cout << *ap << endl;
    cout << *ap1 << endl;
//    cout << *ap2 << endl;

//    func(ap);
//    cout << *ap << endl;



}

int main01()
{
    auto_ptr<string> films[4] = {
        auto_ptr<string> (new string("aaaa")),
        auto_ptr<string> (new string("bbbb")),
        auto_ptr<string> (new string("cccc")),
        auto_ptr<string> (new string("dddd")),
    };
//    auto_ptr<string> &pwin = films[2];
    auto_ptr<string> pwin;
    pwin = films[2];
    cout << *pwin << endl;
    for(int i = 0;i < 4;++i)
    {
        cout << *films[i] << endl;
    }
    cout << *pwin << endl;
    return 0;
}

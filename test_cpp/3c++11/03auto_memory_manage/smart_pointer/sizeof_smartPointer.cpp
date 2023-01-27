#include <iostream>
#include <memory>

using namespace std;

void test_sizeof_smartPointer()
{
    unique_ptr<char> upc(new char);
    shared_ptr<char> spc(new char);
    weak_ptr<char> wpc(spc);

    cout << sizeof(upc) << endl;    // 8
    cout << sizeof(spc) << endl;    // 16
    cout << sizeof(wpc) << endl;    // 16

}

int main()
{
    test_sizeof_smartPointer();

    return 0;
}


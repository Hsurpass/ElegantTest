#include <iostream>

using namespace std;

void test_support_c11()
{
    cout << __cplusplus << endl;    // 201402
}

int main()
{
    test_support_c11();

    return 0;
}
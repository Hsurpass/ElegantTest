#include <stdio.h>
#include <sys/select.h>
#include <iostream>

using namespace std;

void select01()
{
    fd_set rset, allset;
    // cout << sizeof(__fd_mask) << endl;

    // FD_SET();
    // select();
    // FD_ISSET();
}

int main()
{
    select01();

    return 0;
}
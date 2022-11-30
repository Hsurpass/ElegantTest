#include <iostream>
#include <vector>
#include <functional>

using namespace std;

auto lazy_sum()
{
    int sum = 0;
    return [=](int val) mutable{
        sum += val;
        return sum;
    };

}

void testClosure01()
{
    auto sum = lazy_sum();
    cout << sum(0) << endl;
    cout << sum(1) << endl;
    cout << sum(2) << endl;
    cout << sum(3) << endl;
    cout << sum(4) << endl;

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", sum(i));
        // cout << sum(i) << " ";
    }
    cout << endl;
}

auto sum_(int *arr, int n)
{
    int sum = 0;
    return [=]() mutable {
        for(int i = 0; i < n; i++)
        {
            sum += arr[i];
        }
        return sum;
    };
}

void testClosure02()
{
    int arr[5] = {0,1,2,3,4};
    auto sum = sum_(arr, 5);
    cout << sum() << endl;
}

typedef int (*pf)();
typedef function<int()> PF;
std::vector<PF> funcArr()
{
    vector<PF> vpf;
    for(int i = 0; i < 3; i++)
    {
        PF f = [i]()->int {
            return i*i;
        };
        vpf.push_back(f);
    }
    
    return vpf;
}

void testClosure03()
{
    vector<PF> v = funcArr();
    for (auto &f:v)
    {
        cout << f() << endl;
    }
    
}

int main()
{
    // testClosure01();
    // testClosure02();
    testClosure03();

    return 0;
}
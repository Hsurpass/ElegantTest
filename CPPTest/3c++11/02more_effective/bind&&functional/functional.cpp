#include <iostream>
#include <functional>
#include <map>
#include <algorithm>

using namespace std;

// functional可以适配 普通函数 函数指针 lambda 仿函数

// 普通函数
int add(int i, int j)
{
    return i + j;
}

// lambda
auto _minus = [](int i, int j) {
    return i - j;
};

// 仿函数 functor
class mul
{
public:
    int operator()(int i, int j)
    {
        return i * j;
    }
};

// typedef int(*_MINUS)(int,int);
typedef std::function<int(int, int)> FUNC;

void test_functional_map()
{
    map<string, FUNC> math; // map排序了 * + - /
    math.insert(make_pair("+", add));
    math.insert(make_pair("-", _minus));
    math.insert(make_pair("*", mul()));
    math.insert(make_pair("/", [](int i, int j) { return i / j; }));

    cout << math.begin()->second(11, 10) << endl;   // 110
    
    for (map<string, FUNC>::const_iterator itr = math.begin(); itr != math.end(); ++itr)
    {
        cout << itr->second(10, 2) << endl; // 20 12 8 5
    }

    cout << "-----------------------" << endl;

    for (auto &p:math)
    {
        cout << p.second(2, 1) << endl; // 2 1 1 2
    }
}

void functional_match_func_funcPointer_functor_lambda()
{
    // 普通函数
    auto op = function<int(int, int)>(add);
    cout << op(1, 2) << endl; // 3

    // func pointer
    typedef int (*_MINUS)(int, int);
    _MINUS m = _minus;
    op = function<int(int, int)>(m);
    cout << op(10, 3) << endl; // 7

    // functor
    op = mul();
    cout << op(3, 5) << endl; // 15

    // lambda
    op = function<int(int, int)>([](int x, int j) {
        return x / j;
    });
    cout << op(10, 5) << endl; // 2
}

void selectsort(int *arr, int n, function<bool(int, int)> comp)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1;j < n; j++)
        {
//            if(arr[i] < arr[j])
            if(comp(arr[i],arr[j]))
            {
                arr[i] ^= arr[j];
                arr[j] ^= arr[i];
                arr[i] ^= arr[j];
            }
        }
    }
}

void selectsort_with_functional()
{
    int arr[] = {1,3,5,7,9,2,4,6,8,10};

    for_each(arr, arr+10, [](int &i){
        cout << i <<" ";
    });
    cout << endl;
//    selectsort(arr,sizeof(arr)/sizeof(*arr));
    selectsort(arr, sizeof(arr)/sizeof(*arr), [](int i, int j){return i > j;} );
    for_each(arr, arr+10, [](int& i){
        cout << i <<" ";
    });
    cout << endl;

}

int main()
{
    // functional_match_func_funcPointer_functor_lambda();
    // test_functional_map();
    selectsort_with_functional();

    return 0;
}

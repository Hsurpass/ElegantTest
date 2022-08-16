#include <iostream>

using namespace std;

template <typename T>
void printOneDimensionArray(T *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T, int len>
void printTwoDimensionArray(T (*arr)[len], int row)
// void printTwoDimensionArray(T arr[][len], int row)
{
    cout << "row:" << row << ", " << "len:" << len << endl;
    
    //# 1
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < len; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    //# 2
    // for(auto p = arr; p != arr + row; ++p)
    // {
    //     for(auto q = *p; q != *p + len; ++q)
    //     {
    //         cout << *q << " ";
    //     }
    //     cout << endl;
    // }

}

template <typename T, int x, int y>
void printTwoDimensionArrayUseAutoFor(T (&arr)[x][y])   //使用auto for传参必须使用这种形式 (T (&arr)[m][n])
// void printTwoDimensionArrayUseAutoFor(int (&arr)[3][4])
{
    //# 1
    for (const auto &row : arr)
    {
        cout << row << endl;
        for(auto col :row)
        {
            cout << col << " ";
        }
        cout << endl;
    }

    // # 2
    // for (auto p = arr; p != arr + x; ++p)
    // {
    //     for(auto q = *p; q != *p + y; ++q)
    //     {
    //         cout << *q << " ";
    //     }
    //     cout << endl;
    // }

    // # 3 使用std::begin() std::end()
    // for(auto p = begin(arr); p != end(arr); ++p)
    // {
    //     for(auto q = begin(*p); q != end(*p); ++q)
    //     {
    //         cout << *q << " ";
    //     }
    //     cout << endl;
    // }
}

template <typename T, int col, int size>
void printThreeDimensionArray(T (*arr)[col][size], int row)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for (int m = 0; m < size; m++)
            {
                cout << arr[i][j][m] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}



string sa[10];
int ia[10];

// 多维数组
int main04()
{
    int ia[3][4] = {{0}, {4}, {8}};
    printTwoDimensionArray<int, 4>(ia, 3);

    int ia1[3][4] = {1,3,5,7};
    printTwoDimensionArray<int, 4>(ia1, 3);

    int (&row)[4] = ia[1];
    cout << row[0] << endl;

    int *p = ia[1];
    cout << p[0] << endl;

    printTwoDimensionArrayUseAutoFor<int, 3, 4>(ia);
    // for (const auto &row : ia)  // 第一个for遍历ia的所有元素，这些元素是大小为4的数组，因此row的类型就应该是含有4个整数的的数组的引用 (int[4] &)
    // {
    //     for (auto col: row)     // 第二个for遍历四元素数组中的某一个，因此col的类型是整数(int)
    //     {
    //         cout << col << " ";
    //     }
    //     cout << endl;
    // }

    // typedef int[4] int_array;    // error
    // #define int_array int[4]     // error
    using int_array = int[4];
    for(int_array *p = ia; p != ia + 3; ++p )
    {
        for(int *q = *p; q != *p + 4; ++q)
        {
            cout << *q << " ";
        }
        cout << endl;
    }
    return 0;
}

int main03()
{
    int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *beg = std::begin(ia);
    int *end = std::end(ia);

    cout << end - beg << endl;
    for (; beg != end; ++beg)
    {
        cout << *beg << " ";
    }
    cout << endl;

    return 0;
}

int main02()
{
    int ia[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto ia2(ia); // ia2会推断出是首元素的地址
    cout << ia2 << endl;

    decltype(ia) ia3 = {11, 22, 33, 44, 55, 66}; // int [10] 会推断出是10个元素的数组
    printOneDimensionArray(ia3, 10);
    ia3[6] = 77;
    printOneDimensionArray(ia3, 10);

    return 0;
}

int main01()
{
    int a1[] = {1, 2, 3}; // {1,2,3}
    printOneDimensionArray(a1, sizeof(a1) / sizeof(a1[0]));

    int a2[5] = {1, 2, 3};
    printOneDimensionArray(a2, 5); //{1,2,3,0,0}

    // int a3[2] = {7,8,9}; //error
    // printArray(a3, 2);

    string a4[3] = {"hi", "hello"};
    printOneDimensionArray(a4, 3); // {"hi", "hello", ""}

    // int a5[4 * 7 - 14];
    int a5[4 * 7 - 14] = {};
    printOneDimensionArray(a5, 14);

    string a6[10];
    int a7[10];

    printOneDimensionArray(sa, 10);
    printOneDimensionArray(ia, 10);
    printOneDimensionArray(a6, 10);
    printOneDimensionArray(a7, 10);

    return 0;
}

void test_array_init_value()
{
    // int arr[10] = { 1, 2, 3, 4, 5};  // 其他值初始化为0
    // int arr[10];    // 随机值
    // int arr[10] = {10}; // 其他值初始化为0
    int arr[10] = {};   // 全部初始化为0
    printOneDimensionArray(arr, 10);
}

int main()
{
    test_array_init_value();

    return 0;
}
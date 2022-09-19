#include <iostream>
#include <vector>
#include <array>
using namespace std;
/*
1  2  8  9
2  4  9  12
4  7  10 13
6  8  11 15
*/


int main()
{
   vector<vector<int>> vvi= {{1,2,8,9},
                             {2,4,9,12},
                             {4,7,10,13},
                             {6,8,11,15}
                            };
//      int *p = (int*)vvi[0];
   cout << "&vvi:" << &vvi << endl;

   printf("vvi[0]:%p\n", vvi[0]);
   cout << "&vi[0][0]:" << &vvi[0][0];



}
void findsorteddoublematrix_vector02(int* matrix,int rows,int columns,int finddata,vector<pair<int,int>> &index)
{
    int i = 0;int j = columns-1;

    if(matrix && rows > 0 && columns > 0)
    {
        while(i < rows && j >= 0)
        {
            if(matrix[i*columns +j] == finddata)
            {
                index.push_back(make_pair(i,j));
//                break;
                i++;
                j--;
            }
            else if(matrix[i*columns +j] > finddata)
            {
                j--;
            }
            else {
                i++;
            }
        }
    }
}
int main03()
{
   int array[4][4] = {1,2,8,9,
                      2,4,9,12,
                      4,7,10,13,
                      6,8,11,15
                            };
    cout << "&array:" << &array <<  endl;
    cout << "array:" << array << endl;
    cout << "array[0]:" << array[0] << endl;
    cout << "&array[0][0]:" << &array[0][0] << endl;
    vector<pair<int,int>> index;
    findsorteddoublematrix_array((int*)array,4,4,8,index);
    cout <<index.size() << endl;
    if(index.empty())
    {
        cout << "none" << endl;
    }
    else {
        while(!index.empty())
        {
            cout << "(" << index.back().first << "," << index.back().second << ")" << endl;
            index.pop_back();
        }
    }
#if 0
//   int (*p)[4] = array;
   int *q = (int*)array;
   int rows = 4;
   int columns = 4;
   for(int i =0;i < rows;++i)
   {
       for(int j=0;j < columns;++j)
       {
//           cout << *(*(array+i)+j) << " ";
//           cout << *(*(p+i)+j) << " ";
//           cout << *(q+(i*columns)+j) << " ";
//           cout << q[i*columns+j] << " ";
       }
       cout << endl;
   }
#endif
    return 0;
}
int main02()
{
//    array<array<int>,4> v;
    /*= {{1,2,8,9},
                             {2,4,9,12},
                             {4,7,10,13},
                             {6,8,11,15}

                                }*/
        #if 0
    for(int i =0;i < v.size();++i)
    {
        for(int j = 0;j < v[i].size();++j)
        {
            cout << v[i][j] << "  ";
        }
        cout << endl;
    }
    cout<< "----------------------" << endl;
    for(int i = 0;i < v.size();++i)
    {
        int colunms = v[i].size();
        for(int j = 0;j < v[i].size();++j)
        {
//            cout << v[i*colunms + j] << " ";
//            cout << v.at(i*colunms + j) << " ";
        }
        cout << endl;
    }
#endif
    return 0;
}
bool findsorteddoublematrix01(vector<vector<int>> &vvi,int finddata,pair<int,int> &index)
{
    //从右上角开始找
    index = make_pair(999999,999999);
    int i;int m = 0;
    int j;int n = vvi[1].size();
    for(int i =m;i < vvi.size();++i)
    {
        for(j = n;j >=0;--j)
        {
            if(vvi[i][j] == finddata)
            {
                index = make_pair(i,j);
                return true;
            }
            else if(vvi[i][j] > finddata)
            {
                continue;
            }
            else
            {
                n = j;
                break;
            }
        }
    }
    return false;
}

#if 0
int main01()
{
    vector<vector<int>> v = {{1,2,8,9},
                             {2,4,9,12},
                             {4,7,10,13},
                             {6,8,11,15}
                            };
    for(int i =0;i < v.size();++i)
    {
        for(int j = 0;j < v[i].size();++j)
        {
            cout << v[i][j] << "  ";
        }
        cout << endl;
    }
    cout<< "----------------------" << endl;

    pair<int,int> index;
    bool b = findsorteddoublematrix(v,6,index);
    cout << "bool:" << b << "index:(" << index.first << "," << index.second << ")" <<endl;

    cout<< "----------------------" << endl;
    vector<vector<int>>::iterator vvitr = v.begin();
    vector<int>::iterator vitr;
    vector<int> vi;
//    itr += 3 * 4 + 3;

   for(vvitr = v.begin();vvitr != v.end();++vvitr)
   {
       vi = *vvitr;
       for(vitr = vi.begin();vitr != vi.end();++vitr)
       {
            cout << *vitr << "  ";
       }
       cout << endl;
   }

    return 0;
}

#endif

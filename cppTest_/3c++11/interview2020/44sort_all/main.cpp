#include <iostream>
#include <vector>
using namespace std;

void bubblesort(vector<int> &v)
{
    int size = v.size();
    if(size == 0)
    {
        cout << "size is empty" << endl;
        return;
    }
    int i=0;int j = 0;bool flag = false;
    for(i = 0;i < size-1;++i)
    {
        flag = false;
        for(j = 0;j < size-1-i;++j)
        {
            if(v[j] > v[j+1])
            {
                int tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
//                v[i] ^= v[j];
//                v[j] ^= v[i];
//                v[i] ^= v[j];
                flag = true;
            }
        }
        if(!flag)
        {
            break;
        }
    }
}
void selectsort(vector<int> &v)
{
    int i=0;int j = 0;
    int size = v.size();
    if(size == 0)
    {
        return;
    }
    int k = 0;
    for(i = 0;i < size-1;++i)
    {
        k = i;
        for(j = k+1;j < size;++j)
        {
            if(v[k] > v[j])
            {
                k = j;
            }
//            if(v[i] > v[j])
//            {
//                v[i] ^= v[j];
//                v[j] ^= v[i];
//                v[i] ^= v[j];
//            }
        }
        if(k != i)
        {
            v[i] ^= v[k];
            v[k] ^= v[i];
            v[i] ^= v[k];
        }
    }

}
void printvector(vector<int> v)
{
    for(vector<int>::iterator itr = v.begin();itr != v.end();++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}
void quicksort(int *arr,int low,int high)
{
    if(low < high) //low 和high相等没必要比
    {
        int l = low;int h = high;
        int pivot = arr[l];
        while (l < h) //相等是枢轴赋值的条件
        {
            while(arr[h] >= pivot && l < h)   //从右边开始比较，大而移动，小而赋值
            {
                h--;
            }
            arr[l] = arr[h];
            while (arr[l] <= pivot && l < h)    //小而移动，大而赋值
            {
                l++;
            }
            arr[h] = arr[l];
        }

        arr[l] = pivot;
        quicksort(arr,low,l-1);
        quicksort(arr,l+1,high);
    }

}
int binarysearch_iterator(int *arr,int low,int high,int finddata)
{
    while (low <= high)
    {
        int mid = (low + high)/2;
        if(arr[mid] == finddata)
        {
            return mid;
        }
        else if(arr[mid] > finddata )
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}
int binarysearch_recursive(int *arr,int low,int high,int finddata)
{
    if(low <= high)
    {
        int mid = (low + high) /2;
        if(arr[mid] == finddata)
        {
            return mid;
        }
        else if(arr[mid] > finddata)
        {
            return binarysearch_recursive(arr,low,mid -1,finddata);
        }
        else {
            return binarysearch_recursive(arr,mid + 1,high,finddata);
        }
    }
    else {
        return -1;
    }
}
void printarr(int *arr,int n)
{
    for(int i = 0;i < n;++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
class A
{
public:
    A(int a):m_a(a) {}
    void print()
    {
        cout << "A::print" << endl;
    }
private:
    int m_a;
};
struct B{
    int a;
    int b;
    int c;
};

int main()
{
//    A* p = NULL;
//    p->print();
//    char *p = "abc";
//    cout << sizeof(*p) << endl;
    B *b = NULL;
    int d = ()
}
int main02()
{
//    int arr[] = {10,1,3,5,7,9,2,4,6,8,10};
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
//    printarr(arr,sizeof(arr)/sizeof(int));
//    quicksort(arr,0,(sizeof(arr)/sizeof(int) - 1));
//    printarr(arr,sizeof(arr)/sizeof(int));

    int index = -1;
//    index = binarysearch_iterator(arr,0,(sizeof(arr)/sizeof(int)-1),5);
//    index = binarysearch_recursive(arr,0,(sizeof(arr)/sizeof(int)-1),9);
    cout << "index: " << index << endl;

    return 0;
}
int main01()
{
    vector<int> vi = {100,1,3,5,7,9,0,2,4,6,8,10};
    printvector(vi);
    cout << "------------------" << endl;
//    bubblesort(vi);
    selectsort(vi);
    printvector(vi);

    return 0;
}

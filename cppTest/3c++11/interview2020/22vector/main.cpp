#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
using namespace std;
class A
{
public:
    A()
    {
        cout<<"A()"<<this<<endl;
    }
    A(int i):_data(i)
    {
        cout<<"A(int i):_data(i),i:" << i <<" "<<this<<endl;
    }
    A(const A & other)
    {
        cout<<"A(const A & other),other._data:"<<other._data << " " << this<<" from "<<&other<<endl;
        this->_data = other._data;
    }
    A& operator=(const A & other)
    {
        cout<<"A& operator=(const A & other),other._data:" << other._data << " " <<this<<" from "<<&other<<endl;
        if(this != &other)
        {
            this->_data = other._data;
        }
        return *this;
    }
    ~A()
    {
        cout<<"~A()"<<this<<endl;
    }
    int dis()const
    {
        return _data;
    }
    //private:
    //    int _data;
//    string _data;
    int _data;
};

int main()
{
//    vector<A> *pvsp = new vector<A>;
    shared_ptr<vector<A>> pvsp(new vector<A>);
    return 0;
}
int main14()
{
    vector<shared_ptr<A>> vsp;
    vsp.reserve(10);
    cout << "---------------------"<<endl;
    cout << vsp.size() << endl;
    cout << vsp.capacity() << endl;
    cout << "---------------------"<<endl;
    for(int i =0;i < 10;++i)
    {
//        vsp.emplace_back(new A(i));
//        vsp.emplace_back(make_shared<A>(i));
        vsp.push_back(make_shared<A>(i));
    }
    for(vector<shared_ptr<A>>::iterator itr = vsp.begin();itr != vsp.end();++itr)
    {
        cout << (*itr)->dis() << endl;
    }
    cout << "---------------------"<<endl;
    cout << vsp.size() << endl;
    cout << vsp.capacity() << endl;
    cout << "---------------------"<<endl;

}
#if 0
int main13()
{
    vector<A> va;
    va.reserve(10);
//    va.emplace(va.begin(),"1");
//    va.emplace(va.begin(),"2");
//    va.emplace(va.begin(),"3");
//    va.emplace_back("4");
//    va.emplace_back("5");
//    va.emplace_back("6");
//    A a4("4");
//    va.emplace_back(a4);
    va.emplace(va.begin(),A("1"));
    va.emplace(va.begin(),A("2"));
    va.emplace(va.begin(),A("3"));

    cout << "---------------------"<<endl;
    cout << va.size() << endl;
    cout << va.capacity() << endl;
    cout << "---------------------"<<endl;
    return 0;
}

int main12()
{
    vector<vector<int> > arr(5,vector<int>(5,0));
    cout << arr.size() << endl;
    cout << arr[0].size() << endl;
    cout << arr[1].size() << endl;
    cout << arr[2].size() << endl;
    cout << arr[3].size() << endl;
    cout << arr[4].size() << endl;
}

int main11()
{
//    vector<A> va(5);
    vector<A> va;
    A a("2");
     va.insert(va.begin(),a);
//    cout << va.at(0).dis() << endl;
}

int main10()
{
    vector<int> vi;
    int data[10] = {1,3,5,7,9,2,4,6,8,10};
    vi.assign(data,data+10);
    vector<int>::iterator itr = vi.begin();
    vi.erase(vi.begin(),vi.end() - 1);
    //    itr = vi.insert(itr,100);
    //    cout << *++itr << endl;
    //    itr = vi.erase(itr);
    //    cout << *++itr << endl;
    //    vi.shrink_to_fit();
    //    cout << vi.size() << endl;
    //    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
//    for(;itr != vi.end();)
//    {
//        if(*itr%2==0)
//            itr = vi.erase(itr);
//        else
//        {
//            cout<<*itr<<endl;
//            ++itr;
//        }
//    }
    /*
    for(;itr != vi.end();)
    {
        if(*itr % 2)
        {
            itr = vi.insert(itr,100);
            itr += 2;
        }
        else {
            ++itr;
        }
    }
    for(auto &v:vi)
    {
        cout << v << " ";
    }
    cout << endl; */
    cout << "---------------------"<<endl;
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
    return 0;

}

int main09()
{
    //    vector<A*> vap;
    //    vap.push_back(new A);
    vector<shared_ptr<A>> vap;
    vap.push_back(shared_ptr<A>(new A));

    return 0;
}

int main08()
{
    //    A a[5];
    //    A aa[5] = {A("1")};

    vector<A> vi = {A("1"),A("2"),A("3"),A("4"),A("5")};
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
    vi.resize(10);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
    vi.resize(8);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
    vi.shrink_to_fit();
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
    vi.clear();
    //    vi.shrink_to_fit();
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    cout << "---------------------"<<endl;
}

int main07()
{
    vector<int> vi;
    vi.push_back(1);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    vi.push_back(2);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    vi.push_back(3);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    vi.push_back(4);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    vi.push_back(5);
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
}

int main06()
{
    vector<int> vi = {1,2,3,4,5};
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;      //5

    vi.resize(10);
    vi.shrink_to_fit();
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    vi.resize(8);
    //    vi.shrink_to_fit();
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    vi.shrink_to_fit();
    cout << vi.size() << endl;
    cout << vi.capacity() << endl;
    return 0;
}

int main05()
{
    A *p1 = new A("1");
    A *p2 = new A("2");
    A *p3 = new A("3");
    A *p4 = new A("4");
    A *p5 = new A("5");
    cout << "===============" << endl;
    vector<A*> vp;
    vp.push_back(p1);
    A *ptmp = vp.front();
    cout << ptmp->dis() << endl;
    return 0;
}

int main04()
{
    vector<string> v;
    string a1("1");
    string a2("2");
    string a3("3");
    string a4("4");
    string a5("5");
    v.push_back(a1);
    v.push_back(a2);
    v.push_back(a3);
    v.push_back(a4);
    v.push_back(a5);
    cout << v.capacity() << endl;
    cout << v.size() << endl;
    cout << "==================" << endl;
    vector<string>::iterator itr;
    itr = std::find(v.begin(),v.end(),"2");
    if(itr != v.end())
    {
        cout << *itr << endl;
        itr = v.erase(itr);
        cout << *itr << endl;

    }
    else {
        cout << "find none" << endl;
    }
    return 0;
}
#endif
#if 0
int main03()
{
    vector<A> v;
    A a1("1");
    A a2("2");
    A a3("3");
    A a4("4");
    A a5("5");
    v.push_back(a1);
    v.push_back(a2);
    v.push_back(a3);
    v.push_back(a4);
    v.push_back(a5);

    //    vector<A> v = {A(1),A(2),A(3),A(4),A(5)};
    A &tmp = a2;
    cout << v.capacity() << endl;
    cout << v.size() << endl;
    cout << "==================" << endl;
    vector<A>::iterator itr;
    itr = std::find(v.begin(),v.end(),tmp);
    if(itr != v.end())
    {
        cout << itr->dis() << endl;
        itr = v.erase(itr);
        cout << itr->dis() << endl;

    }
    else {
        cout << "find none" << endl;
    }
    return 0;
}

int main02()
{
    //    vector<A> v = {A(1),A(2)};
    vector<A> v;
    //    v.resize(5);
    //    vector<A> v2 = {A(1),A(2),A(3),A(4),A(5)};
    //    v.insert(v.end() - 1,A(3));
    //    v.reserve(10);
    v.assign(5,A(10));
    //    v.assign(v2.begin(),v2.end());
    //    v.swap(v2);
    cout << v.capacity() << endl;
    cout << v.size() << endl;
    //    v.shrink_to_fit();
    cout << "==================" << endl;
    v.resize(10);
    cout << v.capacity() << endl;
    cout << v.size() << endl;
    cout << "==================" << endl;
    v.clear();
    cout << v.capacity() << endl;
    cout << v.size() << endl;
    for(auto &i:v)
    {
        cout << i.dis() << endl;
    }
    cout << "==================" << endl;
}
int main01()
{
    //    vector<A> v;
    //    vector<A> v(5);
    //    vector<A> v(5,A(2));
    vector<A>  v;
    v.reserve(10);
    //    v.resize(10);
    cout<< "-----------------" <<endl;
    //    v.resize(5);
    //    v.resize(20);
    v.push_back(A(1));
    v.push_back(A(2));
    v.push_back(A(3));
    v.push_back(A(4));
    //    v.insert(v.begin()+1,A(100));
    cout<< "-----------------" <<endl;
    vector<A> v1;
    //    vector<A> v1(v);
    //    v1 = v;
    //    v1.reserve(10);
    //    v1.resize(10);
    //    v1 = v;
    //    v1.assign(v.begin(),v.end());
    //    v1.emplace(v.begin(),v.end());
    //    v1.emplace_back(v.begin(),v.end());
    //    v.pop_back();
    //    v.erase(v.begin());
    //    v.erase(v.begin()+2,v.end() -1);

    cout << v.size() << endl;
    cout<< "-----------------" <<endl;

    return 0;
}
\
#endif

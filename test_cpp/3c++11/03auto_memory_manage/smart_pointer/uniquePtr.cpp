#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Copy
{
public:
    Copy(int i = 10) : _i(new int(i))
    {
        cout << "Copy(int i)" << this << endl;
    }
    Copy(const Copy &another) : _i(new int(*another._i))
    {
        cout << " Copy(const Copy & another)" << endl;
    }
    Copy& operator=(const Copy& another)
    {
        cout << "Copy& operator=(const Copy& another)" << endl;

        if (&another != this)
        {
            delete _i;
            _i = new int(*(another._i));
        }

        return *this;
    }
    ~Copy()
    {
        cout << "~Copy()" << this << endl;
    }
    void dis()
    {
        cout << *_i << endl;
    }

    int *_i;
};

void test_move_uniquePtr_to_sharedPtr()
{
    unique_ptr<Copy> uc(new Copy(123));

    shared_ptr<Copy> sc = std::move(uc);    // shared_ptr(unique_ptr<_Yp, _Del>&& __r)
    cout << sc.use_count() << endl; // 1
    sc->dis();  // 123
    // uc->dis();  // core dump
    cout << (uc ? true : false) << endl;// 0
    cout << (uc == nullptr) << endl;    // 1

}

void test_vector_pushback_unique_ptr()
{
    vector<unique_ptr<Copy> > vc;

    unique_ptr<Copy> uc1(new Copy(5));
    unique_ptr<Copy> uc2(new Copy(6));
    unique_ptr<Copy> uc3(new Copy(7));
    unique_ptr<Copy> uc4(new Copy(8));
    unique_ptr<Copy> uc5(new Copy(9));
    cout << "------------------------------" << endl;
    // error copy constructor = delete
    // vc.push_back(uc1);
    // vc.push_back(uc2);
    // vc.push_back(uc3);
    // vc.push_back(uc4);
    // error copy constructor = delete
    // vc.emplace_back(uc1);
    // vc.emplace_back(uc2);
    // vc.emplace_back(uc3);
    // vc.emplace_back(uc4);

    // correct 传入右值引用 调用 move constructor copy constructor
    // vc.push_back(std::move(uc1) );
    // vc.push_back(std::move(uc2) );
    // vc.push_back(std::move(uc3) );
    // vc.push_back(std::move(uc4) );
    // vc.push_back(std::move(uc5));

    vc.emplace_back(std::move(uc1) );
    cout << "size:" << vc.size() << ", capacity:" << vc.capacity() << endl;   // 1 2

    vc.emplace_back(std::move(uc2) );
    cout << "size:" << vc.size() << ", capacity:" << vc.capacity() << endl;   // 2 2

    vc.emplace_back(std::move(uc3) );
    cout << "size:" << vc.size() << ", capacity:" << vc.capacity() << endl;   // 3 4

    vc.emplace_back(std::move(uc4) );
    cout << "size:" << vc.size() << ", capacity:" << vc.capacity() << endl;   // 4 4

    vc.emplace_back(new Copy(9));
    cout << "size:" << vc.size() << ", capacity:" << vc.capacity() << endl;   // 5 8

    cout << (uc1 ? "uc1 is not empty": "uc1 is empty") << endl;
    cout << (uc2 ? "uc2 is not empty": "uc2 is empty") << endl;
    cout << (uc3 ? "uc3 is not empty": "uc3 is empty") << endl;
    cout << (uc4 ? "uc4 is not empty": "uc4 is empty") << endl;
    cout << (uc5 ? "uc5 is not empty": "uc5 is empty") << endl;
#if 0
    vc.push_back(make_unique<Copy>(1));
    vc.push_back(make_unique<Copy>(2));
    vc.push_back(make_unique<Copy>(3));
    vc.push_back(make_unique<Copy>(4));
#endif

    cout << "size:" << vc.size() << ", capacity:" << vc.capacity() << endl;
}

void test_make_unique()
{
    unique_ptr<Copy> p1 = make_unique<Copy>();
    
}

void test_unique_ptr_std_move()
{
    unique_ptr<Copy> up(new Copy(100));
    cout << *up->_i << endl;    // 100

    unique_ptr<Copy> up1;
    up1 = std::move(up);
    cout << *up1->_i << endl;   // 100

    cout << (up ? true : false) << endl;    // 0
    cout << *up->_i << endl;    // core dump    所有权被转移了
}

void test_uniquePtr_newArray()
{
#if 1
    int arr[10]= {};
    typedef int(*INT)[2];
    INT a = (int(*)[2])arr;
#endif

    unique_ptr<int[]> up(new int[10]{1, 3, 5});
    for (int i = 0; i < 10; i++)
    {
        cout << up[i] << " ";  // 1 3 5
    }
    cout << endl;
    cout << "--------------------------" << endl;
    
    unique_ptr<Copy[]> upc(new Copy[5]);
    for (int i = 0; i < 5; i++)
    {
        upc[i].dis();
    }
}

void test_unique_ptr_reset()
{
    {
        unique_ptr<Copy> up(new Copy(100)); // Copy(int i)0x7ffff0dcbe70
        cout << *up->_i << endl;    // 100
        up.reset(new Copy(999));    // 释放旧资源，托管新资源   Copy(int i)0x7ffff0dcc2c0 ~Copy()0x7ffff0dcbe70
        cout << *up->_i << endl;    // 999 

        cout << "=====================" << endl;
    }   // ~Copy()0x7ffff0dcc2c0
    cout << "-----------------------" << endl;
}

void test_unique_ptr_release()
{
    {
        unique_ptr<Copy> up(new Copy(100));
        if (up)
        {
            cout << "up has resource" << endl;
            cout << "resource this: " << up.get() << endl;
        }
        else
        {
            cout << "up has no resource" << endl;
        }

        cout << "------------------" << endl;
        Copy *p = up.release(); // 放弃托管，但不会释放资源
        if (up)
        {
            cout << "up has resource" << endl;
            cout << "resource this: " << up.get() << endl;
        }
        else
        {
            cout << "up has no resource" << endl;
        }

        cout << *p->_i << endl;     // 100
        // cout << *up->_i << endl;    // core dump    up已经放弃托管
        delete p;

        cout << "=====================" << endl;
    }
    cout << "-----------------------" << endl;
}

void test_unique_ptr_get()
{
    unique_ptr<Copy> cp(new Copy(100));

    Copy* p = cp.get();
    cout << *(p->_i) << endl;
    cout << *(cp->_i) << endl;
    cout << p->_i << endl;
    cout << cp->_i << endl;

    cout << (cp ? true : false) << endl;

}

void func(unique_ptr<Copy> &tmp)
{
    cout << *tmp->_i << endl;
}

void test_unique_ptr_passByReference()
{
    unique_ptr<Copy> ui(new Copy(100));

    func(ui);

    cout << *ui->_i << endl;
}

void test_unique_ptr_copyAndAssign()
{
    // Copy *p = new Copy(100);
    unique_ptr<Copy> ui(new Copy(100));
    // unique_ptr<int> uicopy = ui;    // copy constructor =delete
    // unique_ptr<Copy> uiassign;
    // uiassign = ui;    // operator=()  =delete

}

void test_unique_ptr_destructor()
{
    Copy *p = new Copy(100);    // Copy(int i)
    {
        unique_ptr<Copy> up(p);
        cout << *(up->_i) << endl; // 100
        cout << *(p->_i) << endl;  // 100
    }
    // cout << "p:" << *p << endl;
    // cout << *(p->_i) << endl;   // (core dumped)
    unique_ptr<Copy> up1(p);
    // cout << *(up1->_i) << endl; // (core dumped)
}

int main()
{
#if 0
    // delete free NULL不会崩
    int* p = NULL;
    delete p;
    free(p);
#endif
#if 0
    unique_ptr<int> ui;  // 未初始化
    cout << *ui << endl; // Segmentation fault (core dumped)
#endif
    // test_unique_ptr_destructor();
    // test_unique_ptr_copyAndAssign();
    // test_unique_ptr_passByReference();
    // test_unique_ptr_get();
    // test_unique_ptr_release();
    // test_unique_ptr_reset();
    // test_uniquePtr_newArray();
    // test_unique_ptr_std_move();

    // test_vector_pushback_unique_ptr();
    test_move_uniquePtr_to_sharedPtr();

}

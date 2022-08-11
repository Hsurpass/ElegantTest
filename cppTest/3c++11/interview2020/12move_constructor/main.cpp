#include <iostream>

using namespace std;

class Move
{
public:
    Move(int i):m_i(new int(i)) {
        cout << "Move():m_i " << this << endl;
    }
    ~Move()
    {
        cout << "~Move() " << this << endl;
        if(m_i != nullptr)
        {
            delete m_i;
        }
    }
    Move(const Move& another)
    {
        m_i = new int(*(another.m_i));
        cout << "Move(const Move& another) " << this << " copy from " << &another <<endl;
    }

    Move(Move &&another)
    {
        cout << "Move(Move &&another) " << this << " move from " << &another << endl;
        m_i = another.m_i;
        another.m_i = nullptr;
    }

    Move& operator=(const Move& another)
    {
        cout << "Move& operator=(const Move& another)" << endl;
        if(this != &another)
        {
            delete m_i;
            m_i = new int(*another.m_i);
        }
        return *this;
    }
    Move& operator =(Move &&another)
    {
        cout << "Move& operator =(Move &&another)" << endl;
        if(this != &another)
        {
            delete m_i;
            m_i = another.m_i;
            another.m_i = nullptr;
        }
        return *this;
    }
private:
    int *m_i;
};

Move getmove()
{
    return Move(20);
}
int main()
{
//    Move m(100);
//    Move n(m);
//    Move ma = getmove();
//    Move &&_ma = getmove();
    Move &&ma = std::move(getmove());

    return 0;
}

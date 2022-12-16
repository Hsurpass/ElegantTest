// g++ less_than_comparable.cpp

#include <boost/operators.hpp>
#include <iostream>


/*
less_than_comparable: 只需要实现operator<() const, 则>, <=, >=,就会自动实现。
equality_comparable：只需要实现operator==() const, 则 != 就会自动实现

note: 如果使用成员函数重载，则应该是const成员函数。
*/
class A : public boost::less_than_comparable<A>, public boost::equality_comparable<A>
{
public:
    A(int a) : m_a(a) {}

    friend bool operator<(const A& one, const A& other)
    {
        std::cout << "friend bool operator<(const A& one, const A& other)" << std::endl;
        return one.m_a < other.m_a;
    }

    friend bool operator==(const A& one, const A& other)
    {
        std::cout << "friend operator==(const A& one, const A& other)" << std::endl;
        return one.m_a == other.m_a;
    }

    // bool operator<(const A& other) const
    // {
    //     std::cout << "bool operator<(const A& other)" << std::endl;
    //     return this->m_a < other.m_a;
    // }

    // bool operator==(const A& other) const
    // {
    //     std::cout << "bool operator==(const A& other)" << std::endl;
    //     return this->m_a == other.m_a;
    // }

private:
    int m_a;
};

// 要传const reference
// bool operator<(const A& one, const A& other)
// {
//     std::cout << "bool operator<(const A& one, const A& other)" << std::endl;
//     return one.m_a < other.m_a;
// }

// bool operator==(const A& one, const A& other)
// {
//     std::cout << "operator==(const A& one, const A& other)" << std::endl;
//     return one.m_a == other.m_a;
// }

int main()
{
    A a1(10);
    A a2(20);
    A a3(30);
    A a4(10);
    
    std::cout << "a1 < a2: " << (a1 < a2) << std::endl;
    std::cout << "a1 > a2: " << (a1 > a2) << std::endl;
    std::cout << "a1 <= a2: " << (a1 <= a2) << std::endl;
    std::cout << "a1 >= a2: " << (a1 >= a2) << std::endl;
    std::cout << "a1 <= a4: " << (a1 <= a4) << std::endl;
    std::cout << "a1 >= a4: " << (a1 >= a4) << std::endl;

    std::cout << "a3 == a2: " << (a3 == a2) << std::endl;
    std::cout << "a3 != a2: " << (a3 != a2) << std::endl;

    return 0;
}
// g++ less_than_comparable.cpp

#include <boost/operators.hpp>
#include <iostream>

class A : public boost::less_than_comparable<A>, public boost::equality_comparable<A>
{
public:
    A(int a) : m_a(a) {}
    // friend bool operator<(const A& one, const A& other)
    // {
    //     std::cout << "bool operator<(A& other)" << std::endl;
    //     return one.m_a < other.m_a;
    // }

    // bool operator>(A& other)
    // {
    //     std::cout << "bool operator>(A& other)" << std::endl;
    //     return other < *this;
    // }
    // bool operator==(A& other)
    // {
    //     std::cout << "bool operator==(A& other)" << std::endl;
    //     return m_a == other.m_a;
    // }
    int m_a;
};

// 要传cosnt reference
bool operator<(const A& one, const A& other)
{
    std::cout << "bool operator<(const A& one, const A& other)" << std::endl;
    return one.m_a < other.m_a;
}

bool operator==(const A& one, const A& other)
{
    std::cout << "operator==(const A& one, const A& other)" << std::endl;
    return one.m_a == other.m_a;
}

int main()
{
    A a1(10);
    A a2(20);
    A a3(30);
    A a4(10);
    
    std::cout << (a1 < a2) << std::endl;
    std::cout << (a1 > a2) << std::endl;
    std::cout << (a1 <= a2) << std::endl;
    std::cout << (a1 >= a2) << std::endl;
    std::cout << (a1 <= a4) << std::endl;
    std::cout << (a1 >= a4) << std::endl;

    std::cout << (a3 == a2) << std::endl;
    std::cout << (a3 != a2) << std::endl;

    return 0;
}
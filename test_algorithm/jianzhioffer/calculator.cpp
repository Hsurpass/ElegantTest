#include <iostream>
#include <stack>

using namespace std;

class HasPtr
{
public:
    HasPtr(int i) : i_(i), ptr_(new string()) {}
    HasPtr(const HasPtr &another)
    {
        i_ = another.i_;
        ptr_ = new string(*(another.ptr_));
    }
    HasPtr &operator=(const HasPtr &another)
    {
        if (this == &another)
            return *this;

        i_ = another.i_;
        delete ptr_;
        ptr_ = new string(*(another.ptr_));

        return *this;
    }
    ~HasPtr() { delete ptr_; }

private:
    int i_;
    std::string *ptr_;
};

/* 
实现一个简单的计算器功能，输入是一个字符串，
如："100+20-30/5*2+100" 输入仅包含0-9 和 + - * /
输出是一个int类型计算结果，不考虑越界
*/

double cal(string &str)
{
    int len = str.size();
    stack<double> si;
    char preOperator = '+';
    string numStr;

    for (int i = 0; i < len; i++)
    {
        if ((str[i] >= '0' && str[i] <= '9'))
        {
            numStr.push_back(str[i]);
        }

        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || i == len-1)
        {
            double num = std::stod(numStr);
            // cout << numStr << "," << num << endl;

            switch (preOperator)
            {
            case '+':
                si.push(num);
                cout << si.top() << endl;
                break;
            case '-':
                si.push(-num);
                cout << si.top() << endl;
                break;
            case '*':
                si.top() *= num; 
                cout << si.top() << endl;
                break;
            case '/':
                si.top() /= num; 
                cout << si.top() << endl;
                break;
            default:
                break;
            }
            preOperator = str[i];
            numStr.clear();
        }
    }

    double result = 0;
    while (!si.empty())
    {
        result += si.top();
        si.pop();
    }

    return result;
}

int main()
{
    string s("100+20-30/5*2+100");
    double result = cal(s);
    cout << result << endl;    

    return 0;
}
#include <iostream>
#include <string>
#include <stack>

using namespace std;

/*
给定一个 0-9数字字符 组成的字符序列s。
假设3和4相邻会爆炸，5和6相邻也会爆炸，字符爆炸之后会消失，爆炸之后可能导致连续爆炸，直到最终稳定。 比如
"1234756" 完全爆炸之后稳定为 127 字符串, 爆炸消失4个字符，我们说 "1234756" 的爆炸指数为4 .
求解字符序列s的爆炸指数.
示例:
输入: s = "1234765"
输出: 4
解释: 因为34爆炸 65爆炸。
示例:
输入: s = "124653"
输出: 4
解释: 因为 65爆炸 43爆炸。
示例:
输入: s = "1230564"
输出: 2
解释: 因为 56爆炸 。
说明：
 s是非空的，元素是数字 0-9
*/

int fBombA100_stack(string& str)
{
    int len = str.size();

    int i = 0, count = 0;
    stack<char> sc;
    sc.push(str[i]);
    i++;

    while (i < len) //s = "1234765"
    {
        if( (str[i] == '3' && sc.top() == '4') || 
            (str[i] == '4' && sc.top() == '3') || 
            (str[i] == '5' && sc.top() == '6') || 
            (str[i] == '6' && sc.top() == '5'))
        {
            sc.pop();
            count += 2;
            i++;
            continue;   // s = "124653"
        }
        sc.push(str[i]);
        i++;
    }
    
    return count;
}

void test_fBombA100_stack()
{
    string s("1234765");
    int n = fBombA100_stack(s);
    cout << s << ", "<< n << endl;  // 1234765, 4

    s = "124653";
    n = fBombA100_stack(s);
    cout << s << ", "<< n << endl;  // 124653, 4

    s = "1230564";
    n = fBombA100_stack(s);
    cout << s << ", "<< n << endl;  // 1230564, 2
    
    s = "12305864";
    n = fBombA100_stack(s);
    cout << s << ", "<< n << endl;  // 12305864, 0
}

int fBombA100(string &str)
{
    int len = str.size();

    int pos;
    while ((pos = str.find("34")) != string::npos ||
           (pos = str.find("43")) != string::npos ||
           (pos = str.find("65")) != string::npos ||
           (pos = str.find("56")) != string::npos)
    {
        str.erase(pos, 2);
    }
    return len - str.size();
}

void test_fBombA100()
{
    string s("1234765");
    int n = fBombA100(s);
    cout << s << ", "<< n << endl;  // 127, 4

    s = "124653";
    n = fBombA100(s);
    cout << s << ", "<< n << endl;  // 12, 4

    s = "1230564";
    n = fBombA100(s);
    cout << s << ", "<< n << endl;  // 12304, 2
    

    s = "12305864";
    n = fBombA100(s);
    cout << s << ", "<< n << endl;  // 12305864, 0
}

int main()
{
    test_fBombA100();
    cout << "----------------------------" << endl;
    test_fBombA100_stack();

    return 0;
}
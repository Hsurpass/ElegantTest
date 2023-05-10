#include <iostream>

using namespace std;

/*
    若满足b为2的整数次幂（即b=1<<k，k为整数）时，可用一个特殊的小技巧将取模运算转化为位运算，即：a%b=a&(b-1)，且b=1<<k（k为整数）。为什么呢？
    我们以8为例，8的二进制表示为：
        3 2 1 0
        1 0 0 0
    在3号位以上均为8的倍数，即对8取模均为0，因此对取模有贡献的为3号位以下的。
    根据上述公式：b-1=8-1=7,7的二进制表示为:
        3 2 1 0
        0 1 1 1
    此时任何1~7的数与7进行按位与（&）操作，均为其本身，即恰好是对8取模的结果:
        0 1 1 1
       &
        x x x x
        0 x x x
*/

void modConvertBitOperator()
{
    int mod = 8;
    int a = 5;

    cout << a%mod << endl;
    cout << (a & (mod-1)) << endl;

}

int main()
{
    modConvertBitOperator();

    return 0;
}
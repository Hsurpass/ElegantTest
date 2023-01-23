#include <iostream>

using namespace std;

void test_RawString()
{
    string path  = "C:\Program Files (x86)\alipay\aliedit\5.1.0.3754";
    string path2 = "C:\\Program Files (x86)\\alipay\\aliedit\\5.1.0.3754";
    string path3 = R"(C:\Program Files (x86)\alipay\aliedit\5.1.0.3754)";
    string path4 = R"(C:\Program Files (x86)\alipay\aliedit\5.1.0.3754)";
    string path5 = R"(C:\Program "Files" (x86)\\alipay\aliedit\5.1.0.3754)";
    cout << path << endl;   // C:Program Files (x86)lipayliedit.1.0.3754
    cout << path2 << endl;  // C:\Program Files (x86)\alipay\aliedit\5.1.0.3754
    cout << path3 << endl;  // C:\Program Files (x86)\alipay\aliedit\5.1.0.3754
    cout << path4 << endl;  // C:\Program Files (x86)\alipay\aliedit\5.1.0.3754
    cout << path5 << endl;  // C:\Program "Files" (x86)\\alipay\aliedit\5.1.0.3754
}

int main()
{
    test_RawString();

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

class StringRotation {
public:
    string rotateString(string A, int n, int p) {
        string str = A.substr(p+1, n);
        str += A.substr(0, p+1);

        return str;
    }
};

int main()
{
    string s("ABCDEFGH");
    StringRotation sr;
    
    string str = sr.rotateString(s, s.size(), 4);
    cout << str << endl;

    return 0;
}
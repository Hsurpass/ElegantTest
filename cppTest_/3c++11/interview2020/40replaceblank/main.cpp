#include <iostream>

using namespace std;
void replaceblank(char *p,int length)
{
    if(p == NULL || length <= 0)
    {
        return;
    }
    int originallen = 0;
    int blankcount = 0;
    int newlen = 0;

    while(*p != '\0')
    {
        ++originallen;
        if(*p == ' ')
        {
            ++blankcount;
        }
        p++;
    }
    newlen = originallen + blankcount * 2;
//    char *p_oritail = buf + originallen;
//    char *p_newtail = buf + newlen;

    while (originallen < newlen) {
        if(p[originallen] == ' ')
        {
            p[newlen--] = '0';
            p[newlen--] = '2';
            p[newlen--] = '%';
        }
        else {
            p[newlen--] = p[originallen];
        }
        originallen--;
    }
}

int main()
{
//    char buf[64] = "we are happy";
//    char *buf=NULL;
//    char buf[64] = " ";
    char buf[64] = "    ";
    printf("%s\n",buf);
//    cout << sizeof(buf) << endl;
//    cout << sizeof(64) << endl;
    replaceblank(buf,sizeof(buf));
//    cout << buf << endl;
    printf("%s\n",buf);
    return 0;
}

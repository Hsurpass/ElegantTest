#include <iostream>

using namespace std;
class Goat
{
public:
    virtual void miemie() = 0;
};
class normalgoat:public Goat
{
public:
    normalgoat() {}
    void miemie()
    {
        cout << "I am a real goat" << endl;
    }
};
class Wolf
{
public:
    Wolf() {}
    void howl()
    {
        cout << "I am a real Wolf" << endl;
    }
};
class Adaptergoat:public Goat
{
public:
    Adaptergoat(Wolf *w) {_w = w;}
    void miemie()
    {
        _w->howl();
    }
protected:
    Wolf *_w;
};
int main()
{
    normalgoat g;
    g.miemie();
    Wolf w;
    w.howl();
    Adaptergoat gw(&w);
    gw.miemie();
    return 0;
}

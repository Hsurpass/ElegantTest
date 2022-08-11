#include <iostream>

using namespace std;

class Weapon
{
public:
    virtual void use() = 0;
};
class knife:public Weapon
{
public:
//    knife() {}
    void use()
    {
        cout << "use knife kill you" << endl;
    }
};
class gun:public Weapon
{
public:
//    gun() {}
    void use()
    {
        cout << "use gun kill you" << endl;
    }
};
class sprite
{
public:
    sprite(Weapon *w = new knife) {
       _w = w;
    }
    void changeweapon(Weapon *w)
    {
        _w = w;
    }
    void fight()
    {
        _w->use();
    }
private:
    Weapon *_w;
};
int main()
{
    knife *kn = new knife;
    gun * g = new gun;

    sprite *sp = new sprite;
    sp->fight();

    sp->changeweapon(g);
    sp->fight();
    return 0;
}

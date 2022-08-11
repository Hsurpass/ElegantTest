#include <iostream>

using namespace std;
class Line
{
public:
    virtual void drawLine() = 0;
};
class solidLine:public Line
{
public:
    solidLine() {}
    void drawLine()
    {
        cout << "solidLine.....solidLine" << endl;
    }
};
class dotLine:public Line
{
public:
    dotLine() {}
    void drawLine()
    {
        cout << "dotLine.....dotLine" << endl;
    }
};
class Shape
{
public:
    Shape(int x,int y,Line *pl):_x(x),_y(y),_pl(pl)
    {}
    virtual void drawshape() = 0;
protected:
    int _x;
    int _y;
    Line *_pl;
};
class Circle:public Shape
{
public:
    Circle(int x = 0,int y = 0,int ridus = 0,Line *pl = NULL):Shape(x,y,pl),_ridus(ridus)
    {}
    void drawshape()
    {
        cout << "cirle:x=" << _x << ",y=" << _y << ",ridus=" << _ridus << endl;
        _pl->drawLine();
    }
private:
    int _ridus;
};
class Rect:public Shape
{
public:
    Rect(int x = 0,int y = 0,int length=0,int width=0,Line *pl = NULL)
        :Shape(x,y,pl),_length(length),_width(width)
    {}
    void drawshape()
    {
        cout << "Rect:x=" << _x << ",y=" << _y << ",length=" << _length << ",_width" << _width << endl;
        _pl->drawLine();
    }
private:
    int _length;
    int _width;
};
int main()
{
    solidLine sl;
    dotLine dl;
    Circle cir(1,2,3,&sl);
    cir.drawshape();
    Rect rect(5,6,7,8,&dl);
    rect.drawshape();
    return 0;
}

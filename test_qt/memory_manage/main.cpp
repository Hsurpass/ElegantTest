#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QString>

class mypushbutton : public QPushButton
{
public:
    mypushbutton(QString s, QWidget* parent = nullptr):QPushButton(s, parent) {
        qDebug() << "mypushbutton";
    }
    ~mypushbutton() { qDebug() << "~mypushbutton()"; }
};

class mywidget : public QWidget {
public:
    mywidget(QWidget* parent = nullptr):QWidget(parent){
        qDebug() << "mywidget()";
        this->resize(400,300);
        this->move(100, 100);
        mypushbutton* mpb = new mypushbutton(QString("click"), this);
//        mpb->setParent(this);
        mpb->show();
    }
    ~mywidget() { qDebug() << "~mywidget()"; }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    mywidget mw;
    mw.show();
    return a.exec();
}

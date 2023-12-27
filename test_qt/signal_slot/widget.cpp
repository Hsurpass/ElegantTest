#include "widget.h"
#include <QPushButton>
#include <QString>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(420,300);
    this->setWindowTitle("信号槽");
    QPushButton* btn = new QPushButton(QString("close"), this);
//    connect(btn, SIGNAL(clicked()), this, SLOT(close()));
//    connect(btn, &QPushButton::clicked, this, &Widget::close);
//    connect(btn, &QPushButton::clicked, this, &Widget::widgetClose);

    connect(btn, &QPushButton::clicked, this, &Widget::emitClick);
    connect(this, &Widget::widgetClick, this, &Widget::widgetClose);
    btn->show();
}

Widget::~Widget()
{

}
//void Widget::widgetClick(){}

void Widget::widgetClose(QString str)
{
    qDebug() << "Widget::widgetClose()" << str;
    this->close();
}

void Widget::emitClick()
{
    qDebug() << "emit Widget::emitClick()";
//    emit
    emit widgetClick(QString("hello"));
}

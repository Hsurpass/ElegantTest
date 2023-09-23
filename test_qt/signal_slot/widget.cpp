#include "widget.h"
#include <QPushButton>
#include <QString>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
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

void Widget::widgetClose()
{
    qDebug() << "Widget::widgetClose()";
    this->close();
}

void Widget::emitClick()
{
    qDebug() << "emit Widget::emitClick()";
//    emit
    emit widgetClick();
}

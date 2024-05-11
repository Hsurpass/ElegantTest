#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>
#include <QDialog>
#include <QDebug>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton* btn1 = new QPushButton("dialog", this);
    connect(btn1, SIGNAL(clicked()), this, SLOT(showDialog()));
}

Widget::~Widget()
{
    delete ui;
}



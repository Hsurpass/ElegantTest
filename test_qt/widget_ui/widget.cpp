#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->horizontalSlider_3->setMinimum(0);
    ui->horizontalSlider_3->setMaximum(100);
    ui->spinBox_3->setMinimum(0);
    ui->spinBox_3->setMaximum(100);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slider1_valueChange(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(slider2_valueChange(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(slider3_valueChange(int)));

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBox1_valueChange(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(spinBox2_valueChange(int)));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(spinBox3_valueChange(int)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::slider1_valueChange(int value)
{
    ui->spinBox->setValue(value);
}

void Widget::slider2_valueChange(int value)
{
    ui->spinBox_2->setValue(value);
}

void Widget::slider3_valueChange(int value)
{
    ui->spinBox_3->setValue(value);
}

void Widget::spinBox1_valueChange(int value)
{
    ui->horizontalSlider->setValue(value);
}

void Widget::spinBox2_valueChange(int value)
{
    ui->horizontalSlider_2->setValue(value);
}

void Widget::spinBox3_valueChange(int value)
{
    ui->horizontalSlider_3->setValue(value);
}


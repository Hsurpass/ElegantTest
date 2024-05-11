#include "My_Dialog.h"
#include <QDebug>

My_Dialog::My_Dialog(QWidget *parent):QDialog(parent)
{}

My_Dialog::~My_Dialog(){
    qDebug() << "My_Dialog::~My_Dialog()" ;
}

// void My_Dialog::accept()
// {
//     qDebug() << "accept!!!";
// }

// void My_Dialog::reject()
// {
//     qDebug() << "reject!!";
//     this->close();
// }


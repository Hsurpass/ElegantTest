#include <QApplication>
#include <QLabel>
#include <QString>
#include <iostream>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QLabel label(QString("hello world!!"));
    label.show();

    return app.exec();
}
#include "widget.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
#if 0   // 水平布局
//    QHBoxLayout* hboxlayout = new QHBoxLayout();
    QHBoxLayout* hboxlayout = new QHBoxLayout(&w);
    QPushButton* btn[3];

    QString btnstr[3] = {
        "monday",
        "tuesday",
        "wednesday"
    };
    for(int i = 0;i < 3;i++){
        btn[i] = new QPushButton(btnstr[i]);
        hboxlayout->addWidget(btn[i]);
    }

//    w.setLayout(hboxlayout);
#endif
#if 0   // 垂直布局
    QVBoxLayout* vboxlayout = new QVBoxLayout(&w);
    QPushButton* btn[3];

    QString btnstr[3] = {
        "monday",
        "tuesday",
        "wednesday"
    };
    for(int i = 0;i < 3;i++){
        btn[i] = new QPushButton(btnstr[i]);
        vboxlayout->addWidget(btn[i]);
    }

#endif

#if 0   // 网格布局
    QGridLayout* gridlayout = new QGridLayout(&w);
    QPushButton* btn[5];

    QString btnstr[5] = {
        "monday",
        "tuesday",
        "wednesday",
        "thursday",
        "friday"
    };

    for(int i = 0;i < 5;i++){
        btn[i] = new QPushButton(btnstr[i]);
    }
    gridlayout->addWidget(btn[0], 0, 0);
    gridlayout->addWidget(btn[1], 0, 1);
    gridlayout->addWidget(btn[2], 1, 0, 1, 2);
    gridlayout->addWidget(btn[3], 2, 0);
    gridlayout->addWidget(btn[4], 2, 1);
#endif

#if 1
    QVBoxLayout* defaultlayout = new QVBoxLayout();

    QHBoxLayout* hlayout = new QHBoxLayout();
    QVBoxLayout* vlayout = new QVBoxLayout();
    QGridLayout* gridlayout = new QGridLayout();
    QString btnstr[6] = {
        "monday",
        "tuesday",
        "wednesday",
        "thursday",
        "friday",
        "saturday"

    };

    // 水平布局
    for(int i = 0 ;i < 6;i++){
        hlayout->addWidget(new QPushButton(btnstr[i]));
    }
    // 垂直布局
    for(int i =0; i < 3; i++){
        vlayout->addWidget(new QPushButton(btnstr[i]));
    }
    //网格布局
    gridlayout->addWidget(new QPushButton(btnstr[0]), 0, 0);
    gridlayout->addWidget(new QPushButton(btnstr[1]), 0, 1);
    gridlayout->addWidget(new QPushButton(btnstr[2]), 1, 0, 1, 2);
    gridlayout->addWidget(new QPushButton(btnstr[3]), 2, 0);
    gridlayout->addWidget(new QPushButton(btnstr[4]), 2, 1);

    // 三个布局叠加到垂直布局上
    defaultlayout->addLayout(hlayout);
    defaultlayout->addLayout(vlayout);
    defaultlayout->addLayout(gridlayout);

    w.setLayout(defaultlayout);
#endif

    w.show();
    return a.exec();
}

#include "widget.h"
#include "./ui_widget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "my_dialog.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initMainWidget();
    initDialog();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initMainWidget()
{
    QHBoxLayout* hlayout = new QHBoxLayout(this);
    QPushButton* btn = new QPushButton("click",this);
    hlayout->addWidget(btn);
    connect(btn, SIGNAL(clicked()), this, SLOT(showDialog()));
    this->setLayout(hlayout);
}

void Widget::initDialog()
{
    // m_dialog = new QDialog(this);
    m_dialog = new My_Dialog(this);

    QHBoxLayout * hBox = new QHBoxLayout(m_dialog);
    QPushButton * pbEnter = new QPushButton("enter", m_dialog);
    QPushButton * pbCancel = new QPushButton("cancel", m_dialog);
    connect(pbEnter, SIGNAL(clicked()), m_dialog, SLOT(accept()));
    connect(pbCancel, SIGNAL(clicked()), m_dialog, SLOT(reject()));

    hBox->addWidget(pbEnter);
    hBox->addWidget(pbCancel);

    m_dialog->setLayout(hBox);

    // connect(pbEnter, SIGNAL(clicked()), m_dialog, SLOT(accept()));
    // connect(pbCancel, SIGNAL(clicked()), m_dialog, SLOT(close()));
    qDebug() << "initDialog finish";
}

void Widget::showDialog()
{
    int ret = m_dialog->exec();
    qDebug() << "show Dialog return value " << ret;
}




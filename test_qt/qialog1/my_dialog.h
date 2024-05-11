#ifndef MY_DIALOG_H
#define MY_DIALOG_H

#include <QDialog>

class My_Dialog : public QDialog
{
    Q_OBJECT
public:
    My_Dialog(QWidget *parent = nullptr);
    virtual ~My_Dialog();

public slots:
    // void accept() override;
    // void reject() override;
};

#endif // MY_DIALOG_H

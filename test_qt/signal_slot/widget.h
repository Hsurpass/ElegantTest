#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void widgetClick(); // 信号只声明不实现
public slots:
    void widgetClose();
    void emitClick();
};
#endif // WIDGET_H

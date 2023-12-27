#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void widgetClick(QString str); // 信号只声明不实现
public slots:
    void widgetClose(QString str);
    void emitClick();
};
#endif // WIDGET_H

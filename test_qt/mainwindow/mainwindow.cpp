#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QToolBar>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 添加菜单栏
    QMenuBar* menuBar = this->menuBar();
    QString curr_path = QDir::currentPath();
    qDebug() << "curr_path: " << curr_path;
    QString appDirPath = QCoreApplication::applicationDirPath();
    qDebug() << "appDirPath: " << appDirPath;
    // "D:/WorkSpace/3github/ElegantTest/test_qt/mainwindow/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug"

    // QString close_ico_path = curr_path + "../../res/close.ico";
    QString close_ico_path = "D:\\WorkSpace\\3github\\ElegantTest\\test_qt\\test_mainWindow\\res\\close.ico";
    QMenu* file_menu = menuBar->addMenu("File(&F)");
    // file_menu->addAction(QIcon(close_ico_path),"close");
    // file_menu->addAction(QIcon(close_ico_path),"close",this, SLOT(close()), QKeySequence("ctrl+q"));
    QAction* file_action =file_menu->addAction(QIcon(close_ico_path),"close",this, SLOT(close()), QKeySequence("Ctrl+Q"));
    // file_action->setCheckable(false); // default is true

    // 添加工具栏
    QToolBar* toolbar1 = this->addToolBar("tool bar1");
    toolbar1->addAction(file_action); // action可以复用

    QToolBar* toolbar2 = new QToolBar("tool bar2", this);
    toolbar2->addAction(file_action);
    this->addToolBar(Qt::LeftToolBarArea, toolbar2);

    // 添加状态栏
    QStatusBar* statusbar = this->statusBar();
    // statusbar->addAction(file_action);
    statusbar->showMessage("ready");
    // statusbar->showMessage("ready", 5000);

    // 设置中心窗口
    QTextEdit* textedit = new QTextEdit(this);
    this->setCentralWidget(textedit);

    // 设置停靠窗口
    QDockWidget* dock1 = new QDockWidget("dock1", this);
        /*把textedit嵌到dockwidget(停靠窗口)中*/
    QTextEdit* dock_edit = new QTextEdit("dock_edit", dock1);
    dock1->setWidget(dock_edit);
        /*把textedit嵌到dockwidget(停靠窗口)中*/
    this->addDockWidget(Qt::RightDockWidgetArea, dock1);


}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // add menu bar
    QMenuBar* menuBar = this->menuBar();
    // QMenuBar* menubar = new QMenuBar;
    // this->setMenuBar(menubar);

    // add menu
    QMenu* fileMenu = menuBar->addMenu("File(&F)");
    QMenu* editMenu = new QMenu("Edit(&E)", menuBar);
    menuBar->addMenu(editMenu);

    // add action, open, close save are action
    // fileMenu->addAction("close");
    // fileMenu->addAction(QIcon("/mnt/d/WorkSpace/3github/ElegantTest/test_qt/test_mainWindow/res/close.png"),"close");
    // fileMenu->addAction(QIcon("/mnt/d/WorkSpace/3github/ElegantTest/test_qt/test_mainWindow/res/close.ico"),"close");

}

MainWindow::~MainWindow()
{
    delete ui;
}

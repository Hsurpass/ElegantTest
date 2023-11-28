# -*- coding: utf-8 -*-

import sys

from PyQt5.QtWidgets import QApplication, QWidget, QPushButton,QLabel,QLineEdit,QDesktopWidget,QMainWindow
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = QWidget()
    # w = QMainWindow() 
    w.setWindowTitle("first windows")
    w.resize(420,300) # 设置窗口大小

    accLabel = QLabel("account:", w)
    accLabel.setGeometry(20,20,55,20)

    passwdLabel = QLabel("passwd:", w)
    passwdLabel.setGeometry(20,40,55,20)

    # lineEdit = QLineEdit("account", w)
    accountLineEdit = QLineEdit(w)
    accountLineEdit.setPlaceholderText("account")
    accountLineEdit.setGeometry(80,20,200,20)

    passwdLineEdit = QLineEdit(w)
    passwdLineEdit.setPlaceholderText("password")
    passwdLineEdit.setGeometry(80,40,200,20)

    # loginButton = QPushButton(w)
    # loginButton.setText("登录")
    loginButton = QPushButton("登录", w)
    loginButton.setGeometry(100,100,100,30)

    # w.move(0, 0) #移动到左上角

    # 移动到屏幕中间
    # 方法1：
    center_point = app.desktop().availableGeometry().center()
    # center_point = QDesktopWidget().availableGeometry().center()
    print("screen center_point: {0} ".format(center_point))
    # # w.move(center_point) #这只是把widget左上角放到屏幕中央
    # x = center_point.x() - 210
    # y = center_point.y() - 150
    # w.move(x, y) #减去widget长和高的一半

    # 方法二：
    wx,wy,ww,wh = w.frameGeometry().getRect()
    print("wx:{0},wy:{1},ww:{2},wh:{3}".format(wx,wy,ww,wh))
    w.move(int(center_point.x() - ww/2), int(center_point.y() - wh/2))

    # 设置窗口左上角图标
    # w.setWindowIcon(QIcon("/mnt/d/WorkSpace/3github/ElegantTest/test_python/python3/pyqt5/online_learning_32px_1298421_easyicon.net.xpm"))

    # 去掉标题栏
    # w.setWindowFlag(Qt.FramelessWindowHint)


    


    w.show()

    app.exec()
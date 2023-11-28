
import sys

from PyQt5 import QtCore

from PyQt5.QtWidgets import QApplication, QWidget, QDesktopWidget,QMainWindow,\
    QPushButton,QLabel,QLineEdit,\
    QVBoxLayout,QHBoxLayout,QFormLayout,QStackedLayout

from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

class loginWindow(QWidget):
    def __init__(self):
        #一定要调用父类的__init__方法，里面有很多初始化操作
        super().__init__()
        self.init_loginUI()

    def init_loginUI(self):
        self.setWindowTitle("login")
        self.setFixedSize(420,300)  #固定窗口大小，禁止拉伸
        # self.resize(420,300) # 设置窗口大小

        rootvlayout = QVBoxLayout()
        
        # accHlayout = QHBoxLayout()
        # accLabel = QLabel("account:")
        # accLabel.setGeometry(20,20,55,20)
        # accountLineEdit = QLineEdit()
        # accountLineEdit.setPlaceholderText("account")
        # accountLineEdit.setGeometry(80,20,200,20)
        # accHlayout.addWidget(accLabel)
        # accHlayout.addWidget(accountLineEdit)
        # rootvlayout.addLayout(accHlayout)

        # passwdHlayout = QHBoxLayout()
        # passwdLabel = QLabel("passwd:")
        # passwdLabel.setGeometry(20,40,55,20)
        # passwdLineEdit = QLineEdit()
        # passwdLineEdit.setPlaceholderText("password")
        # passwdLineEdit.setGeometry(80,40,200,20)
        # passwdHlayout.addWidget(passwdLabel)
        # passwdHlayout.addWidget(passwdLineEdit)
        # rootvlayout.addLayout(passwdHlayout)
        
        # loginButton = QPushButton("登录")
        # loginButton.setGeometry(100,100,100,30)
        # rootvlayout.addWidget(loginButton)

        accpdFormLayout = QFormLayout()

        accLineEdit = QLineEdit()
        accLineEdit.setPlaceholderText("请输入账号")
        passwdLineEdit = QLineEdit()
        passwdLineEdit.setPlaceholderText("请输入密码")
        accpdFormLayout.addRow("账号：", accLineEdit)
        accpdFormLayout.addRow("密码：", passwdLineEdit)
        rootvlayout.addLayout(accpdFormLayout)

        loginButton = QPushButton("登录")
        loginButton.setFixedSize(100,30)#固定按钮大小
        rootvlayout.addWidget(loginButton, alignment=Qt.AlignmentFlag.AlignCenter)#指定对齐方式

        self.setLayout(rootvlayout)
 

if __name__ == "__main__":
    app = QApplication(sys.argv)

    loginWind = loginWindow()

    loginWind.show()

    app.exec()

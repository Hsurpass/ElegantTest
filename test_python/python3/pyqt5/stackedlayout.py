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

    def init_loginUI():
        pass

if __name__ == "__main__":
    app = QApplication(sys.argv)

    loginWind = loginWindow()

    loginWind.show()

    app.exec()
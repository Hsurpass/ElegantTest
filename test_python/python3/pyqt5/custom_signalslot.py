import sys

from PyQt5 import QtCore

from PyQt5.QtWidgets import QApplication, QWidget, QDesktopWidget,QMainWindow,QDialog,\
    QPushButton,QLabel,QLineEdit,\
    QVBoxLayout,QHBoxLayout,QFormLayout,QStackedLayout

from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt,pyqtSignal

class mywindow(QMainWindow):
    sig1 = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        self.count = 0
        self.init_mywindow()

    def init_mywindow(self):
        self.resize(420,300)

        btn = QPushButton(self)
        btn.clicked.connect(self.on_click)
        self.sig1.connect(self.slot1)

        

    def slot1(self, str):
        print("slot1: ", str)

    def on_click(self):
        print("btn clicked: ", self.count)
        self.sig1.emit("hello: {0}".format(self.count))
        self.count += 1


if __name__ == "__main__":
    app = QApplication(sys.argv)

    mywindow = mywindow()

    mywindow.show()

    app.exec()
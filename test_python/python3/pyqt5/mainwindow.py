import sys

from PyQt5 import QtCore

from PyQt5.QtWidgets import QApplication, QWidget, QDesktopWidget,QMainWindow,QDialog,\
    QPushButton,QLabel,QLineEdit,\
    QVBoxLayout,QHBoxLayout,QFormLayout,QStackedLayout

from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

class mywindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.init_mywindow()

    def init_mywindow(self):
        label = QLabel("这是文字")
        label.setStyleSheet("font-size:30px;color:red")

        rootmenu = self.menuBar()
        # rootmenu.setNativeMenuBar(False)
        
        filemenu = rootmenu.addMenu("文件")
        filemenu.addAction("新建")
        filemenu.addAction("打开")
        filemenu.addAction("保存")
        
        editmenu = rootmenu.addMenu("编辑")
        editmenu.addAction("复制")
        editmenu.addAction("粘贴")
        editmenu.addAction("剪切")


        self.setCentralWidget(label)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    mywindow = mywindow()

    mywindow.show()

    app.exec()
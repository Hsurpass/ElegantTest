import sys
import typing
from PyQt5 import QtCore

from PyQt5.QtWidgets import QApplication, QWidget,QDesktopWidget,QMainWindow, \
        QGroupBox, QPushButton,QRadioButton,QLabel,QLineEdit,\
        QVBoxLayout,QHBoxLayout, QGridLayout,QFormLayout,QStackedLayout

from PyQt5.QtGui import QIcon,QFont
from PyQt5.QtCore import Qt

class Calculator(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("计算器")
        self.setWindowIcon(QIcon("/home/hchy/24px.ico"))

        rootLayout = QVBoxLayout()

        # 输入框
        le = QLineEdit()
        le.setPlaceholderText('请输入内容')
        rootLayout.addWidget(le)
        # rootLayout.addStretch()
    
        #网格布局按键
        gridLayout = QGridLayout()

        data = {
            0:["7","8","9","+","("],
            1:["4","5","6","-",")"],
            2:["1","2","3","*","<-"],
            3:["0",".","=","/","C"]
        }
        for row, arr in data.items():
            for col, ele in  enumerate(arr):
                btn = QPushButton(ele)
                gridLayout.addWidget(btn,row,col)

        rootLayout.addLayout(gridLayout)


        self.setLayout(rootLayout)



if __name__ == "__main__":
    app = QApplication(sys.argv)

    cal = Calculator()

    cal.show()

    # app.setWindowIcon(QIcon("/mnt/d/WorkSpace/3github/ElegantTest/test_python/python3/pyqt5/24px.png"))
    
    app.exec()
 
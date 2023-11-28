
import sys

from PyQt5.QtWidgets import QApplication, QWidget,QGroupBox, \
        QPushButton,QLabel,QLineEdit,QDesktopWidget,QMainWindow,\
        QVBoxLayout,QHBoxLayout, QRadioButton
from PyQt5.QtGui import QIcon,QFont
from PyQt5.QtCore import Qt


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = QWidget()
    # sudo apt install fonts-noto-cjk **
    # sudo apt install fontconfig
    # sudo fc-cache -fv     # 刷新字体缓存
    w.setFont(QFont('utf-8',12))    #12代表字体大小（12磅）
    # w.setFont(QFont('Noto Sans',12))
    # w.setFont(QFont('Noto Sans CJK SC', 12))

    # sudo apt install ttf-mscorefonts-installer
    # w.setFont(QFont('Arial',12))

    rootlayout = QVBoxLayout()

    vlayout = QVBoxLayout()
    hobby_box = QGroupBox(u"爱好")
    btn1 = QRadioButton()
    btn1.setText("抽烟")
    btn2 = QRadioButton("喝酒")
    btn3 = QRadioButton("烫头")
    vlayout.addWidget(btn1)
    vlayout.addWidget(btn2)
    vlayout.addWidget(btn3)
    hobby_box.setLayout(vlayout)

    genderbox = QGroupBox("性别")
    hlayout = QHBoxLayout()
    btn4 = QRadioButton("男")
    btn5 = QRadioButton("女")
    hlayout.addWidget(btn4)
    hlayout.addWidget(btn5)
    genderbox.setLayout(hlayout)

    rootlayout.addWidget(hobby_box)
    rootlayout.addWidget(genderbox)

    w.setLayout(rootlayout)
    w.show()

    app.exec()

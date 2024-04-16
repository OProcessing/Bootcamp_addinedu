import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
import urllib.request

from_class = uic.loadUiType("Spinbox.ui")[0]

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)

        min = 100
        max = 500
        step = 10

        self.lineMin.setText(str(min))
        self.lineMax.setText(str(max))
        self.lineStep.setText(str(step))

        self.pushButton.clicked.connect(self.apply)
        
        self.pBtnLoad.clicked.connect(self.load_file)
        self.pBtnSave.clicked.connect(self.save_file)

        self.slider.setRange(min,max)
        self.slider.setSingleStep(step)
        self.slider.valueChanged.connect(self.changeSlider)
        self.sliderLabel.setText(str(self.slider.value()))


        self.pixmap = QPixmap()
        self.pixmap.load('./toothless.jpeg')
        self.pixmap = self.pixmap.scaled(self.pixMap.width(), self.pixMap.height())
        self.pixMap.setPixmap(self.pixmap)
        self.pixMap.resize(self.pixmap.width(), self.pixmap.height())

    def load_file(self) :
        self.fname=QFileDialog.getOpenFileName(self, '', '', 'All File(*);; 그림(*.png *jpg *jpeg)')
        self.pixmap = QPixmap()
        self.pixmap.load(self.fname[0])
        print(self.fname[0])
        self.pixmap = self.pixmap.scaled(self.pixMap.width(), self.pixMap.height())
        self.pixMap.setPixmap(self.pixmap)
        self.pixMap.resize(self.pixmap.width(), self.pixmap.height())

    def save_file(self) :
        fileName,_ = QFileDialog.getSaveFileName(self)
        if fileName:
            self.pixmap.save(fileName)
            print("Image saved as:", fileName)

    def changeSlider(self) :
        actualValue =  self.slider.value()
        self.sliderLabel.setText(str(actualValue))
        self.pixmap = QPixmap()
        self.pixmap.load(self.fname[0])
        self.pixmap = self.pixmap.scaled(actualValue, actualValue)
        self.pixMap.setPixmap(self.pixmap)
        self.pixMap.resize(self.pixmap.width(), self.pixmap.height())

    def apply(self) :
        min = self.lineMin.text()
        max = self.lineMax.text()
        step = self.lineStep.text()

        self.slider.setRange(int(min), int(max))
        self.slider.setSingleStep(int(step))

if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()

    sys.exit(app.exec())
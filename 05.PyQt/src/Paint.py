import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
from PyQt5.QtCore import *
import urllib.request


from_class = uic.loadUiType("Paint.ui")[0]

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)

        self.pixmap = QPixmap(self.label.width(), self.label.height())
        self.pixmap.fill(Qt.white)

        self.label.setPixmap(self.pixmap)
        self.draw()
        self.x, self.y = None, None

    def draw(self) :
        painter = QPainter(self.label.pixmap())

        self.pen = QPen(Qt.red, 5, Qt.SolidLine)
        painter.setPen(self.pen)
        painter.drawLine(100,100,500,100)

        
        self.pen.setBrush(Qt.blue)
        self.pen.setWidth(5)
        self.pen.setStyle(Qt.DashDotLine)
        painter.setPen(self.pen)
        
        self.line = QLine(100,200,300,300)
        painter.drawLine(self.line)

        painter.setPen(QPen(Qt.black, 3, Qt.DashDotLine))
        self.p1 = QPoint(100,300)
        self.p2 = QPoint(400,150)
        painter.drawLine(self.p1, self.p2)

        painter.setPen(QPen(Qt.blue, 15, Qt.DotLine))
        painter.setBrush(QBrush(Qt.green))
        painter.drawRect(100,100,100,100)

        painter.setPen(QPen(Qt.red, 15, Qt.DotLine))
        painter.setBrush(QBrush(Qt.blue))
        painter.drawEllipse(200,200,100,100)


        painter.setPen(QPen(Qt.black, 30, Qt.SolidLine))
        painter.drawPoint(50,50)

        painter.drawText(300,300, 'This letter is origined by the united kingdom of great britain, ')

        
        painter.end

    def mouseMoveEvent(self,event) :
        if self.x is None :
            self.x = event.x()
            self.y = event.y()
            return
        painter = QPainter(self.label.pixmap())
        painter.drawLine(self.x - self.label.x(), self.y - self.label.y(), event.x() - self.label.x(), event.y() - self.label.y())


        painter.end()
        self.update()

        self.x = event.x()
        self.y = event.y()

    def mousReleaseEvent(self, event) :
        self.x = None
        self.y = None
    
if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())
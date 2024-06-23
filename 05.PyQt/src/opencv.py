import sys
import time
import datetime
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
import cv2, imutils

from_class = uic.loadUiType("opencv.ui")[0]


class Camera(QThread) :
    update = pyqtSignal()
    def __init__ (self, sec=0, parent=None) :
        super().__init__()
        self.main = parent
        self.running = True

    def run(self) :
        while self.running == True :
            self.update.emit()
            time.sleep(0.05)

class VideoThread(QThread):
    updatePixmap = pyqtSignal(QPixmap)

    def __init__(self, fileName):
        super().__init__()
        self.fileName = fileName

    def run(self):
        cap = cv2.VideoCapture(self.fileName)
        while cap.isOpened():
            ret, frame = cap.read()
            if ret:
                #frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
                h, w, c = frame.shape
                qimage = QImage(frame.data, w, h, w * c, QImage.Format_RGB888)
                pixmap = QPixmap.fromImage(qimage)
                self.updatePixmap.emit(pixmap)
            else:
                break
            time.sleep(0.05)  # Optional: Add delay between frames
        cap.release()

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)

        self.isCameraOn = False
        self.isRecStart = False

        self.pixmap = QPixmap()
        self.camera = Camera(self)
        self.camera.daemon = True
        self.record = Camera(self)
        self.record.daemon = True
        self.count = 0

        self.btnRecord.hide()
        self.btnCapture.hide()

        self.btnOpenfile.clicked.connect(self.openFile)
        self.btnOpenVideo.clicked.connect(self.openVideo)
        self.btnCamera.clicked.connect(self.clickCamera)
        self.camera.update.connect(self.updateCamera)
        self.btnRecord.clicked.connect(self.clickRecord)
        self.record.update.connect(self.updateRecording)
        self.btnCapture.clicked.connect(self.capture)

    def clickRecord(self) :
        if self.isRecStart == False :
            self.btnRecord.setText('Rec stop')
            self.isRecStart = True
            self.recordingStart()
        else :
            self.btnRecord.setText('Rec Start')
            self.isRecStart = False
            self.recordingStop()

    def updateRecording(self) :
        self.writer.write(self.image)

    def recordingStart(self) :
        self.record.running = True
        self.record.start()
        self.now = datetime.datetime.now().strftime('%Y%m%d_%H%M%WS')
        filename = self.now + '.avi'
        self.fourcc = cv2.VideoWriter_fourcc(*'XVID')
        w = int(self.video.get(cv2.CAP_PROP_FRAME_WIDTH))
        h = int(self.video.get(cv2.CAP_PROP_FRAME_HEIGHT))
        self.writer = cv2.VideoWriter(filename, self.fourcc, 20.0, (w,h))

    def recordingStop(self) :
        self.record.running = False
        if self.isRecStart == True :
            self.writer.release()
            
    def capture(self) :
        self.now = datetime.datetime.now().strftime('%Y%m%d_%H%M%WS')
        filename = self.now + '.png'
        cv2.imwrite(filename, cv2.cvtColor(self.image, cv2.COLOR_RGB2BGR))


    def clickCapture(self) :
        if self.isRecStart == False :
            self.btnRecord.setText('Rec stop')
            self.isRecStart = True
        else :
            self.btnRecord.setText('Rec Start')
            self.isRecStart = False
    def clickCamera(self) :
        if self.isCameraOn == False :
            self.btnCamera.setText('Camera off')
            self.btnRecord.show()
            self.btnCapture.show()
            self.cameraStart()
            self.isCameraOn = True
        else :
            self.btnCamera.setText('Camera on')
            self.isCameraOn = False
            self.btnRecord.hide()
            self.btnCapture.hide()
            self.cameraStop()
            self.recordingStop()
    def cameraStart(self) :
        self.camera.running =  True
        self.camera.start()
        self.video = cv2.VideoCapture(-1)
    def cameraStop(self) :
        self.camera.running =  False
        self.count = 0
        self.video.release

    def updateCamera(self) :
        retval, self.image = self.video.read()
        if retval :
            self.image = cv2.cvtColor(self.image, cv2.COLOR_BGR2RGB)

            h,w,c = self.image.shape
            qimage = QImage(self.image.data, w, h, w*c, QImage.Format_RGB888)

            self.pixmap = self.pixmap.fromImage(qimage)
            self.pixmap = self.pixmap.scaled(self.label.width(), self.label.height())

            self.label.setPixmap(self.pixmap)
    
    def openFile(self) :
        file = QFileDialog.getOpenFileName(filter = 'ALL (*.*)')

        image = cv2.imread(file[0])
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)


        h,w,c = image.shape
        qimage = QImage(image.data, w, h, w*c, QImage.Format_RGB888)

        self.pixmap = self.pixmap.fromImage(qimage)
        self.pixmap = self.pixmap.scaled(self.label.width(), self.label.height())

        self.label.setPixmap(self.pixmap)

    def openVideo(self):
        fileName, _ = QFileDialog.getOpenFileName(self, "Open Video File", "", "Video Files (*.mp4 *.avi)")
        if fileName:
            self.videoThread = VideoThread(fileName)
            self.videoThread.updatePixmap.connect(self.updateLabelPixmap)
            self.videoThread.start()

    def updateLabelPixmap(self, pixmap):
        pixmap = pixmap.scaled(self.label.width(), self.label.height())
        self.label.setPixmap(pixmap)
            
if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())
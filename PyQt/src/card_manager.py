import sys
import serial
import struct
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
from PyQt5.QtCore import *

from_class = uic.loadUiType("./PyQt/card_machine.ui")[0]

class Receiver(QThread) :
    detected = pyqtSignal(bytes)
    recvTotal = pyqtSignal(int)
    changedTotal = pyqtSignal()
    noCard = pyqtSignal()

    def __init__ (self, conn, parent=None) :
        super (Receiver, self).__init__(parent)
        self.is_running = False
        self.conn = conn
        print("recv init")

    def run (self) :
        print("recv start")
        self.is_running = True
        while (self.is_running == True) :
            if self.conn.readable() :
                res = self.conn.read_until(b'\n')
                if len(res) > 0 :
                    res = res[:-2]
                    cmd = res[:2].decode()
                    if cmd == 'GS' and res[2] == 0 :
                        print("recs detected")
                        self.detected.emit(res[3:])
                    elif cmd == 'GT' and res[2] == 0 :
                        print("recv total")
                        print(len(res))
                        self.recvTotal.emit(int.from_bytes(res[3:7], 'little'))
                    elif cmd == 'ST' and res[2] == 0 :
                        print("set total")
                        self.changedTotal.emit()     
                    elif res[2].to_bytes(1, 'little') == b'\xfa' :
                        print("recv noCard")
                        self.noCard.emit()                    
                    else :
                        print("unknown error")
                        print(cmd)

    def stop (self) :
        print("recv stop")
        self.is_running = False

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)

        self.uid = bytes(4)
        self.conn = serial.Serial(port='/dev/ttyACM1', baudrate=9600, timeout=1)

        self.recv = Receiver(self.conn)
        self.recv.start()

        self.recv.detected.connect(self.detected)
        self.recv.recvTotal.connect(self.recvTotal)
        self.recv.changedTotal.connect(self.changedTotal)
        self.recv.noCard.connect(self.noCard)

        self.btnreset.clicked.connect(self.reset)
        self.btncharge.clicked.connect(self.charge)
        self.btnpayment.clicked.connect(self.payment)
        self.disable()

        self.timer = QTimer()
        self.timer.setInterval(3000)
        self.timer.timeout.connect(self.getStatus)
        self.timer.start()

    def reset(self) :
        print("reset")
        self.setTotal(0)
        return

    def send (self, command, data = 0) :
        print ("send")
        req_data = struct.pack('<2s4sic', command, self.uid, data, b'\n')
        self.conn.write(req_data)
        return
    
    def getStatus(self) :
        print("getStatus")
        self.send(b'GS')
        return
    
    def detected(self, uid) :
        print("detected")
        self.uid = uid
        self.timer.stop()
        self.getTotal()
        self.btnreset.setDisabled(False)
        return
    
    def getTotal(self) :
        print("getTotal")
        self.send(b'GT')
        return
    
    def setTotal(self, total) :
        print("setTotal")
        self.send(b'ST', total)
        return
    
    def recvTotal(self, total) :
        print("recvTotal")
        self.enable(total)
        self.linecharge.setText("")
        self.linepayment.setText("")
    
    def changedTotal(self) :
        self.getTotal()
        return
    
    def charge(self) :
        print("charge")
        total = int(self.labeltotal.text())
        charge = int(self.linecharge.text())
        self.setTotal(total + charge)
        return
    
    def payment(self) :
        print("payment")        
        total = int(self.labeltotal.text())
        payment = int(self.linepayment.text())
        if (total < payment) :
            QMessageBox.warning(self, 'Arduino Manager', '잔액이 부족합니다.')
            self.linepayment.setText("")
        else :
            total = total - payment
            self.setTotal(total)
        return
    
    def enable(self, total) :
        self.labeltotal.setText(str(total))
        self.linecharge.setDisabled(False)
        self.btncharge.setDisabled(False)
        self.linepayment.setDisabled(False)
        self.btnpayment.setDisabled(False)
    def disable(self) :
        self.labeltotal.setText("-")
        self.btnreset.setDisabled(True)
        self.linecharge.setDisabled(True)
        self.btncharge.setDisabled(True)
        self.linepayment.setDisabled(True)
        self.btnpayment.setDisabled(True)
    def noCard(self) :
        print("noCard")
        if (self.timer.isActive() == False) :
            print("startTimer")
            self.timer.start()
        self.linecharge.setText("")
        self.linepayment.setText("")
        self.disable()
        return

if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())
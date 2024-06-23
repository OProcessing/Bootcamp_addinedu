import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic

from_class = uic.loadUiType("boxbox.ui")[0]

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Test, PyQt!")

        self.btn_1.clicked.connect(self.btn_clicked_select)
        self.btn_2.clicked.connect(self.btn_clicked_select)
        self.btn_3.clicked.connect(self.btn_clicked_select)
        self.btn_reset.clicked.connect(self.btn_clicked_event)
        self.btn_enter.clicked.connect(self.btn_clicked_event)
        self.btn_clear.clicked.connect(self.btn_clicked_event)

        self.btn_font_ubuntu.clicked.connect(lambda : self.setFont("Ubuntu"))
        self.btn_font_nanumgothic.clicked.connect(lambda : self.setFont("NanumGothic"))

        self.btn_colour_red.clicked.connect(lambda : self.setTextColor(255, 0, 0))
        self.btn_colour_green.clicked.connect(lambda : self.setTextColor(0, 255, 0))
        self.btn_colour_blue.clicked.connect(lambda : self.setTextColor(0, 0, 255))
        self.btn_font_size.clicked.connect(self.setTextSize)

        self.radio_1.clicked.connect(self.radio_clicked)
        self.radio_2.clicked.connect(self.radio_clicked)
        self.radio_3.clicked.connect(self.radio_clicked)

        self.Input1.clicked.connect(self.check_clicked)
        self.Input2.clicked.connect(self.check_clicked)
        self.Input3.clicked.connect(self.check_clicked)
        self.Input4.clicked.connect(self.check_clicked)

        self.btn_pop_name.clicked.connect(self.inputName)
        self.btn_pop_season.clicked.connect(self.inputSeason)
        self.btn_pop_color.clicked.connect(self.inputColor)
        self.btn_pop_font.clicked.connect(self.inputFont)
        self.btn_pop_file.clicked.connect(self.openFile)
        self.line_pop.returnPressed.connect(self.question)

        self.count = 0
        self.label_c.setText(str(self.count))
        self.label_s.setText("")
    
    def question(self) :
        text = self.line_pop.text()
        if text.isdigit() :
            self.text_pop.setText(text)
        else :
            retval = QMessageBox.question(self, 'QMessageBox - question',
                                          'Are you sure to print?',
                                          QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if retval == QMessageBox.Yes :
                self.text_pop.setText(text)
            else :
                self.line_pop.clear()

    def inputName(self) :
        text, ok = QInputDialog.getText(self, 'QInputDialog - Name', 'User name: ')
        if ok and text :
            self. text_pop.append(text)

    def inputSeason(self) :
        items = ['Spring', 'Summer', 'Fall', 'Winter']
        item, ok = QInputDialog.getItem(self, 'QInputDialog - Season', 'Season:', items, 0, False)
        if ok and item :
            self.text_pop.append(item)

    def inputColor(self) :
        color = QColorDialog.getColor()
        if color.isValid():
            self.text_pop.append("Color")
            self.text_pop.selectAll()
            self.text_pop.setTextColor(color)
            self.text_pop.moveCursor(QTextCursor.End)

    def inputFont(self):
        font, ok = QFontDialog.getFont()
        if ok and font :
            info = QFontInfo(font)
            self.text_pop.append(info.family() + info.styleName())
            self.text_pop.selectAll()
            self.text_pop.setFont(font)
            self.text_pop.moveCursor(QTextCursor.End)
    
    def openFile(self) :
        name = QFileDialog.getOpenFileName(self, 'Open File', './')
        if name[0] :
            with open(name[0], 'r') as file:
                data = file.read()
                self.text_pop.setText(data)


    def setFont(self, fontName) :
        font = QFont(fontName, 11)
        self.text_output.setFont(font)

    def setTextColor(self, r, g, b) :
        colour = QColor(r, g, b)
        self.text_output.selectAll()
        self.text_output.setTextColor(colour)
        self.text_output.moveCursor(QTextCursor.End)
        self.text_output.setTextColor(colour)

    def setTextSize(self) :
        if self.line_font_size.text().isdigit() :
            size = int(self.line_font_size.text())
            self.text_output.selectAll()
            self.text_output.setFontPointSize(size)
            self.text_output.moveCursor(QTextCursor.End)

    def btn_clicked_select(self) :
        sender = self.sender()
        self.count += 1
        self.label_c.setText(str(self.count))
        if sender == self.btn_1 : 
            self.label_s.setText("Button 1")
            self.radio_1.setChecked(True)
        elif sender == self.btn_2 : 
            self.label_s.setText("Button 2")
            self.radio_2.setChecked(True)
        elif sender == self.btn_3 : 
            self.label_s.setText("Button 3")
            self.radio_3.setChecked(True)
        else :
            self.label_s.setText("Blank")

    def btn_clicked_event(self) :
        sender = self.sender()
        if sender == self.btn_reset : 
            self.count = 0
            self.label_c.setText(str(self.count))
        elif sender == self.btn_enter :
            input = self.text_input.toPlainText()
            self.text_input.clear()
            self.text_output.append(input)
        elif sender == self.btn_clear :
            self.text_output.clear()
            
    def radio_clicked(self) :
        if self.radio_1.isChecked() :
            self.label_s.setText("Radio 1")
        elif self.radio_2.isChecked() : 
            self.label_s.setText("Radio 2")
        elif self.radio_3.isChecked() :
            self.label_s.setText("Radio 3")
        else :
            self.label_s.setText("Unknown")

    def check_clicked(self) :
        sender = self.sender()
        if sender == self.Input1 :
            if (self.Input1.isChecked()) :
                self.Output1.setChecked(True)
            else :
                self.Output1.setChecked(False)
        elif sender == self.Input2 :
            if (self.Input2.isChecked()) :
                self.Output2.setChecked(True)
            else :
                self.Output2.setChecked(False)
        elif sender == self.Input3 :
            if (self.Input3.isChecked()) :
                self.Output3.setChecked(True)
            else :
                self.Output3.setChecked(False)
        elif sender == self.Input4 :
            if (self.Input4.isChecked()) :
                self.Output4.setChecked(True)
            else :
                self.Output4.setChecked(False)
        else :
            self.text_input.setText("이스터에그 삐뿌삐")




if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())
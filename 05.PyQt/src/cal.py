import sys
import math
from math import pi, e
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
from PyQt5.QtCore import Qt

oper_list = ['+', '-', '/', '*', '%']
num_list = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

from_class = uic.loadUiType('/home/han/Desktop/Han_ws/00.Data/05.PyQt/cal.ui')[0]

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle(" ")

        self.B_0.clicked.connect(self.Btn_n)
        self.B_1.clicked.connect(self.Btn_n)
        self.B_2.clicked.connect(self.Btn_n)
        self.B_3.clicked.connect(self.Btn_n)
        self.B_4.clicked.connect(self.Btn_n)
        self.B_5.clicked.connect(self.Btn_n)
        self.B_6.clicked.connect(self.Btn_n)
        self.B_7.clicked.connect(self.Btn_n)
        self.B_8.clicked.connect(self.Btn_n)
        self.B_9.clicked.connect(self.Btn_n)

        self.B_plus.clicked.connect(self.Btn_operator)
        self.B_minus.clicked.connect(self.Btn_operator)
        self.B_multiple.clicked.connect(self.Btn_operator)
        self.B_divide.clicked.connect(self.Btn_operator)
        self.B_modulo.clicked.connect(self.Btn_operator)

        self.B_root.clicked.connect(self.Btn_expansion)
        self.B_sin.clicked.connect(self.Btn_expansion)
        self.B_cos.clicked.connect(self.Btn_expansion)
        self.B_tan.clicked.connect(self.Btn_expansion)
        self.B_log.clicked.connect(self.Btn_expansion)
        self.B_ln.clicked.connect(self.Btn_expansion)


        self.B_allclear.clicked.connect(self.Btn_other)
        self.B_clear.clicked.connect(self.Btn_other)
        self.B_delete.clicked.connect(self.Btn_other)
        self.B_point.clicked.connect(self.Btn_other)
        self.B_x10.clicked.connect(self.Btn_other)
        self.B_square_inverse.clicked.connect(self.Btn_other)
        self.B_square.clicked.connect(self.Btn_other)
        self.B_square_y.clicked.connect(self.Btn_other)
        self.B_pi.clicked.connect(self.Btn_other)
        self.B_e.clicked.connect(self.Btn_other)
        self.B_bracket_open.clicked.connect(self.Btn_other)
        self.B_bracket_closed.clicked.connect(self.Btn_other)
        self.B_ans.clicked.connect(self.Btn_other)

        self.B_is.clicked.connect(self.Ans)

        self.Box_input.setText("")
        self.input = ''
        self.output = ''
        self.ans = ''
        self.exp_oper = ''
        self.exp_exp = ''
        self.f_ans = 0
        self.f_exp = 0

    def Dp(self) :
        if self.f_exp == 1 :
            self.Box_input.setText("E ::")
            self.Box_input.append('=' + self.output)
            if self.exp_oper == 'r' : self.exp_exp = 'root'
            elif self.exp_oper == 's' : self.exp_exp = 'sin'
            elif self.exp_oper == 'c' : self.exp_exp = 'cos'
            elif self.exp_oper == 't' : self.exp_exp = 'tan'
            elif self.exp_oper == 'l' : self.exp_exp = 'log'
            elif self.exp_oper == 'n' : self.exp_exp = 'ln'
            self.Box_input.append(self.exp_exp + '(' + self.input + ')')
            
        else :
            self.Box_input.setText('G ::')
            self.Box_input.append('= ' + self.output)
            if self.f_ans == 0 :
                self.Box_input.append(self.input)
            else :
                self.Box_input.append("ANS" + self.input)

    def Btn_n(self) :
        sender = self.sender()
        if self.input == self.output : 
            self.input = ''
        if sender == self.B_0 :  self.input += '0'
        elif sender == self.B_1 : self.input += '1'
        elif sender == self.B_2 : self.input += '2'
        elif sender == self.B_3 : self.input += '3'
        elif sender == self.B_4 : self.input += '4'
        elif sender == self.B_5 : self.input += '5'
        elif sender == self.B_6 : self.input += '6'
        elif sender == self.B_7 : self.input += '7'
        elif sender == self.B_8 : self.input += '8'
        elif sender == self.B_9 : self.input += '9'
        self.Dp()

    def Btn_operator(self) :
        sender = self.sender()
        if self.input[-1:] in oper_list :
            self.input = self.input[:-1]
        if sender == self.B_plus : self.input += '+'
        elif sender == self.B_minus : self.input += '-'
        elif sender == self.B_multiple : self.input += '*'
        elif sender == self.B_divide : self.input += '/'
        elif sender == self.B_modulo : self.input += '%'
        self.Dp()

    def Btn_expansion(self) :
        self.f_exp = 1
        sender = self.sender()
        if sender == self.B_root : self.exp_oper = 'r'
        elif sender == self.B_sin : self.exp_oper = 's'
        elif sender == self.B_cos : self.exp_oper = 'c'
        elif sender == self.B_tan : self.exp_oper = 't'
        elif sender == self.B_log : self.exp_oper = 'l'
        elif sender == self.B_ln : self.exp_oper = 'n'
        self.Dp()

    def Btn_other(self) :
        sender = self.sender()
        if sender == self.B_delete : 
            if len(self.input[:]) == len(self.input[:-1]) : 
                self.f_ans = 0
                self.f_exp = 0
                self.exp_oper = ''
                self.exp_exp = ''
            self.input = self.input[:-1]
        elif sender == self.B_allclear :
            self.input = ''
            self.output = ''
            self.ans = ''
            self.exp_oper = ''
            self.exp_exp = ''
            self.f_ans = 0
            self.f_exp = 0
            self.Box_output.setText('')
            self.Dp()
        elif sender == self.B_clear :
            self.input = ''
            self.f_ans = 0
        elif sender == self.B_point : 
            last_operator = 0
            count = 0
            for i in range(len(self.input)):
                if self.input[i] in oper_list:
                    last_operator = i
            for i in range(len(self.input[last_operator:])) :
                if self.input[last_operator+i] == '.' : count += 1
            if count == 0 : 
                if self.input[-1:] not in num_list :
                    self.input += '0'
                self.input += '.'

        elif sender == self.B_ans : 
            if self.f_exp == 0 :  
                self.input = ''
                self.f_ans = 1
        elif sender == self.B_x10 :
            self.input += '*10**'
        elif sender == self.B_square_inverse :
            self.input += '**-1'
        elif sender == self.B_square :
            self.input += '**2'
        elif sender == self.B_square_y :
            self.input += '**'
        elif sender == self.B_pi :
            if self.input == self.output : 
                self.input = ''
            self.input += 'pi'
        elif sender == self.B_e :
            if self.input == self.output : 
                self.input = ''
            self.input += 'e'
        elif sender == self.B_bracket_open :
            if self.input[-1:] in oper_list :
                self.input += '('
            elif self.input[-1:] == '' :
                self.input += '('
            elif self.input[-1:] == '(' :
                self.input += '('
        elif sender == self.B_bracket_closed :
            if self.input.count('(') > self.input.count(')') :
                self.input += ')'
        self.Dp()

    def Ans(self) :
        while (self.input.count('(') > self.input.count(')')) :
            self.input += ')'
            self.Dp()
        try : 
            if self.f_ans == 1 :
                self.input = self.ans + self.input
            tmp = self.input
            self.input = eval(self.input)
            if self.exp_oper == 'r' : self.output = math.sqrt(self.input)
            elif self.exp_oper == 's' : self.output = math.sin(self.input)
            elif self.exp_oper == 'c' : self.output = math.cos(self.input)
            elif self.exp_oper == 't' : self.output = math.tan(self.input)
            elif self.exp_oper == 'l' : self.output = math.log10(self.input)
            elif self.exp_oper == 'n' : self.output = math.log(self.input)
            else : self.output = self.input
            self.output = str(round(self.output, 5))
            self.ans = "(" + str(self.input) +")"
            self.input = self.output
            if self.f_exp == 1 :
                self.Box_output.append(self.exp_exp + '(' + tmp + ') = ' + self.output)
            else :
                self.Box_output.append(tmp +' = ' + self.output)
            self.f_ans = 0
            self.exp_exp = ''
            self.exp_oper = ''
            self.f_exp = 0
            self.Dp()
        except Exception as e :
            self.Box_output.setText("ERROR")
            self.input = ''
    
if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5 import uic
import mysql.connector
import pandas as pd

server = mysql.connector.Connect(
    host = "database-1.c96mmei8egml.ap-northeast-2.rds.amazonaws.com",
    port = "3306",
    user = "root",
    password = " ",
    database = "amrbase"
)

cursor = server.cursor()
cursor.execute("SELECT MIN(Birthday) FROM celeb")
MIN = cursor.fetchall()[0][0].strftime("%Y%m%d")

cursor.execute("SELECT MAX(Birthday) FROM celeb")
MAX = cursor.fetchall()[0][0].strftime("%Y%m%d")

cursor.execute("SELECT DISTINCT(SEX) FROM celeb")
trans = cursor.fetchall()
sex = []
for i in range(len(trans)) :
    sex.append(trans[i][0])

cursor.execute("SELECT DISTINCT(JOB_TITLE) FROM celeb")
trans = cursor.fetchall()
items = []
for i in range(len(trans)) :
    for j in range(len(trans[i])) :
        items.append(trans[i][j])
job = list(set([item for sublist in [item.split(', ') for item in items] for item in sublist]))

cursor.execute("SELECT DISTINCT(AGENCY) FROM celeb")
trans = cursor.fetchall()
agency = []
for i in range(len(trans)) :
    agency.append(trans[i][0])

from_class = uic.loadUiType("Search.ui")[0]

class WindowClass(QMainWindow, from_class) :
    def __init__(self) :
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("searchbox")
            
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.btn_search.clicked.connect(self.Search)

        self.bdstart.setDate(QDate.fromString(MIN, "yyyyMMdd"))
        self.bdend.setDate(QDate.fromString(MAX, "yyyyMMdd"))
        self.bdstart.dateTimeChanged.connect(self.inputNumber)
        self.bdend.dateTimeChanged.connect(self.inputNumber)
      

        for i in range(len(sex)) :
            self.cbsex.addItem(str(sex[i]))

        for i in range(len(job)) :
            self.cbjob.addItem(str(job[i]))

        for i in range(len(agency)) :
            self.cbagency.addItem(str(agency[i]))

    def inputNumber(self) :
        start = self.bdstart.date().toString("yyyyMMdd")
        end = self.bdend.date().toString("yyyyMMdd")
        if start > MAX :
            QMessageBox.warning(self, 'error', '범위를 넘어갔습니다.')
            self.bdstart.setDate(QDate.fromString(MAX, "yyyyMMdd"))
            self.bdend.setDate(QDate.currentDate())
        elif end < MIN :
            QMessageBox.warning(self, 'error', '범위를 넘어갔습니다.')
            self.bdend.setDate(QDate.currentDate())
            self.bdstart.setDate(QDate.fromString(MIN, "yyyyMMdd"))
        elif start > end :
            QMessageBox.warning(self, 'error', '범위를 넘어갔습니다.')
            self.bdstart.setDate(QDate.fromString(MIN, "yyyyMMdd"))
            self.bdend.setDate(QDate.fromString(MAX, "yyyyMMdd"))

    def Search(self) :
        date_start = self.bdstart.text()
        date_end = self.bdend.text()
        sex = self.cbsex.currentText()
        job = self.cbjob.currentText()
        agency = self.cbagency.currentText()

        query = "SELECT NAME, BIRTHDAY, AGE, SEX, JOB_TITLE, AGENCY FROM celeb"
        condition = " BIRTHDAY BETWEEN " + date_start + " and " + date_end + " "
        if sex != 'All' :
            condition += """and sex = '""" + sex + """' """
        if job != 'All' :
            condition += """and JOB_TITLE LIKE '%""" + job + """%' """
        if agency != 'All' :
            condition += """and agency = '""" + agency + """' """
        if condition != "" :
            query += " WHERE " + condition

        cursor.execute(query)
        result = cursor.fetchall()
        message = "SUCCESS"
        self.tester.setText(message)
        
        for i in range(len(result)) :
            self.tableWidget.insertRow(i)
            self.tableWidget.setItem(i, 0, QTableWidgetItem(result[i][0]))
            self.tableWidget.setItem(i, 1, QTableWidgetItem(result[i][1].strftime("%Y%m%d")))
            self.tableWidget.setItem(i, 2, QTableWidgetItem(str(result[i][2])))
            self.tableWidget.setItem(i, 3, QTableWidgetItem(result[i][3]))
            self.tableWidget.setItem(i, 4, QTableWidgetItem(result[i][4]))
            self.tableWidget.setItem(i, 5, QTableWidgetItem(result[i][5]))


if __name__ == "__main__" :
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())



cursor.close()
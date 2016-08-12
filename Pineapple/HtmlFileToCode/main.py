# coding = utf-8

import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *
from PyQt4 import uic

form_class = uic.loadUiType("convertWIN.ui")[0]

class MyWindow(QMainWindow, form_class):
    def __init__(self):
        super(MyWindow, self).__init__()
        self.setupUi(self)

        #event connect
        self.connect(self.checkBox_SelectFile, SIGNAL("clicked()"), self.checkBox_SelectFile_Clicked)
        self.connect(self.btn_Convert, SIGNAL("clicked()"), self.btn_Convert_Clicked)
        self.connect(self.btn_ShutDown, SIGNAL("clicked()"), self.btn_ShutDown_Clicked)


    #event handle
    def checkBox_SelectFile_Clicked(self):
        QMessageBox.about(self, "message", "checkBox_SelectFile")

    def btn_Convert_Clicked(self):
        QMessageBox.about(self, "message", "convert")

    def btn_ShutDown_Clicked(self):
        QMessageBox.about(self, "message", "ShutDown")

    #create_test



if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()


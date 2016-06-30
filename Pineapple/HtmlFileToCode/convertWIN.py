# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'D:\Workspace\SourceTree\Macaron\Pineapple\HtmlFileToCode\convertWIN.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName(_fromUtf8("Dialog"))
        Dialog.resize(640, 472)
        self.linedit_SelectFileName = QtGui.QLineEdit(Dialog)
        self.linedit_SelectFileName.setGeometry(QtCore.QRect(150, 50, 431, 20))
        self.linedit_SelectFileName.setObjectName(_fromUtf8("linedit_SelectFileName"))
        self.lineEdit_HtmlPath = QtGui.QLineEdit(Dialog)
        self.lineEdit_HtmlPath.setGeometry(QtCore.QRect(150, 80, 431, 20))
        self.lineEdit_HtmlPath.setObjectName(_fromUtf8("lineEdit_HtmlPath"))
        self.lineEdit_CodePath = QtGui.QLineEdit(Dialog)
        self.lineEdit_CodePath.setGeometry(QtCore.QRect(150, 110, 431, 20))
        self.lineEdit_CodePath.setObjectName(_fromUtf8("lineEdit_CodePath"))
        self.label = QtGui.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(60, 50, 56, 12))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(40, 80, 91, 16))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(40, 110, 91, 16))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.checkBox_SelectFile = QtGui.QCheckBox(Dialog)
        self.checkBox_SelectFile.setGeometry(QtCore.QRect(130, 50, 16, 16))
        self.checkBox_SelectFile.setText(_fromUtf8(""))
        self.checkBox_SelectFile.setObjectName(_fromUtf8("checkBox_SelectFile"))
        self.btn_Convert = QtGui.QPushButton(Dialog)
        self.btn_Convert.setGeometry(QtCore.QRect(420, 400, 75, 23))
        self.btn_Convert.setObjectName(_fromUtf8("btn_Convert"))
        self.btn_ShutDown = QtGui.QPushButton(Dialog)
        self.btn_ShutDown.setGeometry(QtCore.QRect(510, 400, 75, 23))
        self.btn_ShutDown.setObjectName(_fromUtf8("btn_ShutDown"))

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(_translate("Dialog", "Dialog", None))
        self.label.setText(_translate("Dialog", "특정파일", None))
        self.label_2.setText(_translate("Dialog", "HTML 원본 위치", None))
        self.label_3.setText(_translate("Dialog", "CODE 생성위치", None))
        self.btn_Convert.setText(_translate("Dialog", "변환", None))
        self.btn_ShutDown.setText(_translate("Dialog", "종료", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())


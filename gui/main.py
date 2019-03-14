#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main.ui'
#
# Created by: PyQt4 UI code generator 4.12.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import back
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as plt3d
from mpl_toolkits.mplot3d import Axes3D
import time
from PIL.ImageQt import ImageQt
from PIL import Image

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

class Ui_MainWindow(object):
	def setupUi(self, MainWindow):
		MainWindow.setObjectName(_fromUtf8("MainWindow"))
		MainWindow.resize(580, 824)
		self.centralwidget = QtGui.QWidget(MainWindow)
		self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
		self.label_pic = QtGui.QLabel(self.centralwidget)
		self.label_pic.setGeometry(QtCore.QRect(0, 0, 581, 141))
		self.label_pic.setAutoFillBackground(True)
		self.label_pic.setStyleSheet(_fromUtf8(""))
		self.label_pic.setText(_fromUtf8(""))
		self.label_pic.setPixmap(QtGui.QPixmap(_fromUtf8("Logo.png")))
		self.label_pic.setScaledContents(True)
		self.label_pic.setObjectName(_fromUtf8("label_pic"))
		self.pushButton = QtGui.QPushButton(self.centralwidget)
		self.pushButton.setGeometry(QtCore.QRect(0, 300, 121, 71))
		self.pushButton.setObjectName(_fromUtf8("pushButton"))
		self.pushButton.clicked.connect(self.btnstate)
		self.label_pic_2 = QtGui.QLabel(self.centralwidget)
		self.label_pic_2.setGeometry(QtCore.QRect(0, 370, 581, 291))
		self.label_pic_2.setAutoFillBackground(True)
		self.label_pic_2.setStyleSheet(_fromUtf8(""))
		self.label_pic_2.setText(_fromUtf8(""))
		self.label_pic_2.setPixmap(QtGui.QPixmap())
		self.label_pic_2.setScaledContents(True)
		self.label_pic_2.setObjectName(_fromUtf8("label_pic_2"))
		self.layoutWidget = QtGui.QWidget(self.centralwidget)
		self.layoutWidget.setGeometry(QtCore.QRect(20, 670, 541, 91))
		self.layoutWidget.setObjectName(_fromUtf8("layoutWidget"))
		self.horizontalLayout = QtGui.QHBoxLayout(self.layoutWidget)
		self.horizontalLayout.setMargin(0)
		self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
		self.ESTOP_2 = QtGui.QPushButton(self.layoutWidget)
		palette = QtGui.QPalette()
		brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.Button, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.Button, brush)
		brush = QtGui.QBrush(QtGui.QColor(159, 158, 158))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.Button, brush)
		self.ESTOP_2.setPalette(palette)
		self.ESTOP_2.setObjectName(_fromUtf8("ESTOP_2"))
		self.horizontalLayout.addWidget(self.ESTOP_2)
		self.ESTOP_3 = QtGui.QPushButton(self.layoutWidget)
		palette = QtGui.QPalette()
		brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.Button, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.Button, brush)
		brush = QtGui.QBrush(QtGui.QColor(159, 158, 158))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.Button, brush)
		self.ESTOP_3.setPalette(palette)
		self.ESTOP_3.setObjectName(_fromUtf8("ESTOP_3"))
		self.horizontalLayout.addWidget(self.ESTOP_3)
		self.ESTOP = QtGui.QPushButton(self.layoutWidget)
		palette = QtGui.QPalette()
		brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.Button, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.Button, brush)
		brush = QtGui.QBrush(QtGui.QColor(159, 158, 158))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.WindowText, brush)
		brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
		brush.setStyle(QtCore.Qt.SolidPattern)
		palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.Button, brush)
		self.ESTOP.setPalette(palette)
		self.ESTOP.setObjectName(_fromUtf8("ESTOP"))
		self.horizontalLayout.addWidget(self.ESTOP)
		self.splitter = QtGui.QSplitter(self.centralwidget)
		self.splitter.setGeometry(QtCore.QRect(0, 140, 571, 161))
		self.splitter.setOrientation(QtCore.Qt.Horizontal)
		self.splitter.setObjectName(_fromUtf8("splitter"))
		self.layoutWidget1 = QtGui.QWidget(self.splitter)
		self.layoutWidget1.setObjectName(_fromUtf8("layoutWidget1"))
		self.formLayout = QtGui.QFormLayout(self.layoutWidget1)
		self.formLayout.setFieldGrowthPolicy(QtGui.QFormLayout.AllNonFixedFieldsGrow)
		self.formLayout.setMargin(0)
		self.formLayout.setObjectName(_fromUtf8("formLayout"))
		self.label = QtGui.QLabel(self.layoutWidget1)
		self.label.setObjectName(_fromUtf8("label"))
		self.formLayout.setWidget(0, QtGui.QFormLayout.LabelRole, self.label)
		self.xInput = QtGui.QLabel(self.layoutWidget1)
		self.xInput.setObjectName(_fromUtf8("xInput"))
		self.formLayout.setWidget(1, QtGui.QFormLayout.LabelRole, self.xInput)
		self.xLineEdit = QtGui.QLineEdit(self.layoutWidget1)
		self.xLineEdit.setObjectName(_fromUtf8("xLineEdit"))
		self.formLayout.setWidget(1, QtGui.QFormLayout.FieldRole, self.xLineEdit)
		self.zInput = QtGui.QLabel(self.layoutWidget1)
		self.zInput.setObjectName(_fromUtf8("zInput"))
		self.formLayout.setWidget(2, QtGui.QFormLayout.LabelRole, self.zInput)
		self.zLineEdit = QtGui.QLineEdit(self.layoutWidget1)
		self.zLineEdit.setObjectName(_fromUtf8("zLineEdit"))
		self.formLayout.setWidget(2, QtGui.QFormLayout.FieldRole, self.zLineEdit)
		self.yInput = QtGui.QLabel(self.layoutWidget1)
		self.yInput.setObjectName(_fromUtf8("yInput"))
		self.formLayout.setWidget(3, QtGui.QFormLayout.LabelRole, self.yInput)
		self.yLineEdit = QtGui.QLineEdit(self.layoutWidget1)
		self.yLineEdit.setObjectName(_fromUtf8("yLineEdit"))
		self.formLayout.setWidget(3, QtGui.QFormLayout.FieldRole, self.yLineEdit)
		self.layoutWidget_2 = QtGui.QWidget(self.splitter)
		self.layoutWidget_2.setObjectName(_fromUtf8("layoutWidget_2"))
		self.formLayout_2 = QtGui.QFormLayout(self.layoutWidget_2)
		self.formLayout_2.setFieldGrowthPolicy(QtGui.QFormLayout.AllNonFixedFieldsGrow)
		self.formLayout_2.setMargin(0)
		self.formLayout_2.setObjectName(_fromUtf8("formLayout_2"))
		self.label_2 = QtGui.QLabel(self.layoutWidget_2)
		self.label_2.setObjectName(_fromUtf8("label_2"))
		self.formLayout_2.setWidget(0, QtGui.QFormLayout.LabelRole, self.label_2)
		MainWindow.setCentralWidget(self.centralwidget)
		self.menubar = QtGui.QMenuBar(MainWindow)
		self.menubar.setGeometry(QtCore.QRect(0, 0, 580, 25))
		self.menubar.setObjectName(_fromUtf8("menubar"))
		MainWindow.setMenuBar(self.menubar)
		self.statusbar = QtGui.QStatusBar(MainWindow)
		self.statusbar.setObjectName(_fromUtf8("statusbar"))
		MainWindow.setStatusBar(self.statusbar)

		self.retranslateUi(MainWindow)
		QtCore.QMetaObject.connectSlotsByName(MainWindow)

	def retranslateUi(self, MainWindow):
		MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow", None))
		self.pushButton.setText(_translate("MainWindow", "Check trajectory", None))
		self.ESTOP_2.setText(_translate("MainWindow", "Run", None))
		self.ESTOP_3.setText(_translate("MainWindow", "Pause", None))
		self.ESTOP.setText(_translate("MainWindow", "STOP", None))
		self.label.setText(_translate("MainWindow", "Insert x,y,z co-ordinates", None))
		self.xInput.setText(_translate("MainWindow", "x", None))
		self.zInput.setText(_translate("MainWindow", "z", None))
		self.yInput.setText(_translate("MainWindow", "y:", None))
		self.label_2.setText(_translate("MainWindow", "lengths:"+str(dcb.length_list), None))
	def btnstate(self):
		if self.pushButton.isChecked():
			pass
		else:
			goalX, goalY, goalZ = self.xLineEdit.text(), self.yLineEdit.text(), self.zLineEdit.text()
			goalX=float(goalX)
			goalY=float(goalY)
			goalZ=float(goalZ)
	#plt.pause(0.5)
	# time.sleep(2)
			goalPos=(goalX, goalY, goalZ)
			print(goalPos)
			dcb.drawGoal()
			originPos=(dcb.posX,dcb.posY,dcb.posZ)
			num =10
			deltax=(goalPos[0]-originPos[0])/num
			deltay=(goalPos[1]-originPos[1])/num
			deltaz=(goalPos[2]-originPos[2])/num
			for i in range(0,num+1):
				x = deltax*i+originPos[0]
				y = deltay*i+originPos[1]
				z = deltaz*i+originPos[2]
				dcb.setPos(x,y,z)
				dcb.drawGoal()
				print("calc")
				buff = io.BytesIO()
				plt.savefig(buff, format="png")
				buff.seek(1)
				image2 = Image.open(buff)
				qimage = ImageQt(image2)
				pixmap = QtGui.QPixmap.fromImage(qimage)
				
				self.label_pic_2.setPixmap(pixmap)
				self.retranslateUi(MainWindow)
				QApplication.processEvents()
				time.sleep(0.5)
			print(dcb.length_list)


if __name__ == "__main__":
	import sys
	import io 
	dcb = back.DrawCableBot()
	dcb.initializaton()
	dcb.drawNodes()
	dcb.drawLines()
	
	app = QtGui.QApplication(sys.argv)
	qp = QPixmap()
	MainWindow = QtGui.QMainWindow()
	ui = Ui_MainWindow()
	ui.setupUi(MainWindow)
	MainWindow.show()
	sys.exit(app.exec_())


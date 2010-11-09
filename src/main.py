#! /usr/bin/env python
#
import sys
from PyQt4.QtGui import *
from mainwindow import mainwindow
 
a = QApplication(sys.argv)

# Set these parameters and henceforth call QSettings default constructor.
a.setOrganizationName("Unithorpe")
a.setOrganizationDomain("unithorpe.org")
a.setApplicationName("vandelpos")

w = mainwindow() 
 
w.showFullScreen() 
 
sys.exit(a.exec_()) 


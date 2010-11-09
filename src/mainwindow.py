import sys 
from PyQt4.QtGui import *
from PyQt4.QtCore import *

######################
# This class needs:
# * QSettings
# * Signalling block
# * Style sheet handling
######################
class mainwindow(QMainWindow):

	def __init__(self, *args):
		apply(QWidget.__init__, (self,) + args)
		self.quitbutton = QPushButton(self)
		self.quitbutton.setText("Quit now!")
		self.connect(self.quitbutton, SIGNAL("clicked()"),
				self, SLOT("close()"))
		

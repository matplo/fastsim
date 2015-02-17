#!/usr/bin/env python

from widgets import *
from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import (QApplication, QHBoxLayout, QVBoxLayout, QMessageBox, QSlider,
        QWidget, QPushButton)
from PyQt5.QtOpenGL import QGLWidget

from node import *
import nodes as oldNodes

class GLWidgetTest(GLWidget):
    def __init__(self):
        super(GLWidgetTest, self).__init__()
        
    def addGL(self):
        n0 = Node('n0', parent = None)
        #n0.set_scale(1.0)
        n0.set_translation(0, 0.1, -0.3)

        n1 = Node('n1', parent = n0)
        n1.set_translation(0, 0.2, -0.3)
        n2 = Node('n1', parent = n0)
        n2.set_translation(0, 0.3, -0.3)
                
        ax0 = Axes('axes0', parent=n0)
        
        ax1 = Axes('axes1', parent=n0)
        ax1.set_translation(0, 0.1, -0.3)
        
        self.objects.append(n0)
        
        #c = oldNodes.Coords()
        #self.objects.append(c)
        pass
    
if __name__ == '__main__':

    app = QApplication(sys.argv)
    glw = GLWidgetTest()
    window = Window(glw)
    window.setWindowTitle("Test Nodes Qt")
    window.show()
    sys.exit(app.exec_())

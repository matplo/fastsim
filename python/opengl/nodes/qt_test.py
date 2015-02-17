#!/usr/bin/env python

from widgets import *
from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import (QApplication, QHBoxLayout, QVBoxLayout, QMessageBox, QSlider,
        QWidget, QPushButton)
from PyQt5.QtOpenGL import QGLWidget

from node import *
import nodes as oldNodes

import random

class GLWidgetTest(GLWidget):
    def __init__(self):
        super(GLWidgetTest, self).__init__()
        
    def addGL(self):
        n0 = Node('n0', parent = None)
        #n0.set_scale(1.0)
        #n0.set_translation(0, 0.1, -0.3)
        ax0 = Axes('axes0', parent=n0)

        n1 = Node('n1', parent = n0)
        n1.set_translation(0, 0.3, -0.3)
        n1.set_rotation(120,45,30)
        ax1 = Axes('axes1', parent=n1)
                        
        n2 = Node('n2', parent = n1)
        n2.set_translation(0.3, 0.1, 0.4)
        n2.set_rotation(135,0,0)
        ax2 = Axes('axes2', parent=n2)

        na3 = Node('na3', parent = ax2)
        na3.set_translation(0.0, 0.0, -0.4)
        na3.set_rotation(0,0,0)

        na4 = Node('na4', parent = ax2)
        na4.set_translation(0.0, 0.0, -0.5)
        
        na5 = Node('na5', parent = ax2)
        na5.set_translation(0.0, 0.1, -0.5)
                        
        self.objects.append(n0)

        if '--cubes' in sys.argv:
            rcCubes = RandomCubes('rcs', n0)

        if '--old' in sys.argv:
            c = oldNodes.Coords()
            self.objects.append(c)
    
if __name__ == '__main__':

    app = QApplication(sys.argv)
    glw = GLWidgetTest()
    window = Window(glw)
    window.setWindowTitle("Test Nodes Qt")
    window.show()
    sys.exit(app.exec_())

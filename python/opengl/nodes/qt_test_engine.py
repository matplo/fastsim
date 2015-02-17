#!/usr/bin/env python

from widgets import *
from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt, QTimer
from PyQt5.QtGui import QColor, QFont
from PyQt5.QtWidgets import (QApplication, QHBoxLayout, QVBoxLayout, QMessageBox, QSlider,
        QWidget, QPushButton)
from PyQt5.QtOpenGL import QGLWidget

from node import *
import nodes as oldNodes

import random

class GLWidgetTestEngine(GLWidget):
    def __init__(self):
        super(GLWidgetTestEngine, self).__init__()
        self.timer = QTimer()
        #self.timer.setInterval(1)
        self.timer.timeout.connect(self.animate)
        self.timer.start(1)
        self.speedX  = 1
        self.speedY  = 1
        self.speedZ  = 1
        self.npaints = 1
        
    def animate(self):
        angle = self.xRot + self.speedX * random.random()
        self.setXRotation(angle)
        angle = self.yRot + self.speedY * random.random()
        self.setYRotation(angle)
        angle = self.zRot + self.speedZ * random.random()
        self.setZRotation(angle)
        
    def addGL(self):
        n0 = None
        if '--cubes' in sys.argv:
            n0 = Node('n0', None)
            rcCubes = RandomCubes('rcs', n0)
        else:
            n0 = demoNodes()
        self.objects.append(n0)
            
    def addPaintGL(self):
        self.qglColor(Qt.white)
        strx = 'xRot:{0:3d} yRot:{0:3d} zRot:{0:3d} #paints:{0:010}'.format(
            int(self.xRot/16), int(self.yRot/16), int(self.zRot/16), self.npaints)
        #self.renderText(-0.5, 0.5, -10, strx)      
        self.npaints += 1
        font = QFont('White Rabbit')
        font.setPointSize(11)
        self.renderText(-0.45, 0.40, 0, strx, font)
        #font1 = QFont('Menlo')
        #font1.setPointSize(11)
        #self.renderText(-0.45, -1.40, 0, strx, font1)

class GLWidgetTest(GLWidget):
    def __init__(self):
        super(GLWidgetTest, self).__init__()
        
    def addGL(self):
        n0 = demoNodes()
        self.objects.append(n0)

        if '--cubes' in sys.argv:
            rcCubes = RandomCubes('rcs', n0)

        if '--old' in sys.argv:
            c = oldNodes.Coords()
            self.objects.append(c)
    
if __name__ == '__main__':

    app = QApplication(sys.argv)
    #glw = GLWidgetTest()
    glw = GLWidgetTestEngine()    
    window = Window(glw)
    window.setWindowTitle("Test Nodes Qt")
    window.show()
    sys.exit(app.exec_())

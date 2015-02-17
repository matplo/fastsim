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
import math

def randomz(p):
    #return [p[0], p[1], p[2] + math.sin(p[0])]
    return [p[0], p[1], p[2] + random.random() - 0.5]

def sincos(p, scale=1.):
    return [p[0], p[1], p[2] + math.sin(p[0] * p[1] / scale) * scale * 3.]

def sincos_surf(p, scale=1.):
    return [p[0], p[1] + math.sin(p[0]), p[2] + math.sin(p[0]) * math.cos(p[1])]

def sincosc(p, scale=1.):
    p = math.sin(p[0]), math.cos(p[1]), math.sin(p[0] * p[1]), 0.7
    return p

def raf(p):
    #return [p[0], p[1], p[2] + math.sin(p[0])]
    #return [random.random() * 360, random.random(), random.random(), random.random()]
    return [random.random() * 360, random.random() * 360,random.random() * 360]

class GLWidgetTestEngine(GLWidget):
    def __init__(self):
        super(GLWidgetTestEngine, self).__init__()
        self.timer = QTimer()
        #self.timer.setInterval(1)
        self.timer.timeout.connect(self.animate)
        self.accel = 10
        self.speedX  = 1
        self.speedY  = 1
        self.speedZ  = 1
        self.npaints = 1

    def toggleAnimation(self):
        if self.timer.isActive():
            self.timer.stop()
        else:
            self.timer.start(1)            
        
    def animate(self):
        angle = self.xRot + self.speedX * self.accel #random.random()
        self.setXRotation(angle)
        angle = self.yRot + self.speedY * self.accel #random.random()
        self.setYRotation(angle)
        angle = self.zRot + self.speedZ * self.accel #random.random()
        self.setZRotation(angle)
        
    def addGL(self):
        n0 = RootNode('n0')

        if '--axes' in sys.argv:
            ax0 = Axes('axes0', parent=n0)
    
        if '--cubes' in sys.argv:
            rcCubes = RandomCubes('rcs', n0)
            
        if '--demo' in sys.argv:
            n0.add_node(demoNodes())

        if '--wall' in sys.argv:
            #n0 = Wall('wall', None, 100, 100, 5)
            nw = Wall('wall', n0, 2, 2, 20)
            nw.add_option('wire')
            #rcCubes = RandomCubes('rcs', n0)
            nw.t_function(sincos)
            nw.c_function(sincosc)            
            #n0.r_function(raf)
            
        if '--surface' in sys.argv:
            #n0 = Wall('wall', None, 100, 100, 5)
            ns = Surface('surf', n0, 2, 2, 200)
            ns.add_option('wire')
            #rcCubes = RandomCubes('rcs', n0)
            ns.t_function(sincos_surf)
            #ns.c_function(sincosc)            
            #n0.r_function(raf)            
            
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

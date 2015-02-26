#!/usr/bin/env python

# based on Rivebank's PyQt example

import sys
import math

from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt, QRect
from PyQt5.QtGui import QColor, QPainter, QFont, QFontMetrics
from PyQt5.QtWidgets import (QApplication, QHBoxLayout, QVBoxLayout, QMessageBox, QSlider,
        QWidget, QPushButton, QLabel)
from PyQt5.QtOpenGL import QGLWidget

import random

try:
    from OpenGL import GL
except ImportError:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, "OpenGL hellogl",
            "PyOpenGL must be installed to run this example.")
    sys.exit(1)

try:
    from OpenGL import GLU
except ImportError:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, "OpenGL hellogl",
            "GLU missing")
    sys.exit(1)
    
try:
    from OpenGL import GLUT    
except ImportError:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, "OpenGL hellogl",
            "GLUT missing")
    sys.exit(1)

from nodes import *

class Window(QWidget):
    def __init__(self, glw):
        super(Window, self).__init__()        
        self.glWidget = glw

        self.xSlider = self.createSlider()
        self.ySlider = self.createSlider()
        self.zSlider = self.createSlider()

        self.xSlider.valueChanged.connect(self.glWidget.setXRotation)
        self.glWidget.xRotationChanged.connect(self.xSlider.setValue)
        self.ySlider.valueChanged.connect(self.glWidget.setYRotation)
        self.glWidget.yRotationChanged.connect(self.ySlider.setValue)
        self.zSlider.valueChanged.connect(self.glWidget.setZRotation)
        self.glWidget.zRotationChanged.connect(self.zSlider.setValue)

        self.glWidget.xRotationChanged.connect(self.updateInfo)
        self.glWidget.yRotationChanged.connect(self.updateInfo)
        self.glWidget.zRotationChanged.connect(self.updateInfo)                
        
        mainLayout = QHBoxLayout()
        mainLayout.addWidget(self.glWidget)
        mainLayout.addWidget(self.xSlider)
        mainLayout.addWidget(self.ySlider)
        mainLayout.addWidget(self.zSlider)
        vLayout = QVBoxLayout()
        vLayout.addLayout(mainLayout)

        self.infoLabel = QLabel()
        vLayout.addWidget(self.infoLabel)
        self.updateInfo()
        
        self.resetButton = QPushButton("&Reset View", self)
        self.resetButton.clicked.connect(self.resetView)
        vLayout.addWidget(self.resetButton)

        try:        
            self.animateButton = QPushButton("&Animation Toggle", self)
            self.animateButton.clicked.connect(self.glWidget.toggleAnimation)
            vLayout.addWidget(self.animateButton)
        except:
            pass
        
        self.quitButton = QPushButton("&Quit", self)
        self.quitButton.clicked.connect(QApplication.instance().quit)
        vLayout.addWidget(self.quitButton)
        
        self.setLayout(vLayout)
        self.resetView()        
        self.setWindowTitle("Test Nodes")
                
    def createSlider(self):
        slider = QSlider(Qt.Vertical)
        slider.setRange(0, 360 * 16)
        slider.setSingleStep(16)
        slider.setPageStep(15 * 16)
        slider.setTickInterval(15 * 16)
        slider.setTickPosition(QSlider.TicksRight)
        return slider
    
    def resetView(self):
        self.xSlider.setValue(0)
        self.ySlider.setValue(0)
        self.zSlider.setValue(0)

    def updateInfo(self):
        print self.glWidget.xRot, self.glWidget.yRot, self.glWidget.zRot
        strx = 'xRot:{:4.0f} yRot:{:4.0f} zRot:{:4.0f}'.format(
            self.glWidget.xRot/16., self.glWidget.yRot/16., self.glWidget.zRot/16.)
        font = QFont('White Rabbit')
        font.setPointSize(11)
        self.infoLabel.setText(strx)
        
class GLWidget(QGLWidget):
    xRotationChanged = pyqtSignal(int)
    yRotationChanged = pyqtSignal(int)
    zRotationChanged = pyqtSignal(int)

    def __init__(self, parent=None):
        super(GLWidget, self).__init__(parent)
        
        self.objects = []
        self.xRot = 0
        self.yRot = 0
        self.zRot = 0
        self.npaints = 1

        self.lastPos = QPoint()

        self.setAutoBufferSwap(True) #should be True by default
        
    #check this for light and color tracking:
    # http://www.falloutsoftware.com/tutorials/gl/gl8.htm
    def setupLight(self):
        self.light_ambient   = 0.5, 0.5, 0.5, 0.5
        self.light_diffuse   = 0.5, 0.5, 0.5, 0.5 # diffuse light.
        self.light_specular  = 0.5, 0.5, 0.5, 0.5
        self.light0_position = 0.0, 0.0, -20.0, 1.0
        #GL.glLightfv(GL.GL_LIGHT0, GL.GL_AMBIENT,  self.light_ambient);
        #GL.glLightfv(GL.GL_LIGHT0, GL.GL_DIFFUSE,  self.light_diffuse)
        #GL.glLightfv(GL.GL_LIGHT0, GL.GL_SPECULAR, self.light_specular);
        #GL.glLightfv(GL.GL_LIGHT0, GL.GL_POSITION, self.light0_position)
        #GL.glEnable(GL.GL_LIGHT0);
        
        self.global_ambient = 0.9, 0.9, 0.9, 1.0
        GL.glLightModelfv(GL.GL_LIGHT_MODEL_AMBIENT, self.global_ambient);
        
        # Enable a single OpenGL light.
        GL.glEnable(GL.GL_LIGHTING);
        
    def minimumSizeHint(self):
        return QSize(50, 50)

    def sizeHint(self):
        return QSize(400, 400)

    def setXRotation(self, angle):
        angle = self.normalizeAngle(angle)
        if angle != self.xRot:
            self.xRot = angle
            self.xRotationChanged.emit(angle)
            self.updateGL()
        #print 'rotation',self.xRot,self.yRot,self.zRot

    def setYRotation(self, angle):
        angle = self.normalizeAngle(angle)
        if angle != self.yRot:
            self.yRot = angle
            self.yRotationChanged.emit(angle)
            self.updateGL()
        #print 'rotation',self.xRot,self.yRot,self.zRot

    def setZRotation(self, angle):
        print 'z rotation'                
        angle = self.normalizeAngle(angle)
        if angle != self.zRot:
            self.zRot = angle
            self.zRotationChanged.emit(angle)
            self.updateGL()
        #print 'rotation',self.xRot,self.yRot,self.zRot
        
    def initializeGL(self):
        self.makeCurrent()
        GL.glEnable(GL.GL_MULTISAMPLE);
        GL.glClearColor(0,0,0,0)
        self.setupLight()        
        #GL.glShadeModel(GL.GL_FLAT)
        GL.glShadeModel(GL.GL_SMOOTH)

        GL.glEnable(GL.GL_BLEND);
        GL.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA); 
        GL.glShadeModel(GL.GL_SMOOTH); 

        GL.glHint(GL.GL_POLYGON_SMOOTH_HINT, GL.GL_FASTEST); 
        GL.glEnable(GL.GL_POLYGON_SMOOTH);

        GL.glEnable( GL.GL_ALPHA_TEST );
                
        GL.glEnable(GL.GL_DEPTH_TEST)
        #GL.glDisable(GL.GL_DEPTH_TEST); 
        GL.glEnable(GL.GL_CULL_FACE)
        GL.glEnable(GL.GL_MULTISAMPLE)        
        # Accept fragment if it closer to the camera than the former one
        GL.glDepthFunc(GL.GL_LESS);
        #/* Setup the view of the cube. */
        GL.glMatrixMode(GL.GL_PROJECTION);
        #GLU.gluPerspective( 90.0,   #/* field of view in degree */ 
        #                    1.0,   #/* aspect ratio */ 
        #                    1.0,   #/* Z near */ 
        #                    10.0); #/* Z far */
        
        GL.glMatrixMode(GL.GL_MODELVIEW);
        #GLU.gluLookAt(0.0, 0.0, -10.0,  #/* eye is at (0,0,5) */
        #              0.0, 0.0,  0.0,      #/* center is at (0,0,0) */
        #              0.0, 1.0,  0.);      #/* up is in positive Y direction */
  
        #/* Adjust cube position to be asthetic angle. */
        #GL.glTranslatef(0.0, 0.0, -1.0);
        #GL.glRotatef(60, 1.0, 0.0, 0.0);
        #GL.glRotatef(-20, 0.0, 0.0, 1.0);
        self.addGL()
        
    def drawInstructions(self, text):
        pass
    
    def addGL(self):
        #make all the things...
        self.objects.append(CoordCubes())
        if '--cubes' in sys.argv:
            self.objects.append(RandomCubes())        

    def addPaintGL(self):
        pass
    
    def paintGL(self):
        GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT)
        GL.glLoadIdentity()
        GL.glTranslated(0.0, 0.0, -10.0)
        GL.glRotated(self.xRot / 16., 1.0, 0.0, 0.0)
        GL.glRotated(self.yRot / 16., 0.0, 1.0, 0.0)
        GL.glRotated(self.zRot / 16., 0.0, 0.0, 1.0)
        for o in self.objects:
            o.gl()

        GL.glLoadIdentity()
        GL.glTranslated(-0.5, 0.5, -10.0)
        self.addPaintGL()
        
        if '--rots' in sys.argv:
            GL.glLoadIdentity()            
            GL.glTranslated(-0.5, 0.5, -10.0)
            GL.glRotated(self.xRot / 16.0, 1.0, 0.0, 0.0)        
            #GL.glRotated(self.yRot / 16.0, 0.0, 1.0, 0.0)
            #GL.glRotated(self.zRot / 16.0, 0.0, 0.0, 1.0)        
            for o in self.objects:
                o.gl()
            
            GL.glLoadIdentity()            
            GL.glTranslated(-0.5, -0.5, -10.0)
            #GL.glRotated(self.xRot / 16.0, 1.0, 0.0, 0.0)        
            GL.glRotated(self.yRot / 16.0, 0.0, 1.0, 0.0)
            #GL.glRotated(self.zRot / 16.0, 0.0, 0.0, 1.0)        
            for o in self.objects:
                o.gl()
                
            GL.glLoadIdentity()            
            GL.glTranslated( 0.5, -0.5, -10.0)
            #GL.glRotated(self.xRot / 16.0, 1.0, 0.0, 0.0)
            #GL.glRotated(self.yRot / 16.0, 0.0, 1.0, 0.0)
            GL.glRotated(self.zRot / 16.0, 0.0, 0.0, 1.0)                
            for o in self.objects:
                o.gl()

    def resizeGL(self, width, height):
        side = min(width, height)
        aspect = float(width) / float(height)
        if side < 0:
            return
        GL.glViewport(0, 0, side, side)
        GL.glMatrixMode(GL.GL_PROJECTION)
        GL.glLoadIdentity()
        GL.glOrtho(-1.0 * aspect, +1 * aspect, -1, +1, 1.0, 15.0)        
        GL.glMatrixMode(GL.GL_MODELVIEW)

    def mousePressEvent(self, event):
        self.lastPos = event.pos()

    def mouseMoveEvent(self, event):
        dx = event.x() - self.lastPos.x()
        dy = event.y() - self.lastPos.y()

        if event.buttons() & Qt.LeftButton:
            self.setXRotation(self.xRot + 8 * dy)
            self.setYRotation(self.yRot + 8 * dx)
        elif event.buttons() & Qt.RightButton:
            self.setXRotation(self.xRot + 8 * dy)
            self.setZRotation(self.zRot + 8 * dx)

        self.lastPos = event.pos()
    
    def normalizeAngle(self, angle):
        while angle < 0:
            angle += 360 * 16
        while angle > 360 * 16:
            angle -= 360 * 16
        return angle

if __name__ == '__main__':
    app = QApplication(sys.argv)
    glw = GLWidget()
    window = Window(glw)
    window.show()
    sys.exit(app.exec_())
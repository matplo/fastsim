#!/usr/bin/env python

from widgets import *
from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt, QTimer
from PyQt5.QtGui import QColor
from PyQt5.QtWidgets import (QApplication, QHBoxLayout, QVBoxLayout, QMessageBox, QSlider,
        QWidget, QPushButton, QGraphicsView, QGraphicsScene, QDialog)
from PyQt5.QtOpenGL import QGLWidget

class GrView(QGraphicsView):
    def __init__(self, title):
        super(GrView, self).__init__(title)
    def resizeEvent(self, event):
        if self.scene():
            self.scene.setSceneRect(QRect(QPoint(0,0), event.size()))
        super(GrView, self).resizeEvent(event)

class OpenGLScene(QGraphicsScene):
    def __init__(self):
        super(OpenGLScene, self).__init__()
        self.buttons = QDialog(None, Qt.CustomizeWindowHint | Qt.WindowTitleHint)
        self.buttons.setWindowOpacity(0.8)
        self.buttons.setWindowTitle("Buttons")
        self.buttons.setLayout(QVBoxLayout())
        self.quitButton = QPushButton("&Quit")
        self.quitButton.clicked.connect(QApplication.instance().quit)
        self.buttons.layout().addWidget(self.quitButton)

        print self.items()
                
    def drawBackground(self, painter, rectf):
        QTimer.singleShot(20, self.update)
            
if __name__ == '__main__':

    app = QApplication(sys.argv)
    view = QGraphicsView()
    #view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    glw = QGLWidget()        
    view.setViewport(glw)
    view.setViewportUpdateMode(QGraphicsView.FullViewportUpdate);
    scene = OpenGLScene()
    view.setScene(scene)
    view.show();
    
    view.resize(400,400)
    sys.exit(app.exec_())
    
    #glw = GLWidgetTest()
    glw = GLWidgetTestEngine()    
    window = Window(glw)
    window.setWindowTitle("Test Nodes Qt")
    window.show()

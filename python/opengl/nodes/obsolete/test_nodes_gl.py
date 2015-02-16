#!/usr/bin/env python
from OpenGL import GL
from OpenGL import GLU
from OpenGL import GLUT    
import sys
import time

# angle of rotation for the camera direction
angle = 0.0
# actual vector representing the camera's direction
lx=0.0
lz=-1.0
# XZ position of the camera
x=0.0
z=5.0
# the key states. These variables will be zero
#when no key is being presses
deltaAngle = 0.0
deltaMove = 0

import debug_utils as dbg

def changeSize(w, h):
    dbg.debug('changeSize')
    time.sleep(1)    
    # Prevent a divide by zero, when window is too short
    # (you cant make a window of zero width).
    if h == 0:
        h = 1
    ratio =  w * 1.0 / h

    # Use the Projection Matrix
    GL.glMatrixMode(GL.GL_PROJECTION)
    
    # Reset Matrix
    GL.glLoadIdentity()
    
    # Set the viewport to be the entire window
    GL.glViewport(0, 0, w, h)
    
    # Set the correct perspective.
    GLU.gluPerspective(45.0, ratio, 0.1, 100.0)
    
    # Get Back to the Modelview
    GL.glMatrixMode(GL.GL_MODELVIEW)

def drawSnowMan():
    dbg.debug('drawSnowMan')
    time.sleep(1)
    
    GL.glColor3f(1.0, 1.0, 1.0)

    # Draw Body

    GL.glTranslatef(0.0 ,0.75, 0.0)
    GLUT.glutSolidSphere(0.75,20,20)

    # Draw Head
    GL.glTranslatef(0.0, 1.0, 0.0)
    GLUT.glutSolidSphere(0.25,20,20)

    # Draw Eyes
    GL.glPushMatrix()
    GL.glColor3f(0.0,0.0,0.0)
    GL.glTranslatef(0.05, 0.10, 0.18)
    GLUT.glutSolidSphere(0.05,10,10)
    GL.glTranslatef(-0.1, 0.0, 0.0)
    GLUT.glutSolidSphere(0.05,10,10)
    GL.glPopMatrix()
    
    # Draw Nose
    GL.glColor3f(1.0, 0.5 , 0.5)
    GL.glRotatef(0.0,1.0, 0.0, 0.0)
    GLUT.glutSolidCone(0.08,0.5,10,2)


def computePos(deltaMove):
	x += deltaMove * lx * 0.1
	z += deltaMove * lz * 0.1

def computeDir(deltaAngle):
	angle += deltaAngle
	lx = sin(angle)
	lz = -cos(angle)

def renderScene():
    dbg.debug('renderScene')
    if deltaMove:
        computePos(deltaMove)
        
    if deltaAngle:
        computeDir(deltaAngle)

	# Clear Color and Depth Buffers
	GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT)

	# Reset transformations
	GL.glLoadIdentity()
	# Set the camera
	GLU.gluLookAt(	x, 1.0, z,
                    x+lx, 1.0,  z+lz,
                    0.0, 1.0,  0.0)

    # Draw ground
	#GL.glColor3f(0.9, 0.9, 0.9)
	#GL.glBegin(GL.GL_QUADS)
    #GL.glVertex3f(-100.0, 0.0, -100.0)
    #GL.glVertex3f(-100.0, 0.0,  100.0)
    #GL.glVertex3f( 100.0, 0.0,  100.0)
    #GL.glVertex3f( 100.0, 0.0, -100.0)
    #GL.glEnd()

    # Draw 36 SnowMen
    for i in range(-3, 3):
        for j in range(-3,3):
            GL.glPushMatrix()
            GL.glTranslatef(i*10.0,0,j * 10.0)
            drawSnowMan()
            GL.glPopMatrix()
	GLUT.glutSwapBuffers()

def main():

    # init GLUT and create window
    #glutInit(&argc, argv)
    GLUT.glutInit(len(sys.argv),sys.argv)
    GLUT.glutInitDisplayMode(GLUT.GLUT_DEPTH | GLUT.GLUT_DOUBLE | GLUT.GLUT_RGBA)
    GLUT.glutInitWindowPosition(100,100)
    GLUT.glutInitWindowSize(320,320)
    GLUT.glutCreateWindow("Lighthouse3D - GLUT Tutorial")

    # register callbacks
    GLUT.glutDisplayFunc(renderScene)
    GLUT.glutReshapeFunc(changeSize)
    GLUT.glutIdleFunc(renderScene)

    #GLU.glutSpecialFunc(pressKey)

    # here are the new entries
    #GLUT.glutIgnoreKeyRepeat(1)
    #GLUT.glutSpecialUpFunc(releaseKey)

    # OpenGL init
    GL.glEnable(GL.GL_DEPTH_TEST)

    # enter GLUT event processing cycle
    GLUT.glutMainLoop()

if __name__=='__main__':
    main()

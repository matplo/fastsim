#!/usr/bin/env python

from node import *

import pygame
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

import random
import sys

def demoNodes():
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

    #rcs = RandomCubes('rcs', parent = n0)

    return n0

def main():
    pygame.init()
    display = (800,600)
    pygame.display.set_mode(display, DOUBLEBUF|OPENGL)


    max_distance = 100
    
    gluPerspective(45, (display[0]/display[1]), 0.1, max_distance)

    glTranslatef(random.randrange(-5,5),random.randrange(-5,5), -40)

    n = demoNodes()
    n.set_scale(10.)
    if '--wire' in sys.argv:
        n.add_option('wire', subnodes = True)
    #object_passed = False

    n.dump()

    x_move = 0
    y_move = 0

    #glRotatef(25, 2, 1, 0)

    exit_flag = False

    while exit_flag == False:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x_move = 0.3
                if event.key == pygame.K_RIGHT:
                    x_move = -0.3

                if event.key == pygame.K_UP:
                    y_move = -0.3
                if event.key == pygame.K_DOWN:
                    y_move = 0.3

                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    quit()

            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    x_move = 0

                if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                    y_move = 0

##            if event.type == pygame.MOUSEBUTTONDOWN:
##                if event.button == 4:
##                    glTranslatef(0,0,1.0)
##
##                if event.button == 5:
##                    glTranslatef(0,0,-1.0)
                    

        x = glGetDoublev(GL_MODELVIEW_MATRIX)
  
        camera_x = x[3][0]
        camera_y = x[3][1]
        camera_z = x[3][2]
    
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)

        #glTranslatef(x_move, y_move, 0) #,.50)
        glRotatef(x_move, 1, 0, 0)
        glRotatef(y_move, 0, 1, 0)

        #ground()

        n.gl()

        pygame.display.flip()
        pygame.time.wait(10)

main()
pygame.quit()
quit()

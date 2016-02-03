#!/usr/bin/env python

from node import *

import pygame
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

import random
import sys
import math

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

    return n0

def sinus(x):
    return x[0], x[1], x[2]*x[2]

def main():
    pygame.init()
    psize         = 1000
    display       = (psize, psize)
    screen        = pygame.display.set_mode(display, DOUBLEBUF | OPENGL)

    max_distance  = 1000

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)

    glViewport(0, 0, psize, psize); #glViewport(0, 0, width_of_window_rendering_area, height_of_window_rendering area);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    #gluPerspective(45.0,  (GLfloat)400/400, 0.1, 100); #Sets the frustum to perspective mode, sets up the way in which objects
    gluPerspective(45, (display[0]/display[1]), 0.1, max_distance)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    #gluPerspective(45, (display[0]/display[1]), 0.1, max_distance)

    #glTranslatef(random.randrange(-5,5),random.randrange(-5,5), -40)
    glTranslatef(0, 0, -50)

    n = demoNodes()
    n.set_scale(10.)
    fill = True

    if '--rcs' in sys.argv:
        rcs = RandomCubes('rcs', parent = n)

    if '--wall' in sys.argv:
        wall = Wall('wall', parent = n)

    if '--wire' in sys.argv:
        n.add_option('wire', subnodes = True)

    if '--surf' in sys.argv:
        surface = Surface('surf', parent = n, w = 10, h = 10, igran = 100)
        if '--sin' in sys.argv:
            surface.t_function(sinus)
    n.dump()

    x_move = 0
    y_move = 0
    z_move = 0

    x_move_total = 0
    y_move_total = 0
    z_move_total = 0

    x_rot = 0
    y_rot = 0
    z_rot = 0

    x_rot_total = 0
    y_rot_total = 0
    z_rot_total = 0

    exit_flag = False

    glRotatef(x_rot_total, 1, 0, 0)
    glRotatef(z_rot_total, 0, 0, 1)

    iter = 0

    while exit_flag == False:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if pygame.key.get_mods() & 1024 or pygame.key.get_mods() & 2048:
                sign = +1
            else:
                sign = -1

            if event.type == pygame.KEYDOWN:

                if event.key == pygame.K_LEFT:
                    x_move = 0.3
                if event.key == pygame.K_RIGHT:
                    x_move = -0.3

                if event.key == pygame.K_UP:
                    y_move = -0.3
                if event.key == pygame.K_DOWN:
                    y_move = 0.3

                if event.key == pygame.K_UP:
                    if sign > 0:
                        z_move = 0.3
                if event.key == pygame.K_DOWN:
                    if sign > 0:
                        z_move = -0.3

                if event.key == pygame.K_x:
                    x_rot =  sign * 1.0
                if event.key == pygame.K_y:
                    y_rot = sign * 1.0
                if event.key == pygame.K_z:
                    z_rot = sign * 1.0

                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    quit()

            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    x_move = 0

                if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                    y_move = 0
                    z_move = 0

                if event.key == pygame.K_x:
                    x_rot = 0

                if event.key == pygame.K_y:
                    y_rot = 0

                if event.key == pygame.K_z:
                    z_rot = 0

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
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); #if perspective
        glLoadIdentity();
        gluLookAt(0.0, 0.0, 100.0,  #position
                    0.0, 0.0, 0.0,  #where we are looking
                    0.0, 1.0, 0.0); #up vector

        x_rot_total += x_rot
        y_rot_total += y_rot
        z_rot_total += z_rot

        x_move_total += x_move
        y_move_total += y_move
        z_move_total += z_move

        #glTranslatef(x_move, y_move, z_move) #,.50)
        glTranslatef(x_move_total, y_move_total, z_move_total) #,.50)

        #glRotatef(z_rot, 0, 0, 1)
        glRotatef(z_rot_total, 0, 0, 1)
        #glRotatef(y_rot, 0, 1, 0)
        glRotatef(y_rot_total, 0, 1, 0)
        #glRotatef(x_rot, 1, 0, 0)
        glRotatef(x_rot_total, 1, 0, 0)

        #print 'rotations:',x_rot_total,y_rot_total,z_rot_total
        #ground()

        n.gl()

        if '--rec' in sys.argv:
            fname = 'frame_{}'.format(iter) + '.jpg'
            pygame.image.save(screen, fname)
        iter = iter + 1

        pygame.display.flip()
        pygame.time.wait(10)

main()
pygame.quit()
quit()

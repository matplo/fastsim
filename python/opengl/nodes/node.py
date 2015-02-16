from OpenGL import GL
from OpenGL import GLU
from OpenGL import GLUT    
import random
import math

import debug_utils as dbg

class NodeColor():
    red       = 1.0, 0.0, 0.0, 0.3
    green     = 0.0, 1.0, 0.0, 0.3
    blue      = 0.0, 0.0, 1.0, 0.3
    yellow    = 0.9, 0.9, 0.7, 0.3
    def __init__(self):
        pass

class NodeMaterial():
    spec_refl = 0.8, 0.8, 0.8, 1.0
    def __init__(self):
        pass

class NodeBase(object):
    def __init__(self):
        #dbg.debug()        
        self.t               = (0, 0, 0)
        self.ra              = (0, 0, 0, 0)
        self.color           = NodeColor.yellow
        self.scale           = 1
        self.children        = []
        self.update_requests = []
        self.update = True
        
    def add_node(self, n):
        #dbg.debug()
        self.children.append(n)
        self.update_requests.append(n)        
        self.update = True

    def request_update(self, n):
        self.update_requests.append(n.name)
        
    def set_translation(self, x, y, z):
        self.t = (x, y, z)
        
    def set_rotation(self, ax, ay, az):
        self.ra = (ax, ay, az)

    def set_scale(self, scale):
        if scale >= 0:
            self.scale = scale
            
class Node(NodeBase):
    def __init__(self, name, parent=None):
        super(Node, self).__init__()
        #dbg.debug()
        self.name = name
        self.parent = parent
        if self.parent:
            self.parent.add_node(self)
        self.gl_list = None
        self.update = True
        
    def gl(self):
        #dbg.debug()
        GL.glPushMatrix()
        if self.update:
            self.build_gl_list()
        GL.glCallList(self.gl_list)
        for i in range( len(self.update_requests) ):
            n = self.update_requests.pop()
            n.build_gl_list()
        for n in self.children:
            n.gl()
        GL.glPopMatrix()
        #self.update = False
        #dbg.debug('.')
        
    def build_gl_list(self):
        #dbg.debug('build_gl_list')
        if self.gl_list != None:
            GL.glDeleteLists(self.gl_list, 1)
        self.gl_list = GL.glGenLists(1)        
        GL.glNewList(self.gl_list, GL.GL_COMPILE)
        GL.glPushMatrix()
        GL.glTranslatef(self.t[0], self.t[1], self.t[2])
        GL.glRotatef(self.ra[0], 1, 0, 0)
        GL.glRotatef(self.ra[1], 0, 1, 0)
        GL.glRotatef(self.ra[2], 0, 0, 1)
        GL.glScalef(self.scale, self.scale, self.scale)                
        self.glCode()
        GL.glPopMatrix()        
        GL.glEndList()
        
    def glCode(self):
        #dbg.debug('glCode')
        GL.glLineWidth(1.0);
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.color)
        GLUT.glutWireCube(0.1)
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, NodeColor.red)        
        GLUT.glutWireSphere(0.3, 10, 10)

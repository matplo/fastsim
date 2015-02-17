from OpenGL import GL
from OpenGL import GLU
from OpenGL import GLUT    
import random
import math

import debug_utils as dbg

class NodeColor():
    red       = 1.0, 0.0, 0.0, 0.8
    green     = 0.0, 1.0, 0.0, 0.8
    blue      = 0.0, 0.0, 1.0, 0.8
    yellow    = 0.9, 0.9, 0.5, 0.8
    
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

    def set_color(self, color):
        self.color = color
            
class Node(NodeBase):
    def __init__(self, name, parent=None):
        super(Node, self).__init__()
        #dbg.debug()
        self.name = name
        self.parent = parent
        if self.parent != None:
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
        self.update = False
        #dbg.debug('.')
        
    def build_gl_list(self):
        #dbg.debug('build_gl_list')
        if self.gl_list != None:
            GL.glDeleteLists(self.gl_list, 1)
        self.gl_list = GL.glGenLists(1)        
        GL.glNewList(self.gl_list, GL.GL_COMPILE)
        #GL.glPushMatrix()
        GL.glTranslatef(self.t[0], self.t[1], self.t[2])
        GL.glRotatef(self.ra[0], 1, 0, 0)
        GL.glRotatef(self.ra[1], 0, 1, 0)
        GL.glRotatef(self.ra[2], 0, 0, 1)
        GL.glScalef(self.scale, self.scale, self.scale)                
        self.glCode()
        #GL.glPopMatrix()        
        GL.glEndList()
        
    def glCode(self):
        GL.glLineWidth(1.0);
        GL.glColor3f(self.color[0], self.color[1], self.color[2])
        GL.glMaterialfv(GL.GL_FRONT_AND_BACK, GL.GL_AMBIENT_AND_DIFFUSE, self.color)
        GLUT.glutWireCube(0.1)
        GLUT.glutSolidCube(0.1)        

class Cube(Node):
    def __init__(self, name = 'Cube', parent = None):
        super(Cube, self).__init__(name, parent)
        
    def glCode(self):
        GL.glLineWidth(1.0);
        GL.glColor3f(self.color[0], self.color[1], self.color[2])
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.color)
        #GLUT.glutSolidOctahedron()
        GLUT.glutSolidCube(1.0)

class LSCNode(Node):
    def __init__(self, name = 'LSCNode', parent = None):
        super(LSCNode, self).__init__(name, parent)
    
    def glCode(self):
        #dbg.debug('glCode')
        GL.glLineWidth(2.0);
        GL.glColor3f(self.color[0], self.color[1], self.color[2])
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.color)
        
        #GLUT.glutWireCube(0.5)
        #GLUT.glutWireSphere(0.3, 10, 10)
                
        GLUT.glutSolidCone(0.2, 1.0, 5, 5)

        GL.glRotatef(-self.ra[0], 1, 0, 0)
        GL.glRotatef(-self.ra[1], 0, 1, 0)
        GL.glRotatef(-self.ra[2], 0, 0, 1)
        GL.glBegin(GL.GL_LINES)        
        GL.glVertex3f(0.0, 0.0, 0.0)
        GL.glVertex3f(-self.t[0]/self.scale, -self.t[1]/self.scale, -self.t[2]/self.scale)
        GL.glEnd()
        

class Axes(Node):
    def __init__(self, name = 'Axes', parent = None):
        super(Axes, self).__init__(name, parent)
        nx = LSCNode('nx', self)
        nx.set_color(NodeColor.red)
        nx.set_scale(0.1)
        nx.set_translation(0.2,0,0)
        nx.set_rotation(0, 90, 0)
        ny = LSCNode('ny', self)
        ny.set_color(NodeColor.green)
        ny.set_scale(0.1)
        ny.set_translation(0,0.2,0)        
        ny.set_rotation(270, 0, 0)
        nz = LSCNode('nz', self)
        nz.set_color(NodeColor.blue)
        nz.set_scale(0.1)
        nz.set_translation(0,0,0.2)

class RandomCubes(Node):
    def __init__(self, name='RandomCubes', parent = None):
        super(RandomCubes, self).__init__(name, parent)
        for n in range(0, 500):
            for rn in range(1, 3):
                cuber = Cube('cuber{}'.format(n), self)
                cuber.set_scale(0.01 + random.random() / 10.)
                #r     = 1.-random.random()
                r  = float(rn/10.) * 5.
                rc = 1. - r/3.
                theta = math.pi * 2. * random.random()            
                z     = ( random.random() - 0.5 ) * 2.
                p     = math.sqrt(1-z*z) * math.cos(theta), math.sqrt(1-z*z) * math.sin(theta), z
                cuber.set_translation(r*p[0], r*p[1], r*p[2])
                cuber.set_rotation(360.*random.random(),
                                   360.*random.random(),
                                   360.*random.random())
                cuber.set_color((0.2 + random.random(),
                                 0.2 + random.random(),
                                 0.2 + random.random(),
                                 0.5 + random.random()))
                #cuber.set_color((rc, rc, rc, rc))

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

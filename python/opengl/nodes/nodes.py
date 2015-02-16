from OpenGL import GL
from OpenGL import GLU
from OpenGL import GLUT    
import random
import math

class Node(object):
    red       = 1.0, 0.0, 0.0, 0.3
    green     = 0.0, 1.0, 0.0, 0.3
    blue      = 0.0, 0.0, 1.0, 0.3
    yellow    = 0.9, 0.9, 0.7, 0.3
    spec_refl = 0.8, 0.8, 0.8, 1.0

    def __init__(self, name=None, scale = 1.):
        self.scale = scale
        self.name  = name
        self.translation = (0, 0, 0)
        self.rotation = (0, 0, 0, 0)        
        self.color = self.yellow
        self.nodes = []
        self.gLlist = None

    def set_translation(self, x, y, z):
        self.translation = (x, y, z)
        
    def set_rotation(self, a, x, y, z):
        self.rotation = (a, x, y, z)

    def set_color(self, color):
        self.color = color

    def add_node(self, n):
        self.nodes.append(n)
        self.build_list()
        
    def build_list(self):
        #print self.name,'::_build_list scale = ',self.scale
        #print self.name,'::_build_list gLlist = ',self.gLlist
        if self.gLlist != None:
            GL.glDeleteLists(self.gLlist, 1)
        self.gLlist = GL.glGenLists(1)
        GL.glNewList(self.gLlist, GL.GL_COMPILE)
        #print self.name,'::_build_list translation',self.translation
        self.glCodes()
        GL.glEndList()
        #print self.name,'::_build_list gLlist = ',self.gLlist
            
    def gl(self):
        GL.glPushMatrix()
        if self.gLlist == None:
            self.build_list()            
        ##print self.name,'::_gl gLlist = ',self.gLlist        
        GL.glCallList(self.gLlist)
        GL.glPopMatrix()

    def glCodes(self):
        GL.glPushMatrix()
        #GL.glLoadIdentity()
        GL.glTranslatef(self.translation[0], self.translation[1], self.translation[2])
        GL.glRotatef(self.rotation[0], self.rotation[1], self.rotation[2], self.rotation[3])
        GL.glScalef(self.scale, self.scale, self.scale)                
        self.glCode()
        for n in self.nodes:
            #print self.name,'::build_list',n.name,'::glCode'
            n.glCodes()
        GL.glPopMatrix()
        
    def glCode(self):
        pass
    
class Coords(Node):
    
    def __init__(self, name=None, scale = 1.):
        super(Coords, self).__init__(name, scale)
        if self.name == None:
            self.name = 'Coords'
        
    def glCode(self):
        GL.glLineWidth(2.5); 
        GL.glBegin(GL.GL_LINES)
        
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.red)        
        GL.glColor3f(1.0, 0.0, 0.0)
        GL.glVertex3f(0.0, 0.0, 0.0)
        GL.glVertex3f( 1.0, 0.0, 0.0)
        
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.green)        
        GL.glColor3f(0.0, 1.0, 0.0)        
        GL.glVertex3f(0.0, 0.0, 0.0)
        GL.glVertex3f(0.0,  1.0, 0.0)
        
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.blue)        
        GL.glColor3f(0.0, 0.0, 1.0)        
        GL.glVertex3f(0.0, 0.0, 0.0)
        GL.glVertex3f(0.0, 0.0,  1.0)
        GL.glEnd()

class Cube(Node):
    verts = [
        ( 1.0,  1.0,  1.0),
        ( 1.0, -1.0,  1.0),
        (-1.0, -1.0,  1.0),
        (-1.0,  1.0,  1.0)        
    ]
        
    def __init__(self, name=None, scale = 1.):
        super(Cube, self).__init__(name, scale)
        if self.name == None:
            self.name = 'Cube'

    def square(self, rotation, color=None):
        if color==None:
            color = self.color
        GL.glRotatef(rotation[0],rotation[1],rotation[2],rotation[3])
        GL.glColor4f(0.3, 0.3, 0.3, 0.8)
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, color)
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_SPECULAR, self.spec_refl);               
        GL.glBegin(GL.GL_QUADS)
        for v in self.verts:
            GL.glVertex3d(v[0], v[1], v[2])        
        GL.glEnd()
        
    def glCode(self):
        #print self.name,'::glCode scale:', self.scale
        self.square(rotation=(90,  0.0, 1.0, 0.0))
        self.square(rotation=(180, 0.0, 1.0, 0.0))        
        self.square(rotation=(90,  1.0, 0.0, 0.0))
        self.square(rotation=(180, 1.0, 0.0, 0.0))        
        self.square(rotation=(90,  0.0, 1.0, 0.0))
        self.square(rotation=(180, 0.0, 1.0, 0.0))        

class CoordCube(Cube):
    def __init__(self, name=None, scale = 1.):
        super(Cube, self).__init__(name, scale)
        if self.name == None:
            self.name = 'CoordCube'
            
    def glCode(self):
        #print self.name,'::glCode scale:', self.scale
        self.square(rotation=(90,  0.0, 1.0, 0.0), color=self.red    )
        self.square(rotation=(180, 0.0, 1.0, 0.0), color=self.red    )        
        self.square(rotation=(90,  1.0, 0.0, 0.0), color=self.green  )
        self.square(rotation=(180, 1.0, 0.0, 0.0), color=self.green  )        
        self.square(rotation=(90,  0.0, 1.0, 0.0), color=self.blue   )
        self.square(rotation=(180, 0.0, 1.0, 0.0), color=self.blue   )
        GL.glLineWidth(1.0);
        GL.glMaterialfv(GL.GL_FRONT, GL.GL_AMBIENT_AND_DIFFUSE, self.yellow )
        ws = 3. * self.scale * 100.
        GLUT.glutWireCube(ws) #scaling
        
class CoordCubes(Node):
    def __init__(self, name=None, scale = 1.):
        super(CoordCubes, self).__init__(name, scale)
        if self.name == None:
            self.name = 'CoordCubes'
             
        coords = Coords('coords', scale=0.3)
        self.nodes.append(coords)
        
        cube = CoordCube('cube',scale=0.015)
        cube.set_translation(0,0,0)
        self.nodes.append(cube)
        
        cubeX = CoordCube('cubeX',scale=0.01)
        cubeX.set_translation(0.3,0,0)
        self.nodes.append(cubeX)
        
        cubeY = CoordCube('cubeY',scale=0.01)
        cubeY.set_translation(0,0.3,0)
        self.nodes.append(cubeY)
        
        cubeZ = CoordCube('cubeZ',scale=0.01)
        cubeZ.set_translation(0,0,0.3)
        self.nodes.append(cubeZ)

class RandomCubes(Node):
    def __init__(self, name=None, scale = 1., randomd = 1.):
        super(RandomCubes, self).__init__(name, scale)
        if self.name == None:
            self.name = 'RandomCubes'
        self.randomd = randomd
        for n in range(0, 1000):
            for rn in range(1, 6):
                cuber = Cube('cuber{}'.format(n),scale=0.005)
                #r     = 1.-random.random()
                r  = float(rn/10.) * 3.
                rc = 1. - r/3.
                theta = math.pi * 2. * random.random()            
                z     = ( random.random() - 0.5 ) * 2.
                p     = math.sqrt(1-z*z) * math.cos(theta), math.sqrt(1-z*z) * math.sin(theta), z
                cuber.set_translation(r*p[0], r*p[1], r*p[2])
                cuber.set_rotation(360*random.random(), random.random(), random.random(), random.random())
                #cuber.set_color((random.random(), random.random(), random.random(), random.random()))
                cuber.set_color((rc, rc, rc, rc))
                self.nodes.append(cuber)


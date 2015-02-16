#snip





class World(object):
    def __init__(self, name = None):
        self.scale = 1.
        if name == None:
            self.name  = 'WorldDefault'
        self.translation = (0, 0, 0)
        self.ra = (0, 0, 0, 0)        
        self.nodes  = []
        self.gList  = None
        self.udpate = True
        self.gl_list = None
        self.update_requests = []
        
    def set_translation(self, x, y, z):
        self.t = (x, y, z)
        self.update = True
        
    def set_rotation(self, ax, ay, az):
        self.ra = (ax, ay, az)
        self.update = True
                
    def add_node(self, n):
        self.nodes.append(n)
        self.update = True

    def request_update(self, n):
        self.update_requests.append(n.name)
        
    def render(self):
        dbg.debug()
        if self.update:
            self.build_list()
        dbg.debug("GL.glPushMatrix()")
        dbg.debug("GL.glCallList(self.gl_list)")
        for i in range( len(self.update_requested) ):
            nname = self.update_requests.pop()
            n = self.nodes.find(nname)            
            n.build_list()
            dbg.debug("GL.glCallList(n.gl_list)")
        dbg.debug("GL.glPopMatrix()")
        self.update = False
        
    def build_list(self):
        dbg.debug()        
        if self.gl_list != None:
            dbg.debug("GL.glDeleteLists(self.gl_list, 1)")
        dbg.debug('''
        self.gl_list = GL.glGenLists(1)        
        GL.glNewList(self.gl_list, GL.GL_COMPILE)
        GL.glTranslatef(self.t[0], self.t[1], self.t[2])
        GL.glRotatef(self.ra[0], 1, 0, 0)
        GL.glRotatef(self.ra[1], 0, 1, 0)
        GL.glRotatef(self.ra[2], 0, 0, 1)
        ''')
        for n in self.nodes:
            #print self.name,'::build_list',n.name,'::glCode'
            n.glCodes()
        dbg.debug('''
        GL.glPopMatrix()
        GL.glEndList()''')        

class glNode(object):

    def __init__(self, name, parent):
        self.scale = 1.
        self.name  = name
        self.t = (0, 0, 0)
        self.ra = (0, 0, 0, 0)        
        self.color = NodeColor.yellow
        self.nodes = []
        self.gl_list = None
        self.parent = parent
        self.parent.add_node(self)
        dbg.debug('.')
        
    def set_scale(self, scale):
        self.scale = scale
        self.parent.request_update(self)
        
    def set_translation(self, x, y, z):
        self.t = (x, y, z)
        self.parent.request_update(self)
        
    def set_rotation(self, ax, ay, az):
        self.ra = (ax, ay, az)
        self.parent.request_update(self)
        
    def set_color(self, color):
        self.color = color
        self.parent.request_update(self)
        
    def add_node(self, n):
        self.nodes.append(n)
        self.parent.request_update(self)
        
    def build_list(self):
        #print self.name,'::_build_list scale = ',self.scale
        #print self.name,'::_build_list gl_list = ',self.gl_list
        if self.gl_list != None:
            GL.glDeleteLists(self.gl_list, 1)
        self.gl_list = GL.glGenLists(1)
        GL.glNewList(self.gl_list, GL.GL_COMPILE)
        #print self.name,'::_build_list translation',self.t
        self.glCodes()
        GL.glEndList()
        #print self.name,'::_build_list gl_list = ',self.gl_list
            
    def gl(self):
        GL.glPushMatrix()
        if self.gl_list == None:
            self.build_list()            
        ##print self.name,'::_gl gl_list = ',self.gl_list        
        GL.glCallList(self.gl_list)
        GL.glPopMatrix()

    def glCodes(self):
        GL.glPushMatrix()
        GL.glTranslatef(self.t[0], self.t[1], self.t[2])
        GL.glRotatef(self.ra[0], 1, 0, 0)
        GL.glRotatef(self.ra[1], 0, 1, 0)
        GL.glRotatef(self.ra[2], 0, 0, 1)
        GL.glScalef(self.scale, self.scale, self.scale)                
        self.glCode()
        for n in self.nodes:
            #print self.name,'::build_list',n.name,'::glCode'
            n.glCodes()
        GL.glPopMatrix()
        
    def glCode(self):
        pass

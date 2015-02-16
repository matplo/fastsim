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

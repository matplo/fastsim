#!/usr/bin/env python

import os
import sys
import site

class SitePackages(object):
    def __init__(self, option='load'):
        self.thisdir = os.path.dirname(os.path.realpath(__file__))    
        self.fname = self.thisdir + '/site_packages.info'
        if option == 'load':
            self.load()
        if option == 'write':
            self.write_to_file()
            
    def write_to_file(self):
        self.include_dirs = []
        local_include_dirs = [ '.', 'contents', 'contents/scripts' ]
        for dirname in local_include_dirs:
            self.include_dirs.append(self.thisdir + '/' + dirname)        
        for p in site.getsitepackages():
            self.include_dirs.append(p)
        with open(self.fname, 'w') as f:
            for d in self.include_dirs:
                f.writelines(d + '\n')
        print >> sys.stderr, '[i] written:',self.fname
        
    def load(self):
        with open(self.fname) as f:
            self.include_dirs = [l.strip('\n') for l in f.readlines()]
        for dirname in self.include_dirs:
            sys.path.insert(0, dirname )

def load():
    sp = SitePackages()
    
if __name__=='__main__':
    sp = SitePackages('write')

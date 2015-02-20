#!/usr/bin/env python

from utils.utils import *
from debug_utils.debug_utils import *
from dircrawl.dircrawl import *

class Navbar(object):
    def __init__(self, rootdir):
        self.rootdir = rootdir
        
    def render_link(self, httplink, target):
        link='''
        <li class="dropdown-header">#header#</li>
        <li><a href="#httplink#" target="_blank">#target#</a></li>        
        '''
        #print httplink,'<-',target
        return link.replace('#httplink#', httplink).replace('#target#', target)
    
    def render_header_link(self, header):
        link='''
        <li class="dropdown-header">#header#</li>
        '''
        return link.replace('#header#', header)
    
    def render(self):
        navbar = load_file('./templates/navbar.html',lines=False)
        links = []
        lf = find_files(self.rootdir, '*.links')
        for f in lf:
            ls = load_file(f)
            for l in ls:
                if l[:3] == '#h:':
                    #print 'header line:',l
                    links.append(self.render_header_link(l.strip('#h:')))
                else:
                    try:
                        lnk = l.split('|')[0]
                        tgt = l.split('|')[1]
                        links.append(self.render_link(lnk,tgt))
                    except:
                        pass
        return navbar.replace('#links', '\n'.join(links))
        
class PageBuilder(object):
    def __init__(self, rootdir, roothttp):
        self.rootdir  = rootdir
        self.roothttp = roothttp
        self.navbar   = Navbar(self.rootdir)
        self.sections = DirInfo(self.rootdir)
        #print self.sections.render_as_html()
        
    def render(self):
        idx = load_file('./templates/index.html',lines=False)
        return idx.replace('#navbar',self.navbar.render()).replace('#sections', self.sections.render_as_html())
        
def main():
    #nb = Navbar('./test')
    #print nb.render()
    pb = PageBuilder('/Users/ploskon/devel/sandbox/python/pagebuilder/test', '/')
    print pb.render()
    
if __name__=='__main__':
    main()

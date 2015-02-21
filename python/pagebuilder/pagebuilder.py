#!/usr/bin/env python

from utils.utils import *
from debug_utils.debug_utils import *
from dircrawl.dircrawl import *

class Navbar(object):
    def __init__(self, rootdir):
        self.rootdir = rootdir
        self.template = ''

    def set_template(self, template):
        self.template = load_file(template,lines=False)
        
    def render_link(self, httplink, target):
        link='''
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
        return self.template.replace('#links', '\n'.join(links))
        
class PageBuilder(object):
    def __init__(self, title, rootdir, roothttp):
        self.rootdir  = rootdir
        self.roothttp = roothttp
        self.navbar   = Navbar(self.rootdir)
        self.sections = DirInfo(self.rootdir)
        #print self.sections.render_as_html()
        self.title    = title
        self.template = ''
        self.resources_dir = '/resources'

    def set_resources(self, sdir):
        self.resources_dir = sdir
        
    def set_template(self, template):
        self.template = load_file(template, lines=False)
        
    def set_navbar_template(self, template):
        self.navbar.set_template(template)
        
    def make_title(self, intmpl):
        templ = '''
        <title>#title#</title>
        '''
        return intmpl.replace('#title', templ.replace('#title#', self.title))
    
    def render(self):
        out = self.make_title(self.template)
        out = out.replace('#resources#', self.resources_dir)
        out = out.replace('#navbar',self.navbar.render())
        out = out.replace('#sections', self.sections.render_as_html())
        return out
        
def main():
    #nb = Navbar('./test')
    #print nb.render()
    pb = PageBuilder('Just a test',
                     '/Users/ploskon/devel/sandbox/python/pagebuilder/test',
                     '/')
    pb.set_template('./templates/index.html')
    pb.set_navbar_template('./templates/navbar.html')
    pb.set_resources('./resources/mp/')
    print pb.render()
    
if __name__=='__main__':
    main()

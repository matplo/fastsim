import os
import fnmatch
from flask import render_template
from parse_utils import handle_page_links

class Link(object):
    def __init__(self, target, link, blank = False, users = 'all'):
        self.users  = users
        self.target = target
        self.link   = link
        self.blank  = blank
        #print self.target, self.blank

class LinksGroup(object):
    def __init__(self, name):
        self.links = []
        self.name  = name
    def pop_link(self, link):
        for i,l in enumerate(self.links):
            if l.link == link.link:
                self.links.pop(i)
                return
    def add_link(self, target, link, blank = False, users='all'):
        l = Link(target, link.replace('_',' '), blank, users)
        self.pop_link(l)
        self.links.append(l)        
    def get_links_user(self, user):
        retval = []
        for l in links:
            if user in l.users or 'all' in l.users.lower():
                retval.append(link)
        return retval

class LinksDrop(object):
    def __init__(self, name, navbar=True):
        self.set_navbar(navbar)
        self.groups = []
        self.name   = name
        self.type   = 'btn-default'
    def set_type(self, t):
        self.type = t
    def set_navbar(self, navbar):
        self.navbar = navbar
        self.template = 'links_drop_template.html'
        if navbar == False:
            self.template = 'links_drop_button_template.html'        
    def render(self):
        return render_template(self.template, links = self)
    def get_group(self, name):
        for gr in self.groups:
            if gr.name == name:
                return gr
        return None
    def get_by_name(self, name):
        for gr in self.groups:
            if gr.name == name:
                return gr
        return None
    def add_link(self, group, target, link, blank = False, users = 'all'):
        if self.get_group(group) == None:
            self.groups.append(LinksGroup(group))
            #print 'creating group',group
        gr = self.get_group(group)
        gr.add_link(target, link, blank, users)

class Links(LinksDrop):
    def __init__(self, name):
        super(Links, self).__init__(name)
    def add_link(self, drop, group, target, link, blank = False, users = 'all'):
        if self.get_group(drop) == None:
            self.groups.append(LinksDrop(drop))
            #print 'creating group',drop
        gr = self.get_group(drop)
        gr.add_link(group, target, link, blank, users)
    def pop(self, drop):
        for i,d in enumerate(self.groups):
            if drop.name == d.name:
                self.groups.pop(i)
    def pop_by_name(self, dropname):
        for i,d in enumerate(self.groups):
            if dropname == d.name:
                self.groups.pop(i)
    def replace_drop(self, drop):
        self.pop(drop)
        if len(drop.groups) > 0:
            self.groups.insert(0, drop)
            
    def load_from_file(self, fname):        
        with open(fname) as f:
            lines = f.readlines()
        for l in lines:
            ldata = handle_page_links(l)
            if len(ldata)>0:
                dname = os.path.basename(fname).rsplit('.links')[0].replace('_', ' ')
                #self.pop_by_name(dname) #cannot have two of the same name...
                self.add_link(dname, ldata[0], ldata[1], ldata[2], ldata[3], ldata[4])
                
    def load_from_directory(self, cdir):
        rootdir = cdir
        pattern = '*.links'
        files = [os.path.join(rootdir, filename)
                for rootdir, dirnames, filenames in os.walk(rootdir)
                for filename in filenames
                if fnmatch.fnmatch(filename, pattern)]
        for f in files:
            self.load_from_file(f)

    def drop_all(self):
        self.groups = []


from flask import render_template

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
    def add_link(self, link):
        self.links.append(link)
    def add_link(self, target, link, blank = False, users='all'):
        l = Link(target, link.replace('_',' '), blank, users)
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

from flask import render_template

class Link(object):
    def __init__(self, target, link, blank = False, users = 'all'):
        self.users  = users
        self.target = target
        self.link   = link
        self.blank  = blank
        print self.target, self.blank

class LinksGroup(object):
    def __init__(self, name):
        self.links = []
        self.name  = name
    def add_link(self, link):
        self.links.append(link)
    def add_link(self, target, link, blank = False, users='all'):
        l = Link(target, link, blank, users)
        self.links.append(l)        
    def get_links_user(self, user):
        retval = []
        for l in links:
            if user in l.users or 'all' in l.users.lower():
                retval.append(link)
        return retval

class LinksDrop(object):
    def __init__(self, name):
        self.groups = []
        self.name   = name
    def render(self):
        return render_template('links_drop_template.html', links = self)
    def get_group(self, name):
        for gr in self.groups:
            if gr.name == name:
                return gr
        return None
    def add_link(self, group, target, link, blank = False, users = 'all'):
        if self.get_group(group) == None:
            self.groups.append(LinksGroup(group))
            print 'creating group',group
        gr = self.get_group(group)
        gr.add_link(target, link, blank, users)

class Links(LinksDrop):
    def __init__(self, name):
        super(Links, self).__init__(name)
    def add_link(self, drop, group, target, link, blank = False, users = 'all'):
        if self.get_group(drop) == None:
            self.groups.append(LinksDrop(drop))
            print 'creating group',drop
        gr = self.get_group(drop)
        gr.add_link(group, target, link, blank, users)

#!/usr/bin/env python

from debug_utils.debug_utils import *
import jinja2
import os

class Config(object):
    KEYWORDS = ['---', 'Title:', 'Subtitle:', 'Content:', 'Raw:', 'File.txt:', '...', '- ']
    TEMPLATES = {
        'Section'  : 'section_template.html',
        'Raw:'     : 'section_element_raw.html',
        'image'    : 'section_element_image.html',
        'Content:' : 'section_element_standard.html'}
    def __init__(self, path = os.path.dirname(__file__)):
        self.path = path
        
    def set_path(self, path):
        self.path = path
        
    def template(self, s):
        return self.path + '/' + self.TEMPLATES[s]
            
class Tag(object):
    def __init__(self, key):
        self.key = key
        self.content = []
    def append(self, c):
        self.content.append(c)
    def string(self):
        return '\n'.join(self.content)
    def __repr__(self):
        return self.key

class Section(object):
    def __init__(self, tags, config = Config()):
        self.tconfig  = config
        self.tags     = tags
        self.title    = 'not set'
        self.subtitle = 'not set'
        self.content  = 'not set'
        self.jloader  = jinja2.FileSystemLoader(self.tconfig.path)
        self.jenv     = jinja2.Environment(loader=self.jloader)
        self.process()        

    def pop_tag_key(self, keyname):
        for i,t in enumerate(self.tags):
            if t.key == keyname:
                self.tags.pop(i)
                return t
        return Tag(keyname)
    
    def pop_tag(self):
        if len(self.tags) > 0:
            t = self.tags[0]
            self.tags.pop(0)
            return t
        return None

    def render_element(self, t):
        tvalues = { 'content' : t.string() }
        tmpfile = self.tconfig.template(t.key)
        template = self.jenv.get_template(tmpfile)
        retval = template.render(tvalues)
        #print 'render ele:',t.key,retval
        return retval
    
    def render(self):
        tvalues = { 'section' : self }
        template = self.jenv.get_template(self.tconfig.template('Section'))
        return template.render(tvalues)
    
    def process(self):
        self.title    = self.pop_tag_key('Title:').string()
        self.subtitle = self.pop_tag_key('Subtitle:').string()
        content = []
        for t in self.tags:
            if t.key == 'Content:':
                content.append(self.render_element(t))
            if t.key == 'Raw:':
                content.append(self.render_element(t))
        self.content = ''.join(content)
        
    def __repr__(self):
        return '\n > '.join([self.title,self.subtitle,self.content])

class File(object):
    def __init__(self, stream, config=Config()):
        self.load_stream_to_docs(stream)
        self.config   = config
        self.sections = []
        for d in self.docs:
            self.sections.append(Section(d, self.config))

    def render(self):
        summed = []
        for s in self.sections:
            summed.append(s.render())
        return '\n'.join(summed)
    
    def load_stream_to_docs(self, stream):
        tag = None    
        self.docs = []
        current_doc = []
        for l in stream:
            for k in Config.KEYWORDS:
                if k == l[:len(k)]:
                    if tag:
                        current_doc.append(tag)
                    if k == '- ':
                        key = 'Content:'
                    else:
                        key = k
                    tag = Tag(key)
            if tag:
                if tag.key == '...':
                    self.docs.append(current_doc)
                    current_doc = []
                    tag = None
                    continue
                if tag.key == l[:len(tag.key)]:
                    s = l[len(tag.key):].strip('\n')
                else:
                    s = l.strip('\n')
                if len(s) > 0:
                    tag.append(s)
        if tag:
            current_doc.append(tag)
        if len(current_doc) > 0:
            self.docs.append(current_doc)

def from_file(fname):
    with open(fname) as f:
        stream = f.readlines()
    return File(stream)
    
def main():
    fs = from_file('testinput.txt')
    print fs.render()
    
if __name__ == '__main__':
    main()

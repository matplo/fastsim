#!/usr/bin/env python

from debug_utils.debug_utils import *
import jinja2
import os

class Section(object):
    KEYWORDS = ['---', 'Title:', 'Subtitle:', 'Content:', 'Raw:', 'File.txt:', '...', '- ']
    def __init__(self, tags, template = 'section_template.html'):
        self.template = template
        self.tags     = tags
        self.title    = 'not set'
        self.subtitle = 'not set'
        self.content  = 'not set'
        self.process()
        
        self.jenv = jinja2.Environment(loader=jinja2.FileSystemLoader(os.path.dirname(__file__)))
                    
    def render(self):
        template = self.jenv.get_template(self.template)
        tvalues = { 'section' : self }
        return template.render(tvalues)

    def pop_tag(self, name):
        for i,t in enumerate(self.tags):
            if t.key == name:
                self.tags.pop(i)
                return t
        return None
    
    def process(self):
        t = self.pop_tag('Title:')
        if t != None:
            self.title = ''.join(t.content)
        t = self.pop_tag('Subtitle:')
        if t != None:
            self.subtitle = ''.join(t.content)
        t = self.pop_tag('Content:')
        if t != None:
            self.content = '\n'.join(t.content)

    def __repr__(self):
        return '\n > '.join([self.title,self.subtitle,self.content])
    
class Tag(object):
    def __init__(self, key):
        self.key = key
        self.content = []
    def append(self, c):
        self.content.append(c)
    def __repr__(self):
        return self.key
    
def load_stream_to_docs(stream):
    tag = None    
    docs = []
    current_doc = []
    for l in stream:
        for k in Section.KEYWORDS:
            if k == l[:len(k)]:
                if tag:
                    current_doc.append(tag)
                if k == '- ':
                    key == 'Contents:'
                else:
                    key = k
                tag = Tag(key)
        if tag:
            if tag.key == '...':
                docs.append(current_doc)
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
        docs.append(current_doc)        
    return docs

def load_file(fname):
    with open(fname) as f:
        stream = f.readlines()
    #print stream
    docs = load_stream_to_docs(stream)
    #debug_obj(docs)
    for i,doc in enumerate(docs):
        #print i,doc
        #for tag in doc:
        #    print 'key is:', tag.key, ' | object is:', tag.content
        print '---------'
        s = Section(doc)        
        #print i, s
        print s.render()
            
def main():
    load_file('testinput.txt')
    #s = Section(testin)
    #print
    #print s.render()
    
if __name__ == '__main__':
    main()

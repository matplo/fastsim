#!/usr/bin/env python

from debug_utils.debug_utils import *
import jinja2
import os

class Section(object):
    KEYWORDS = ['---', 'Title:', 'Subtitle:', 'Content:', 'Raw:', 'File.txt:', '- ', '...']
    def __init__(self, doc, template = 'section_template.html'):
        self.template = template
        self.doc      = doc
        self.title    = ''
        self.subtitle = ''
        self.content  = ''

        self.jenv = jinja2.Environment(loader=jinja2.FileSystemLoader(os.path.dirname(__file__)))
                    
    def render(self):
        template = self.jenv.get_template(self.template)
        tvalues = { 'section' : self }
        return template.render(tvalues)

    def process(self):
        self.title    = self.doc['Title']
        self.subtitle = self.doc['Subtitle']
        self.content  = self.doc['Content']
        
class Tag(object):
    def __init__(self, key):
        self.key = key
        self.content = []
        
def load_stream_to_doc(stream):
    tag = None    
    docs = []
    current_doc = []
    for l in stream:
        for k in Section.KEYWORDS:
            if k == l[:len(k)]:
                if tag:
                    current_doc.append(tag)
                tag = Tag(k)
        if tag:
            s = l.lstrip(tag.key)
            if len(s) > 0:
                tag.append(s)
        if tag.key == '...':
            docs.append(current_doc)
            current_doc = []
    if len(current_doc) > 0:
        docs.append(current_doc)        
    return docs

def load_file(fname):
    with open(fname) as f:
        stream = f.readlines()
    print stream
    docs = load_stream_to_doc(stream)
    debug_obj(docs)
    for i,doc in enumerate(docs):
        print i,doc
        for key in doc.keys():
            print 'key is:', key, ' | object is:', doc[key]
        s = Section(doc)
        print s.render()
            
def main():
    load_file('testinput.txt')
    #s = Section(testin)
    #print
    #print s.render()
    
if __name__ == '__main__':
    main()

import os
import sys
import fnmatch

from flask import render_template

class Config(object):
    KEYWORDS = ['---', 'Title:', 'Subtitle:', 'Content:', 'Raw:', 'File.txt:', '...', '>:']
    TEMPLATES = {
        'Section'  : 'section_template.html',
        'Raw:'     : 'section_element_raw.html',
        'image'    : 'section_element_image.html',
        'Content:' : 'section_element_standard.html',
        '>:'       : 'section_element_standard.html'}       
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
    def has_content(self):
        if len(''.join(self.content)) > 0:
            return True
        return False
    def string(self):
        return u'\n'.join(self.content)
    def __repr__(self):
        return self.key

class Section(object):
    def __init__(self, tags, config = Config()):
        self.tconfig  = config
        self.tags     = tags
        self.title    = 'not set'
        self.subtitle = 'not set'
        self.content  = 'not set'
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
        tmpfile  = self.tconfig.template(t.key)
        return render_template(tmpfile, content = t.string())
    
    def render(self):
        tmpfile = self.tconfig.template('Section')
        return render_template(tmpfile, section = self)

    def process(self):
        self.title    = self.pop_tag_key('Title:').string()
        self.subtitle = self.pop_tag_key('Subtitle:').string()
        content = []
        for t in self.tags:
            if t.key == 'Content:' or t.key == '>:':
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
        self.body = self.render()
        
    def render(self):
        summed = []
        for s in self.sections:
            summed.append(s.render())
        return u''.join(summed)
    
    def handle_hrefs(self, s):
        phref   = s.partition('<href:')
        pcol1   = phref[2].partition(':')
        pcol2   = pcol1[2].partition('>')
        target  = pcol1[0]
        link    = pcol2[0]
        old_syn = '<href:{}:{}>'.format(target, link)
        new_syn = '<a href="{}">{}</a>'.format(target, link)
        #new_syn = render_template('section_element_link.html', target=target, link=link)
        news    = s.replace(old_syn, new_syn)
        print old_syn, new_syn        
        retval  = None
        try:
            if len(pcol2[2]) > 0:
                retval = self.handle_hrefs(news)
        except:
            pass
        if retval == None:
            retval = news
        return retval

    def doc_has_entry(self, doc):
        for t in doc:
            if t.has_content():
                return True
        return False
    
    def load_stream_to_docs(self, stream):
        tag = Tag('>:') #tag = None    
        self.docs = []
        current_doc = []
        for l in stream:
            for k in Config.KEYWORDS:
                if k == l[:len(k)]:
                    if tag:
                        current_doc.append(tag)
                    tag = Tag(k)
            if tag:
                if tag.key == '...' or tag.key == '---':
                    if self.doc_has_entry(current_doc):
                        self.docs.append(current_doc)
                    current_doc = []
                    tag = Tag('>:') #tag = None                        
                    continue
                if tag.key == l[:len(tag.key)]:
                    s = l[len(tag.key):].replace('\n', '')
                else:
                    s = l.replace('\n', '')
                if '<href:' in s:
                    s = self.handle_hrefs(s)
                if len(s) > 0:
                    tag.append(s)
        if tag:
            current_doc.append(tag)
        if self.doc_has_entry(current_doc):            
            self.docs.append(current_doc)

def rreplace(s, old, new, occurrence):
    li = s.rsplit(old, occurrence)
    return new.join(li)
    
def lreplace(s, old, new, occurrence):
    li = s.rsplit(old, occurrence)
    return new.join(li)

class Flats(object):
    def __init__(self, rootdir = None):
        self.pages_dir    = rootdir + '/pages'
        #self.template_dir = rootdir + '/templates'
        self.template_dir = ''
        self.config = Config(self.template_dir)
        self.ext = '.flat'
        self.reload()

    def reload(self):
        self.renders = {}
        self.sources = self.find_sources()
        self.paths   = []
        for s in self.sources:
            newp = lreplace(s, self.pages_dir, '', 1)
            newp = rreplace(newp, self.ext, '', 1)
            if newp[0] == '/':
                newp = newp[1:]
            self.paths.append(newp)
            
    def find_sources(self):
        rootdir = self.pages_dir
        pattern = '*' + self.ext
        return [os.path.join(rootdir, filename)
                for rootdir, dirnames, filenames in os.walk(rootdir)
                for filename in filenames
                if fnmatch.fnmatch(filename, pattern)]
    
    def render_file(self, fname):
        with open(fname) as f:
            stream = f.readlines()
        return File(stream, self.config)
        
    def get_rendered(self, path):
        print >> sys.stderr,'request for:',path
        for f in self.paths:
            print >> sys.stderr,'known:',f
        return { 'title' : 'test', 'subtitle' : 'test2', 'body' : 'not much'}
    
    def get(self, path):
        if path in self.paths:
            try:
                p = self.renders[path]
            except KeyError:
                i = self.paths.index(path)
                fname = self.sources[i]
                self.renders[path] = self.render_file(fname)
            p = self.renders[path]
            return p
        return None

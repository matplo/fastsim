#!/usr/bin/env python

from utils.utils import *
from debug_utils.debug_utils import *

class HTMLFragments:
    START_HTML_SECTION = '''
    <div class="well well-sm">
    <div class="page-header">
    <h2>TITLE<small>SUB-TITLE</small></h2>
    </div>
    <div class="well well-sm">'''
    END_HTML_SECTION = '</div></div>'
    PAR_HTML_SECTION = '<p>contents</p>\n'
    VERB_HTML_SECTION='<pre><code class="text">contents</code></pre>\n'
    
class InfoItem(object):
    def __init__(self, fname):
        self.data     = []
        self.fname    = fname
        self.data     = load_file(fname, lines=True)
        self.title    = self.fname
        self.tstamp   = tstamp_file_str(self.fname)
        #debug_obj ( os.stat(self.fname) )
        self.output   = []
        self.process()
        
    def process(self):
        for l in self.data:
            if l[:1] == '#':
                if l[:2] == '#>':
                    ftoload = l.strip('#>')
                    self.output.append('verbatim>' + load_file(ftoload, lines=False))
                else:
                    self.output.append('Section: ' + l[1:])
                if l[:3] == '#v>':
                    ftoload = l.strip('#>')
                    self.output.append(load_file(ftoload, lines=False))
            else:
                self.output.append(l)

    def as_string(self):
        return '\n'.join([l for l in self.output])

    def as_html(self):
        outstr = []
        in_section = False
        for l in self.output:
            if l[:len('Section:')] == 'Section:':
                if in_section == True: #new section is starting...
                    outstr.append(HTMLFragments.END_HTML_SECTION)
                in_section = True
                outstr.append(HTMLFragments.START_HTML_SECTION.replace('SUB-TITLE',self.tstamp).replace('TITLE', l))
                continue
            if l[:len('verbatim>')] == 'verbatim>':
                outstr.append(HTMLFragments.VERB_HTML_SECTION.replace('contents', l.strip('verbatim>')))
                continue
            outstr.append(HTMLFragments.PAR_HTML_SECTION.replace('contents', l))
        if in_section == True: #end the section
            outstr.append(HTMLFragments.END_HTML_SECTION)                
        return ''.join([l for l in outstr])
    
class DirInfo(object):
    def __init__(self, path):
        self.files   = find_files(path, '*.info')
        self.entries = []
        for f in self.files:
            self.entries.append(InfoItem(f))
            
    def _debug(self):
        for e in self.entries:
            debug_obj( e )
            
    def render_as_string(self):
        output = []
        for e in self.entries:
            output.append(e.as_string())
        return ''.join(output)
    
    def render_as_html(self):
        output = []
        for e in self.entries:
            output.append(e.as_html())
        return ''.join([l for l in output])
      
if __name__=='__main__':
    dinfo = DirInfo('.')
    #debug_obj (dinfo)
    #print dinfo.render_as_string()
    print dinfo.render_as_html()

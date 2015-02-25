from flask import render_template
import debug_utils as dbg

class Output(object):
    def __init__(self):
        self.title = ''
        self.subtitle = ''
        self.content = []
        
class Section(Output):
    def __init__(self, page):
        super(Section, self).__init__()
        self.page     = page
        self.title    = page['title']
        self.subtitle = page['subtitle']
        date_str = page['published'].strftime('%Y-%m-%d')
        self.content.append('Page published on:' + date_str)
        self.content.append(page.html)
        self.content.append(self.raw('We need to strip extra tags before rendering page.html'))
        self.content.append(self.raw(dbg.debug_obj_str(self)))
        
    def raw(self, intxt):
        #print >> sys.stderr,render_template('raw_text.html', body=self.body)
        return render_template('raw_text.html', body=intxt)

    def render(self):
        return render_template('flat_section.html', body=self)

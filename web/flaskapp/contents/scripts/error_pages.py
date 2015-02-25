from utils import get_now
from flask import render_template

class ErrorPage(object):
    def __init__(self, e, n):
        self.e = e
        self.n = n
    def render(self):
        if self.n == 401:
            jumbo = { 'head' : 'This is the famous 401... Access denied.', 'text' : 'How did we end up here?' }
            addtxt = {
                'header'  : 'Error #{}'.format(self.n),
                'small'   : get_now(),
                'content' : [str(self.e)]
                }
            return render_template('404.html', jumbo=jumbo, addtxt=addtxt), 401
        if self.n == 404:
            jumbo = { 'head' : 'This is the famous 404...', 'text' : 'How did we end up here?' }
            addtxt = {
                'header'  : 'Error #{}'.format(self.n),
                'small'   : get_now(),
                'content' : [str(self.e)]
                }
            return render_template('404.html', jumbo=jumbo, addtxt=addtxt), 404
        if self.n == 405:
            jumbo = { 'head' : 'This error #405 Method Not Allowed...',
                    'text' : 'How did we end up here?' }
            addtxt = {
                'header'  : 'Error #{}'.format(self.n),
                'small'   : get_now(),
                'content' : [str(self.e)]
                }
            return render_template('404.html', jumbo=jumbo, addtxt=addtxt), 405
        if self.n == 500:
            jumbo = { 'head' : 'This a 500... sorry!', 'text' : 'How did we end up here?' }
            addtxt = {
                'header'  : 'Error #{}'.format(self.n),
                'small'   : get_now(),
                'content' : [str(self.e)]
                }
            return render_template('500.html', jumbo=jumbo, addtxt=addtxt), 500
        
        jumbo = { 'head' : 'This an unknown error... sorry!', 'text' : 'How did we end up here?' }
        addtxt = {
            'header'  : 'Error #{}'.format(self.n),
            'small'   : get_now(),
            'content' : [str(self.e)]
            }
        return render_template('500.html', jumbo=jumbo, addtxt=addtxt), 0

        

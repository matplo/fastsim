from flask import Flask, render_template, request, redirect, session, escape, url_for, flash, g
from flask_bootstrap import Bootstrap
from flask_appconfig import AppConfig
from flask.ext.session import Session

import os
thisdir    = os.path.dirname(os.path.realpath(__file__))    
configfile = thisdir + '/config/default'

app = Flask(__name__)
AppConfig(app, configfile)
Bootstrap(app)
Session(app)

from flask_debugtoolbar import DebugToolbarExtension
app.debug = False # the toolbar is only enabled in debug mode:
app.debug = True  # helps automatic reloading
toolbar = DebugToolbarExtension(app)

from flask_flatpages import FlatPages
pages = FlatPages(app)

from scripts.flats import Flats
fpages = Flats(thisdir)
from scripts.links import Links
gLinks = Links('all')

gNavbar = False
gNavbar = True
def reload_pages():
    fpages.reload()
    gLinks.pop_by_name('Internal Links')    
    for p in fpages.paths:
        if p == 'Not_Found':
            continue
        gLinks.add_link('Internal Links', 'Internal', p, p, False)
    gLinks.get_by_name('Internal Links').set_navbar(gNavbar)
    gLinks.get_by_name('Internal Links').set_type('btn-success')

    gLinks.load_from_directory(thisdir + '/config')
    #gLinks.pop_by_name('External Links')
    #gLinks.get_by_name('External Links').set_navbar(gNavbar)
    #gLinks.get_by_name('External Links').set_type('btn-warning')
    
reload_pages()
    
## preps
@app.before_request
def before_request():
    pass

## routing... catch all from http://flask.pocoo.org/snippets/57/
@app.route('/', defaults = {'path': ''})
@app.route('/<path:path>')
@app.route('/pages/<path>')
def fpage(path=None):
    if path=='Reload_Pages':
        reload_pages()
    if not path:
        path = 'Welcome'
    pf = fpages.get(path)
    if not pf:
        pf = fpages.get('Not_Found')
    pf.links.set_type('btn-primary')
    gLinks.replace_drop(pf.links)
    return render_template('page_template.html', page = pf, links = gLinks)

def page_pages(path=None):
    fpages.get_rendered(path)
    pf = fpages.get(path)
    print pf
    p = pages.get(path)
    if not path:
        p = pages.get('index')
    if not p:
        p = {"title" : "Page not found: /{}".format(path), "body" : "", "html" : ""}
    return render_template('page_template.html', page = p)

if __name__ == '__main__':
    if app.debug == True:
        app.run(debug=True)
    else:
        app.run(debug=False)
    

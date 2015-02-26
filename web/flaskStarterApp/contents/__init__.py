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

import sys
sys.path.insert(0, thisdir + '/contents' )

## preps
@app.before_request
def before_request():
    g.links = []
    for p in pages:
        if 'service/' in p.path:
            continue
        g.links.append({'link':'/pages/' + p.path, 'path' : p.path})

## routing... catch all from http://flask.pocoo.org/snippets/57/
@app.route('/', defaults = {'path': ''})
@app.route('/<path:path>')
@app.route('/pages/<path>')
def page(path=None):
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
    
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
#app.debug = True
toolbar = DebugToolbarExtension(app)

from flask_flatpages import FlatPages
pages = FlatPages(app)

import sys
import datetime as dt

sys.path.insert(0, thisdir + '/contents' )
from scripts import logon_form, gen_pass, geo_ip, userdb
from scripts.page_process import Section
from scripts.utils import now_str

## authentication
def check_auth(username, password):
    return userdb.gUsers.check_passwd(username, password)

from functools import wraps
def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        try:
            session['user'].valid
        except:
            return redirect(url_for('logon'))
        return f(*args, **kwargs)
    return decorated

## preps
@app.before_request
def before_request():
    g.links = []
    for p in pages:
        g.links.append({'link':'/pages/' + p.path, 'path' : p.path})

## routing...
@app.route('/')
def index():
    jumbo = { 'head' : 'Welcome!', 'text' : 'The site is under construction. Come back soon!'}
    return render_template('welcome.html', jumbo=jumbo)

@app.route('/pages/<path>')
@requires_auth
def page(path):
    p = pages.get(path)
    b = Section(p)
    jumbo = { 'head' : path, 'text' : 'Generated from {} characters'.format(len(p.body)) }
    return render_template('flat_index.html', jumbo=jumbo, sections = b.render() )

@app.route('/logon', methods=['GET', 'POST'])
def logon():
    try:
        session.pop('user')
    except:
        pass
    userdb.gUsers.load()
    jumbo = { 'head' : 'Logon page', 'text' : 'No text to add...'}
    form = logon_form.PasswordForm()
    if request.method == 'POST':
        if form.validate_on_submit():
            fentry   = request.form['password']
            try:
                fentries = fentry.split('/')
                if check_auth(fentries[0], fentries[1]):
                    session['user'] = userdb.gUsers.find_user(fentries[0])
                    return redirect(request.args.get("next") or url_for("index"))                
            except:
                pass
            if len(fentry) < 1:
                form.password.errors.insert(0, '...this is not really a password, is it?')                
            else:
                form.password.errors.insert(0, 'unable to authenticate...')
    return render_template('logon.html', jumbo=jumbo, form=form)

@app.route('/logout')
def logout():
    userdb.gUsers.load()    
    try:
        session.pop('user')
    except:
        pass
    return redirect(url_for('index'))

from scripts.error_pages import ErrorPage    
@app.errorhandler(401)
def page_not_found(e):
    return ErrorPage(e,401).render()

@app.errorhandler(404)
def page_not_found(e):
    return ErrorPage(e,404).render()

@app.errorhandler(405)
def page_not_found(e):
    return ErrorPage(e,405).render()

@app.errorhandler(500)
def error_page(e):
    return ErrorPage(e,500).render()

@app.route('/geo')
def geo():
    remoteip = request.remote_addr
    iptext = geo_ip.info(remoteip)
    if remoteip == '127.0.0.1':
        remoteip = geo_ip.public_ip()
        iptext += ' but your public ip is: ' + geo_ip.info(remoteip)
    jumbo = { 'head' : 'Checking your location...', 
              'text' : 'Your ip shows: {}'.format(iptext)}
    return render_template('geo.html', jumbo=jumbo, title='ploskon.com/geo')

@app.route('/test')
@requires_auth
def test():
    return render_template('test.html')

@app.route('/img')
@app.route('/img/<var>')
def img(var=''):
    basename = thisdir + '/static/img/'
    fname    = basename + var
    retval = 'No Image'
    try:
        with open(fname) as f:
            retval = f.read()
    except:
        retval = 'Unable to read from: {}'.format(fname)
    return retval

@app.route('/data')
@app.route('/data/<var>')
def data(var=''):
    basename = thisdir + '/static/data/'
    fname = basename + var
    lines = '[ {"data" : "xx"} ]'.replace('xx',fname.replace(basename, ''))
    try:
        with open(fname) as f:
            lines = f.read()
    except:
        pass
    return lines

@app.route('/query')
@app.route('/query/<var>')
def query(var=''):
    retval = '[]'
    if var == 'time':
        t = dt.datetime.now()
        mins = str(t.minute)
        hs   = str(t.hour)
        retval = '[ {"h" : "xh", "m" : "xm"}]'.replace('xh', hs).replace('xm',mins)
    return retval

if __name__ == '__main__':
    if app.debug == True:
        app.run(debug=True)
    else:
        app.run(debug=False)
    

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
# the toolbar is only enabled in debug mode:
app.debug = False
#app.debug = True
toolbar = DebugToolbarExtension(app)

from flask_flatpages import FlatPages
pages = FlatPages(app)
    
## authentication
from functools import wraps
from flask import Response

import sys
sys.path.insert(0, thisdir + '/contents' )
from scripts import logon_form, gen_pass, geo_ip, userdb

def check_auth(username, password):
    return userdb.gUsers.check_passwd(username, password)

def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        try:
            session['user'].valid
        except:
            return redirect(url_for('logon'))
        return f(*args, **kwargs)
    return decorated

import datetime as dt
def now_str():
    t = dt.datetime.now()
    mins = str(t.minute)
    hs   = str(t.hour)
    return '{} : {}'.format(hs, mins)

## preps
@app.before_request
def before_request():
    g.links = pages

## routing...

@app.route('/')
def index():
    #import form_cuts
    #form = form_cuts.ExampleForm()
    #form.validate_on_submit() #to get error messages to the browser
    jumbo = { 'head' : 'Welcome!', 'text' : 'The site is under construction. Come back soon!'}
    #return render_template('index.html', jumbo=jumbo)
    return render_template('welcome.html', jumbo=jumbo)

@app.route('/pages/<path>')
def page(path):
    jumbo = { 'head' : 'Welcome!', 'text' : 'The site is under construction. Come back soon!'}
    #ps = (p for p in pages if 'published' in p.meta)
    p = pages.get(path)
    addtxt = { 'header'  : p['title'],
               'small'   : p['subtitle'],
               'content' : [p.body] }               
    #               'content' : [p.html] }
    return render_template('page_template.html', jumbo=jumbo,addtxt=addtxt)

@app.route('/logon', methods=['GET', 'POST'])
def logon():
    try:
        session.pop('user')
    except:
        pass
    jumbo = { 'head' : 'Logon page', 'text' : 'No text to add...'}
    form = logon_form.PasswordForm()
    if request.method == 'POST':
        if form.validate():
            fentry   = request.form['password']
            try:
                fentries = fentry.split('/')
                if check_auth(fentries[0], fentries[1]):
                    session['user'] = userdb.gUsers.find_user(fentries[0])
                    return redirect(url_for('index'))
            except:
                pass
            if len(fentry) < 1:
                form.password.errors.insert(0, '...this is not really a password, is it?')                
            else:
                form.password.errors.insert(0, 'unable to authenticate...')
    return render_template('logon.html', jumbo=jumbo, form=form)

@app.route('/logout')
def logout():
    try:
        session.pop('user')
    except:
        pass
    return redirect(url_for('index'))
    
@app.errorhandler(401)
def page_not_found(e):
    jumbo = { 'head' : 'This is the famous 401... Access denied.', 'text' : 'How did we end up here?' }
    addtxt = {
        'header'  : 'Error content',
        'small'   : now_str(),
        'content' : [str(e)]
        }
    return render_template('404.html', jumbo=jumbo, addtxt=addtxt), 401

@app.errorhandler(404)
def page_not_found(e):
    jumbo = { 'head' : 'This is the famous 404...', 'text' : 'How did we end up here?' }
    addtxt = {
        'header'  : 'Error content',
        'small'   : now_str(),
        'content' : [str(e)]
        }
    return render_template('404.html', jumbo=jumbo, addtxt=addtxt), 404

@app.errorhandler(405)
def page_not_found(e):
    jumbo = { 'head' : 'This error #405 Method Not Allowed...',
              'text' : 'How did we end up here?' }
    addtxt = {
        'header'  : 'Error content',
        'small'   : now_str(),
        'content' : [str(e)]
        }
    return render_template('404.html', jumbo=jumbo, addtxt=addtxt), 405

@app.errorhandler(500)
def error_page(e):
    jumbo = { 'head' : 'This a 500... sorry!', 'text' : 'How did we end up here?' }
    addtxt = {
        'header'  : 'Error content',
        'small'   : now_str(),
        'content' : [str(e)]
        }
    return render_template('500.html', jumbo=jumbo, addtxt=addtxt), 500
    #return error_log(), 500

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
    basedir = os.path.abspath(os.path.dirname(__file__))
    basename = basedir + '/static/img/'
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
    basedir = os.path.abspath(os.path.dirname(__file__))
    basename = basedir + '/static/data/'
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

## errors / logs
import datetime
def log(eid):
    logfileread = []
    with open('./{}.log'.format(eid)) as f:
        logfileread = f.readlines()    
    for i in range(len(logfileread)):
        l = logfileread[i]
        l = '<td style="word-wrap: break-word;min-width: 160px;max-width: 160px;"><h7>' + l + '</h7></td>'
        logfileread[i] = l
    logfileread.reverse()
    #nowtx = datetime.datetime.now().strftime('%Y-%m-%d Time: %H:%M:%S %Z')
    nowtx = datetime.datetime.now().strftime('%c')
    headtx = { 'head' : 'This is the {} log...'.format(eid), 'text' : nowtx }
    if len(logfileread) < 1:
        logfileread.append('No entries.')
    return render_template('index.html', jumbo=headtx, addtxt=logfileread,
                           title='ploskon.com '+eid+' log', isTable=True)
    #, isTable="yes")
    #return render_template('500.html', jumbo=headtx, addtxt=logfileread)    

@app.route('/errlog')
@requires_auth
def error_log():
    return log('error')

## logs
@app.route('/accesslog')
@requires_auth
def access_log():
    return log('access')

if __name__ == '__main__':
    if app.debug == True:
        app.run(debug=True)
    else:
        app.run(debug=False)
    

from flask import Flask, render_template, request
from flask_bootstrap import Bootstrap
from flask_appconfig import AppConfig

import os
configfile=os.path.dirname(__file__) + '/config/default'

app = Flask(__name__)
AppConfig(app, configfile)  # Flask-Appconfig is not necessary, but
# highly recommend =)
# https://github.com/mbr/flask-appconfig
Bootstrap(app)

from flask_debugtoolbar import DebugToolbarExtension
# the toolbar is only enabled in debug mode:
# app.debug = True
app.debug = False
toolbar = DebugToolbarExtension(app)

## authentication
from functools import wraps
from flask import Response

#import sys
#sys.path.insert(0,"/var/www/ploskon.com/FlaskApp/scripts")
import genPass
import os
def check_auth(username, password):
    """This function is called to check if a username /
    password combination is valid.
    """
    basedir = os.path.abspath(os.path.dirname(__file__))
    fname = basedir+'/hash/'+username+'.hash'
    return genPass.check_pass(password, fname)
    #return username == 'ploskon' and password == 'mateusz'

def authenticate():
    """Sends a 401 response that enables basic auth"""
    return Response(
    'Could not verify your access level for that URL.\n'
    'You have to login with proper credentials', 401,
    {'WWW-Authenticate': 'Basic realm="Login Required"'})

def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        auth = request.authorization
        if not auth or not check_auth(auth.username, auth.password):
            return authenticate()
        return f(*args, **kwargs)
    return decorated

## routing...

@app.route('/')
def index():
    #import form_cuts
    #form = form_cuts.ExampleForm()
    #form.validate_on_submit() #to get error messages to the browser
    jumbo = { 'head' : 'Welcome!', 'text' : 'The site is under construction. Come back soon!'}
    #return render_template('index.html', jumbo=jumbo)
    return render_template('welcome.html', jumbo=jumbo, plotData='/data/access.json')

@app.errorhandler(404)
def page_not_found(e):
    jumbo = { 'head' : 'This is the famous 404...', 'text' : 'How did we end up here?' }
    return render_template('404.html', jumbo=jumbo), 404

@app.errorhandler(500)
def error_page(e):
    jumbo = { 'head' : 'This a 500... sorry!', 'text' : 'How did we end up here?' }
    return render_template('500.html', jumbo=jumbo), 500
    #return error_log(), 500

@app.route('/geo')
def geo():
    remoteip = request.remote_addr
    import geo
    iptext = geo.geo(remoteip)
    jumbo = { 'head' : 'Checking your location...', 'text' : 'Your ip shows : {}'.format(iptext)}
    return render_template('geo.html', jumbo=jumbo, title='ploskon.com/geo')

@app.route('/test')
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
    import datetime as dt
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
    

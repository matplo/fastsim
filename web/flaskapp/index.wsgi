#!/opt/local/bin/python
import os
import sys
import logging
import site

thisdir = os.path.dirname(os.path.realpath(__file__))

#load what needs to be loaded
sys.path.insert(0, thisdir )
import site_packages
site_packages.load()

logdir  = thisdir + '/logs'
if not os.path.exists(logdir):
    os.makedirs(logdir)
logfile = logdir + '/debug-{}.log'.format(os.getpid())
FORMAT = '%(asctime)-15s %(message)s'
logging.basicConfig(filename=logfile, filemode='w', level=logging.DEBUG, stream=sys.stderr, format=FORMAT)
logging.debug( 'Log start.' )
logging.debug( 'This dir:' + thisdir )
logging.debug( sys.path )

# Change to the directory this file is located in
try:
    os.chdir( os.path.dirname(__file__) )
except:
    pass

from contents import app as application

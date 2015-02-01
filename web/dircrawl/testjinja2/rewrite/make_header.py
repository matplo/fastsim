#!/usr/bin/env python

import sys
import utils
from jinja2 import Template
    
if __name__=='__main__':
    utils.set_debug()        
    f_template      = 'templates/header.html'
    f_desc          = 'header.desc'
    result = utils.render(f_template, f_desc)
    #utils.debug(1, 'result:', result)
    print result

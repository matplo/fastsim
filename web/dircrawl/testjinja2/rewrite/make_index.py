#!/usr/bin/env python

import sys
import utils
    
if __name__=='__main__':
    utils.set_debug()        
    f_template      = 'templates/index-proto.html'
    f_desc          = 'index.desc'
    result = utils.render(f_template, f_desc)
    #utils.debug(1, 'result:', result)
    print result

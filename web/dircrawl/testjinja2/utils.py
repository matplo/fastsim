#!/usr/bin/env python

import sys

gDebug=1e6

def is_arg_set(arg=''):
    for a in sys.argv:
        if a==arg:
            return True
    return False

def get_arg_with(arg=''):
    retval = None
    maxl = len(sys.argv)
    for i in range(0,maxl):
        if sys.argv[i]==arg and i < maxl-1:
            retval=sys.argv[i+1]
    return retval

def set_debug():
    global gDebug
    try:
        gDebug = int(get_arg_with('-d'))
    except:
        if is_arg_set('-d'):
            gDebug = -1
        else:
            gDebug = 1e6
    
def debug(*args):
    global gDebug
    if gDebug > args[0]:
        return
    print '[d]',
    for a in args:
        print a,
    print

def load_file(fname, lines=False):
    retval = []
    try:
        with open(fname, 'r') as f:
            #retval = f.read().splitlines()
            retval = f.read()
    except:
        debug(0, 'failed to load file:', fname)
        pass
    if lines==True:        
        return retval
    else:
        return ''.join(retval)

def load_items(s):
    items = []
    debug(0, '--- string start:',s,':end string.' )
    for ic in range(0, len(s)-1):
        if s[ic] == '{' and s[ic+1] == '{':
            if ic+2 < len(s):
                start_ic = ic #+2
                debug(0, ' found start at: ',start_ic )
                for ic2 in range(0,len(s)-ic-1):
                    if s[start_ic + ic2] == '}' and s[start_ic + ic2 + 1] == '}':
                        stop_ic = start_ic + ic2 + 2 # was + 0
                        debug(0, ' found stop at: ',stop_ic )
                        debug(0, ' the item is: ',s[start_ic:stop_ic] )                        
                        items.append(s[start_ic:stop_ic])
                        break
    debug(0,'--- found items:',items)
    return items

def load_items_file(fname):
    return load_items( load_file(fname) )

def load_pair_items_lines(fname):
    retval = []
    footer_items_l = load_file(fname, lines=True)
    for l in footer_items_l:
        items = load_items(l.strip('\n'))
        foot_l = [ items[0].strip(' '), items[1] ]
        retval.append(foot_l)
    return retval

def load_pair_items(buf, from_file = True):
    retval = []
    items = []
    if from_file == True:
        items = load_items_file(buf)
    else:
        items = load_items(buf)
    for i in range(0, len(items)/2):
        pair = [ items[i*2], items[i*2+1] ]
        retval.append(pair)
    debug(0, 'retval: ', retval)
    return retval

def load_trio_items(fname):
    retval = []
    items = load_items( load_file(fname) )
    for i in range(0, len(items) / 3):
        trio = [ items[i*3], items[i*3+1], items[i*3+2] ]
        retval.append(trio)
    return retval

def replace_file_input_tags(s):
    tag = '#file:'
    retval = s
    for i in range(0, len(s)):
        if s[i:i+len(tag)] == tag:
            fname = s[i+len(tag):len(s)].split('"')[1]
            what = tag+'"'+fname+'"'
            repl = load_file(fname)
            if len(repl) == 0:
                repl = '<!-- WARNING - missing input:' + what + ' -->'
            debug(0, 'replacing:',what,'with',repl)
            retval = retval.replace(what, repl)
    return retval

def replace_pair_wise(pairs, fname):
    s = load_file(fname)
    for p in pairs:
        repl = p[1][2:-2]
        repl = replace_file_input_tags(repl)
        debug(0, 'will replace',p[0], 'with', repl)
        s = s.replace(p[0], repl)
    return s

def replace_pair_wise_copy(pairs, fname):
    retval = []
    s = load_file(fname)
    for p in pairs:
        repl = p[1][2:-2]
        repl = replace_file_input_tags(repl)
        debug(0, 'will replace',p[0], 'with', repl)
        retval.append( s.replace(p[0], repl) )
    return '\n'.join(retval)

def clean_tags(s, f_template):
    tags = load_items_file(f_template)    
    debug(1, 'things to be replaced in the template:',tags)
    retval = s
    for t in tags:
        retval = retval.replace(t,'')
    return retval

def render(f_template, f_desc):
    repls = f_desc
    if hasattr(repls, '__iter__') == False:
        repls = load_pair_items(f_desc)
    debug(1, 'pair items from description:', repls)
    retval = replace_pair_wise(repls, f_template)        
    retval = clean_tags(retval, f_template)
    return retval

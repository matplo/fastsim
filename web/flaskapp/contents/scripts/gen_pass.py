#!/usr/bin/env python

import sys
from flask.ext.bcrypt import generate_password_hash
from flask.ext.bcrypt import check_password_hash

def check_pass(passw, fname):
    pw_hash = ''
    try:
        with open(fname, 'r') as f:
            pw_hash = f.read()
    except IOError as e:
        print e
        return False
    return check_password_hash(pw_hash, passw)

def gen_hash(passw, fname):
    pw_hash = generate_password_hash(passw, 10)
    with open(fname, 'w') as f:
        f.write(pw_hash)

def main():
    uname=''
    passw=''
    try:
        uname = sys.argv[1]
        passw = sys.argv[2]
    except:
        print 'usage:',sys.argv[0],'<username> <password>'
        return None
        
    what = 'check'
    try:
        if sys.argv[3] == '-gen':
            what = 'gen'
    except:
        pass

    fname = './'+uname+'.hash'
    
    if what == 'check':
        pass
    if what == 'gen':
        gen_hash(passw, fname)

    if what == 'check':
        print check_pass(passw, fname)

if __name__=="__main__":
    main()

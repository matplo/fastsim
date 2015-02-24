#!/usr/bin/env python

from flask.ext.bcrypt import generate_password_hash
from flask.ext.bcrypt import check_password_hash
from utils import find_files, is_arg_set, get_arg_with

import os
import sys

class Users(object):
    hash_dir = './'
    
    def __init__(self, cdir):
        Users.hash_dir = cdir;
        self.files = find_files(cdir, '*.hash')
        self.users = []
        self.load()
        
    def load(self):
        self.users = []
        for f in self.files:
            u = User(fname=f)
            self.users.append(u)

    def find_user(self, name):
        for u in self.users:
            if u.name == name:
                return u
        return None
    
    def add_user(self, name, passwd):
        u = User(name, passwd)
        u.create()
        self.load()
        if self.find_user(name):
            return True
        return False

    def check_passwd(self, name, passwd):
        u = self.find_user(name)
        if u:
            return check_password_hash(u.pass_hash, passwd)
        return False
    
class User(object):
    def __init__(self, name=None, passwd=None, fname = None):
        self.valid = False
        if fname == None:
            if passwd != None:
                self.pass_hash = generate_password_hash(passwd, 10)
            else:
                self.pass_hash = generate_password_hash('default', 10)
            self.name = name
            if name == None:
                self.name = 'user'
            self.fname = Users.hash_dir + '/' + self.name + '.hash'            
        else:
            self.fname = fname
            self.name = os.path.basename(self.fname).rstrip('.hash')
            if self.load():
                self.valid = True
            else:
                self.valid = False
        self.is_root = self.is_root()

    def create(self):
        if self.write():
            self.valid = True
        else:
            self.valid = False

    def is_root(self):
        if self.name == 'mp':
            return True
        return False

    def write(self):
        try: 
            with open(self.fname, 'w') as f:
                f.write(self.pass_hash)
        except IOError as e:
            print >> sys.stderr,e
            return False
        return True
        
    def load(self):
        try:
            with open(self.fname, 'r') as f:
                self.pass_hash = f.read()
        except IOError as e:
            print >> sys.stderr,e
            return False
        return True

thisdir = os.path.dirname(os.path.realpath(__file__))    
hashdir = thisdir.replace('/scripts', '/hash')
gUsers = Users(hashdir)
#print >> sys.stderr, gUsers.hash_dir, hashdir

def main():
    import debug_utils as dbg
    if is_arg_set('--dump'):
        dbg.debug_obj(gUsers)
        for u in gUsers.users:
            dbg.debug_obj(u)
    uname = get_arg_with('--user')
    passwd = get_arg_with('--passwd')    
    create = is_arg_set('--create')
    if create:
        add = gUsers.add_user(uname, passwd)
        if add == True:
            print >> sys.stderr,'[add ok]'
            print >> sys.stderr,'[new user:]'
            dbg.debug_obj(gUsers.find_user(uname))
        else:
            print >> sys.stderr,'[add failed]'
    else:
        if uname and not passwd:
            dbg.debug_obj(gUsers.find_user(uname))        
        if uname and passwd:
            print >> sys.stderr,'[pass OK?:]',gUsers.check_passwd(uname, passwd)
    
if __name__=="__main__":
    main()

def exists(fname):
    try:
        f = open(fname, 'r')
        f.close()
    except:
        return False
    return True

import sys
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

def not_none(a,b):
    if b == None:
        return a
    return b

import traceback
class Flags:
    debugFlag = False
    
def debug(*msg):
    if Flags.debugFlag == False:
        return
    stack = traceback.extract_stack()
    #print stack[0]
    filename, codeline, funcName, text = stack[-2]
    funcName = '({})'.format(codeline) + ' ' + stack[0][-1]
    #return funcName
    msg_str = []
    if len(msg) == 0:
        msg_str.append('begin')
    else:
        for e in msg:
            msg_str.append(str(e))
    if msg_str[0] == '.':
        msg_str[0] = 'done.'
    if msg_str[0] == '-':
        msg_str[0] = ''
        print '   ',funcName,':',' '.join(msg_str)
    else:
        if msg_str[0] == 'e':
            msg_str.remove(msg_str[0])
            print '[error]',funcName,':',' '.join(msg_str)
        else:
            if msg_str[0] == '|':
                msg_str[0] = ''
                print '[d]',funcName,':\n',''.join(msg_str)
            else:
                print '[d]',funcName,':',' '.join(msg_str)

def debug_obj(obj, msg=' ', truncate=50):
    debug ( '|', msg, type(obj), '\n', Inspector(obj).table_members_basic(truncate=truncate) )
    
    
import inspect
from tabulate import tabulate
class Inspector:

    def __init__(self, a):
        self.a = a
        
    def table_members_basic(self, truncate=50, skip='__'):
        members = inspect.getmembers(self.a)
        retval = [ ['type','name','value'] ]
        for name,value in members:
            if inspect.ismethod(value) == False:
                if skip == '__' and name[0:2] != '__':
                    t = type(getattr(self.a, name))
                    if truncate > 0 and len(str(value)) > truncate:
                        value = str(value)[:truncate]+'...'
                    retval.append([t, name, value])
        return tabulate(retval, headers='firstrow')
    
    def table_members_all(self, skip='__'):
        members = inspect.getmembers(self.a)
        retval = [ ['type','name','value'] ]
        for name,value in members:
            if skip == '__' and name[0:2] != '__':
                t = type(getattr(self.a, name))
                retval.append([t, name, value])
        return tabulate(retval, headers='firstrow')

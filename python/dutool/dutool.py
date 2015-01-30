#!/usr/bin/env python

import sys
import os

class DuEntry:
    def __init__(self, s):
        self.string = s
        self.valid  = False
        self.w      = -1
        self.depth  = 1e3
        if 'Permission denied' in s:
            return
        self.ssize = s.split('\t')[0]
        self.size = 0
        try:
            self.size = float(self.ssize.strip('M').strip('K').strip('T').strip('G'))
        except:
            pass
        self.dir = ''
        try:
            self.dir  = s.split('\t')[1]
        except:
            return
        if 'T' in self.ssize:
            self.w = self.size * 1e12
        if 'G' in self.ssize:
            self.w = self.size * 1e9
        if 'M' in self.ssize:
            self.w = self.size * 1e6
        if 'K' in self.ssize:
            self.w = self.size * 1e3
        self.valid = True
        self.depth = len ( self.dir.split('/') ) - 1
        
    def __repr__(self):
        if self.valid == True:
            #return '{} \t {} \t {}'.format(self.ssize, self.w, self.dir)
            ss = self.ssize
            while len(ss) < 6:
                ss = ' ' + ss
            return '{} {}'.format(ss, self.dir)
        else:
            return self.string

def readlines_file(fname):
    content = None
    guess_ext = os.path.splitext(fname)[1][1:].strip().lower()
    if guess_ext == 'gz':
        try:
            print '[i] open with gzip...'
            import gzip
            with gzip.open(fname, 'r') as f: 
                content = f.readlines()
            print '[i] done.'
        except:            
            content = None
    else:
        try:
            with open(fname,'r') as f:
                content = f.readlines()
        except:
            content = None
    if content == None:
        print '[e] reading from',fname,'failed.'
    return content
        
class DuEntries:
    def __init__(self,entries,fname=''):
        self.fname = fname
        self.entries = entries
        #print '[i] loaded:',len(self.entries),'entries'
        
    @classmethod
    def load_from_file(cls,fname, maxdepth = 4):
        entries = []        
        content = []
        if fname != None:
            content = readlines_file(fname)
            if content == None:
                return None
        else:
            try:
                content = sys.stdin.readlines()
            except:
                print '[e] reading from stdin failed.'
                return None
        print '[i] read',len(content),'lines'
        for c in content:
            if len(c.split('/')) > maxdepth:
                continue
            e = DuEntry(c.strip('\n'))
            if e.valid:
                if e.depth <= maxdepth:                
                    entries.append(e)
        return cls(entries)
            
    def top_n(self, topn=10, depth=2, sdir=''):
        ret_entries = []
        entries_sorted = sorted(self.entries, key=lambda e: e.w, reverse=True)
        indx  = -1
        for e in entries_sorted:
            indx = indx + 1                                
            if e.depth != depth:
                #print '[d] no depth: ask:',depth,'is:',e.depth,'entry:',e                
                continue
            else:
                #print '[d] OK depth: ask:',depth,'is:',e.depth,'entry:',e
                pass
            if sdir != '' and sdir+'/' not in e.string+'/':
                #print '[d] no match',sdir,e.string
                continue
            ret_entries.append(e)
            if len(ret_entries) >= topn:
                break
        return DuEntries(ret_entries)

    def __repr__(self):
        ret = []
        for e in self.entries:
            ret.append(str(self.entries.index(e)) + '\t' + str(e))
        return '\n'.join(ret)

    def print_tree(self, topn=5, d=0, maxdepth=3, sdir='', sep=' |'):
        if maxdepth == 0:
            return
        td = self.top_n(topn, d, sdir)
        for e in td.entries:
            print sep,e
            self.print_tree(topn, d+1, maxdepth-1, e.dir, sep+'------|')

def exists(fname):
    try:
        f = open(fname, 'r')
        f.close()
    except:
        return False
    return True

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

def main():
    
    fname = get_arg_with('-f')
    if fname==None:
        fname = 'projectdu_jan17'

    if exists(fname) == False:
        fname = fname + '.gz'
        
    if exists(fname) == False:
        fname = None

    depth = get_arg_with('-d')
    if depth==None:
        depth = 2 #show more than just the current dir

    depth = int(depth)
    
    topn = get_arg_with('-t')
    if topn == None:
        topn = 5 #this is usually enough
    else:
        try:
            topn = int(topn)
        except:
            topn = 10

    print '[i] setup:',fname,'depth:',depth,'top n:',topn
    
    entries = DuEntries.load_from_file(fname, depth)
    if entries:
        entries.print_tree(topn=topn, maxdepth=depth)
    else:
        entries = DuEntries.load_from_file(fname+'.gz', depth)
        if entries:
            entries.print_tree(topn=topn, maxdepth=depth)            
    
    print '[i] done.'
    
if __name__ == '__main__':
    if sys.version_info < ( 2, 7):
        sys.exit('[i] This script requires Python 2.7. hint: module load python')

    main()

#!/usr/bin/env python

import os
import fnmatch
import sys
import pickle
import datetime
import time

def find_files(rootdir='.', pattern='*'):
    return [os.path.join(rootdir, filename)
            for rootdir, dirnames, filenames in os.walk(rootdir)
            for filename in filenames
            if fnmatch.fnmatch(filename, pattern)]

def get_stats(rootdir='.', pattern='*'):
    lf = find_files(rootdir, pattern)
    stats = []
    for f in lf:
        try:
            st = os.stat(f)
            stats.append({'name': f, 'stats' : st})            
        except OSError as e:
            stats.append({'name': f, 'stats' : e})                        
    return stats

class WatchDirEntry:
    def __init__(self, rootdir, pattern, update = False):
        self.rootdir    = rootdir
        self.pattern    = pattern
        self.stats      = []
        if update == True:
            self.stats = get_stats(self.rootdir, self.pattern)

    def compare(self, o):
        if o == None:
            return False
        if len(self.stats) != len(o.stats):
            return False
        for e in self.stats:
            #print '   :',e['name'],e['stats']            
            found = False
            for x in o.stats:
                #print '   -',x['name'],x['stats']
                if e['stats'] == x['stats']:
                    #print 'same:',e
                    #print '     ',x
                    found = True
            if found==False:
                return False
        return True
        
    def __eq__(self, o):
        return self.compare(o)

    def __repr__(self):
        out = [
            'Root dir:', self.rootdir, '\n',
            'Pattern:',self.pattern, '\n'
            ]
        for e in self.stats:
            out.append(str(e))
            out.append('\n')
        return ''.join(out)
    
class WatchDir:
    def __init__(self, rootdir, pattern='*', cache_dir='./'):
        self.rootdir       = os.path.abspath(rootdir)
        self.pattern       = pattern
        self.stats_current = None
        self.cache_dir     = cache_dir
        self.cache_file    = self.cache_dir + '/' + self.rootdir.replace('/', '_').replace('.','dot') + self.pattern.replace('*', '-star') + '.cache'
        #self.stats_cached  = self.read_cache()
        self.stats_cached  = None

    def get_current(self):
        self.stats_current = WatchDirEntry(self.rootdir, self.pattern, update=True)
                
    def read_cache(self):
        try:
            with open(self.cache_file, 'rb') as f:
                self.stats_cached = pickle.load(f)
        except:
            #print >> sys.stderr, '[w] read cache failed',self.cache_file
            self.stats_cached = None
        return self.stats_cached

    def get_cache_time(self):
        st = '?'
        if self.stats_cached:
            ts = os.stat(self.cache_file).st_mtime
            st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
        return st
    
    def write_cache(self):
        with open(self.cache_file, 'wb') as f:        
            pickle.dump(self.stats_current, f)
        #print >> sys.stderr, '[i] cache written',self.cache_file
        
    def __repr__(self):
        out = [
            '[i] Current: \n', str(self.stats_current),'\n',
            '[i] Cached: \n', str(self.stats_cached),'\n',
            ]
        return ''.join(out)

    def has_changed(self):
        self.read_cache()
        self.get_current()
        if self.stats_current == self.stats_cached:
            return False
        else:
            return True
        
def get_arg_with(arg=''):
    retval = None
    maxl = len(sys.argv)
    for i in range(0,maxl):
        if sys.argv[i]==arg and i < maxl-1:
            retval=sys.argv[i+1]
    return retval

def get_now(form='{}'):
    now = time.time()
    stnow = datetime.datetime.fromtimestamp(now).strftime('%Y-%m-%d %H:%M:%S')
    return form.format(stnow)

def test(rootdir_def = './', pattern_def = '*', cache_dir_def = '/tmp/watchdircache'):
    rootdir =rootdir_def
    try:
        rootdir = sys.argv[1]
    except:
        rootdir = rootdir_def
    pattern = get_arg_with('-p')
    if pattern == None:
        pattern = pattern_def
    cache_dir = get_arg_with('--cachedir')
    if cache_dir == None:
        cache_dir = cache_dir_def
    try:
        os.mkdir(cache_dir)
    except:
        pass

    wd = WatchDir(rootdir, pattern, cache_dir)
    if wd.has_changed():
        print get_now(),':',rootdir,'modified since:', wd.get_cache_time()
        #print '[i] writing cache', wd.cache_file
        wd.write_cache()            
    else:
        if '-d' in sys.argv:
            print >> sys.stderr,get_now(),':',rootdir,'unmodified since:', wd.get_cache_time()
        
    if '--update' in sys.argv or wd.stats_cached == None:
        wd.write_cache()
        
if __name__=='__main__':
    test()

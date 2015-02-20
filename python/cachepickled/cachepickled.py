import os
import datetime
import pickle

class CachePickled(object):
    def __init__(self, fname = None, contents = None):
        self.contents   = contents
        self.cache_file = fname

    def set_cahe(self, fname):
        self.cache_file = fname
        
    def read_cache(self):
        try:
            with open(self.cache_file, 'rb') as f:
                self.contents = pickle.load(f)
        except:
            #print >> sys.stderr, '[w] read cache failed',self.cache_file
            self.contents = None
        return self.contents

    def get_cache_time(self):
        st = '?'
        if self.contents == None:
            self.read_cache()
        if self.contents:
            ts = os.stat(self.cache_file).st_mtime
            st = datetime.datetime.fromtimestamp(ts)
        return st
    
    def get_cache_time_str(self):
        st = '?'
        if self.contents:
            st = self.get_cache_time().strftime('%Y-%m-%d %H:%M:%S')
        return st
    
    def write_cache(self):
        if self.contents != None:
            with open(self.cache_file, 'wb') as f:        
                pickle.dump(self.contents, f)
            #print >> sys.stderr, '[i] cache written',self.cache_file                
        else:
            #print >> sys.stderr, '[i] nothing written: contents is empty'
            pass
        
def write(fname, contents):
    c = CachePickled(fname, contents)
    c.write_cache()
    return c.get_cache_time_str()

def read(fname):
    c = CachePickled(fname)
    return c.read_cache()
    

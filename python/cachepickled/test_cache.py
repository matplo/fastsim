#!/usr/bin/env python

import cachepickled as cache

def main():
    obj = ['ala', 'ma', 'kota']
    fname = 'test.cache'
    print '[i] object  :',str(obj)
    ts = cache.write_to_cache(fname, obj)
    print '[i] written to:',fname,'time stamp:',ts
    r = cache.read_from_cache(fname)
    print '[i] in cache:',r

if __name__=='__main__':
    main()

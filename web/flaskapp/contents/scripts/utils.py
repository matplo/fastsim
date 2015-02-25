import os
import sys
import time
import datetime
import fnmatch

def load_file(fname, lines=True, strip_ch='\n'):
    output = []
    try:
        with open(fname) as f:
            output = [line.rstrip(strip_ch) for line in f.readlines()]
    except:
        print >> sys.stderr,'[w] load_file_lines {} failed.'.format(fname)
    if lines == True:
        return output
    else:
        return '\n'.join(l for l in output)

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

def tstamp_file(fname):
    tstamp = os.stat(fname).st_mtime
    return datetime.datetime.fromtimestamp(tstamp)

def tstamp_file_str(fname):
    return tstamp_file(fname).strftime('%Y-%m-%d %H:%M:%S')
    
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

def get_now(form='{}'):
    now = time.time()
    stnow = datetime.datetime.fromtimestamp(now).strftime('%Y-%m-%d %H:%M:%S')
    return form.format(stnow)

def now_str():
    t = dt.datetime.now()
    mins = str(t.minute)
    hs   = str(t.hour)
    return '{} : {}'.format(hs, mins)

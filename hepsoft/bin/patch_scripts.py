#!/usr/bin/env python

import fnmatch
import os
import sys
import stat

def find_files(rootdir='.', pattern='*'):
    return [os.path.join(rootdir, filename)
            for rootdir, dirnames, filenames in os.walk(rootdir)
            for filename in filenames
            if fnmatch.fnmatch(filename, pattern)]

def get_replacement():
    fn = sys.argv[3]
    retvals = []
    try:
        f = open(fn,'r')
        retvals = f.readlines()
        f.close()
    except:
        print >> sys.stderr,'[e] unable to read:',fn
    return retvals
    
def find_scripts():
    sjdir=sys.argv[1]
    print '[i] looking for scripts in',sjdir
    scripts = find_files(sjdir, '*.sh_template')
    retvals = []
    for s in scripts:
        if ('install.sh' in s) or ('setenv.sh' in s): # or ('job.sh' in s):
            retvals.append(s)
    return retvals
        
def main():
    scripts = find_scripts()
    print '[i] scripts to patch:',scripts
    to_replace = sys.argv[2]
    replacement = get_replacement()
    for s in scripts:
        foutname = s.replace('_template', '')        
        try:
            fin = open(s, 'r')
            clines = fin.readlines()
            fin.close()
            outlines = []
            patched = False                        
            for c in clines:
                if to_replace in c:
                    for outl in replacement:
                        outlines.append(outl)
                    patched = True
                else:
                    outlines.append(c)
            fout = open(foutname, 'w')
            for l in outlines:
                fout.write(l)
            fout.close()
            if patched:
                print '[i] template patched to          :',foutname 
            else:
                print '[i] template copied unchanged to :',foutname
        except:
            print '[w] unable to patch              :',foutname
        try:
            st = os.stat(foutname)
            os.chmod(foutname, st.st_mode | stat.S_IEXEC)
        except:
            print '[w] unable to chmod              : ',foutname
    
if __name__=="__main__":
    main()

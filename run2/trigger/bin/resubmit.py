#!/usr/bin/env python

import fnmatch
import os
import string

import sys

def find_files(rootdir='.', pattern='*'):
    return [os.path.join(rootdir, filename)
            for rootdir, dirnames, filenames in os.walk(rootdir)
            for filename in filenames
            if fnmatch.fnmatch(filename, pattern)]

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

def find_to_resubmit(indir, submit_script, success_file, output):
    nfiles = find_files(indir, submit_script)
    outlist = []
    for fn in nfiles:
        output_file = fn.replace(submit_script, success_file)
        if os.path.isfile(output_file):
            pass
        else:
            #print fn, '# but no', output_file
            outlist.append('{} # but no {}\n'.format(fn, output_file))
    
    for ol in outlist:
        print ol

    try:
        fout = open(output, 'w')
        fout.writelines(outlist)
        fout.close()
    except:
        print >> sys.stderr,'# unable to write to:',output
    
def main():

    indir = get_arg_with('--dir')
    if indir == None:
        indir = '.'

    script = get_arg_with('--script')
    if script == None:
        script = 'submit.sh'

    success_file = get_arg_with('--success-file')
    if success_file == None:
        success_file = 'out.hepmc'

    output = get_arg_with('--output')
    if output == None:
        output = 'resubmit.sh'

    find_to_resubmit(indir, script, success_file, output)
        
if __name__=="__main__":
    main()

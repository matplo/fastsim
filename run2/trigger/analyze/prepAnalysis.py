#!/usr/bin/env python

import os
import sys
import stat
import ROOT
import fnmatch

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

def getFiles(ftxt='hardQCDfiles.txt'):
    files = []
    try:
        with open(ftxt, 'r') as f:
            files = [l.strip() for l in f.read().splitlines(True)]
    except:
        print '[w] unable to read from',ftxt
    return files

def is_out_dir_ok(outdir):
    if not os.path.isdir(outdir):
        os.makedirs(outdir)
    return os.path.isdir(outdir)

def write_script(fname, foutname):
    thisfile = os.path.basename(__file__)
    fsh = foutname + '.sh'
    with open(fsh, 'w') as f:
        print >> f, '#!/bin/bash'
        print >> f, 'date'
        print >> f, 'module load use.own'
        print >> f, 'module load run2trigger'
        print >> f, 'cd {}'.format(os.path.dirname(foutname))
        print >> f, '$RUN2EMCTRIGGER/analyze/{} --in {} --out {} | tee {}.log'.format(thisfile, fname, foutname, foutname)
        print >> f, 'date'
    print '[i] script generated:',fsh
    os.chmod(fsh, stat.S_IRWXU | stat.S_IRWXG | stat.S_IROTH | stat.S_IXOTH)
    return fsh

def write_scripts(infiles=None):
    scripts = []
    if infiles == None:
        print '[i] running with default settings...'
        infiles = ['hardQCDfiles.txt', 'photonfiles.txt']
        subm_script = 'submit_ana.sh'
    else:
        subm_script = 'submit-' + infiles[0] + '.sh'
    for fn in infiles:
        infile = os.path.join(os.getcwd(), fn)
        files  = getFiles(infile)
        outdir = os.path.basename(infile).replace('.txt', '') + '.outputs'
        outdir = os.path.join(os.getcwd(), outdir)
        if not is_out_dir_ok(outdir):
            print '[e] unable to access outdir:',outdir
        else:
            for i,fname in enumerate(files):
                if not os.path.isfile(fname):
                    print '[w] file not found:',fname
                    continue
                foutname = '{}/out-{}.root'.format(outdir, i)
                script = write_script(fname, foutname)
                scripts.append(script)
    if len(scripts) < 1:
        print '[i] no scripts written...'
        return
    with open(subm_script, 'w') as fs:
        for sc in scripts:
            if '--pdsf' in sys.argv:
                print >> fs, 'qsub -P alice -o {} -e {} -m e -M mploskon@lbl.gov {}'.format(os.path.dirname(sc), sc)
            else:
                print >> fs,'qsub -d',os.path.dirname(sc),sc
    print '[i] written:',subm_script
    os.chmod(subm_script, stat.S_IRWXU | stat.S_IRWXG | stat.S_IROTH | stat.S_IXOTH)

def analyze():
    libs = ['libR2Util', 'libAnalyze']
    sdir = os.getenv('RUN2EMCTRIGGER')
    sdir = os.path.join(sdir, 'lib')
    print sdir
    ROOT.gSystem.AddDynamicPath(sdir)
    for l in libs:
        ROOT.gSystem.Load(l)
    fname    = get_arg_with('--in')
    foutname = get_arg_with('--out')
    a = ROOT.Analysis()
    a.AnalyzeFile(fname, foutname, -1)

def main():
    libs = ['libR2Util', 'libAnalyze']
    sdir = os.getenv('RUN2EMCTRIGGER')
    sdir = os.path.join(sdir, 'lib')
    print sdir
    ROOT.gSystem.AddDynamicPath(sdir)
    for l in libs:
        ROOT.gSystem.Load(l)
    nev = 100
    infiles = [ 'hardQCDfiles.txt', 'photonfiles.txt' ]
    for infile in infiles:
        files   = getFiles(infile)
        outdir  = os.path.basename(infile).replace('.txt', '.outputs')
        if not is_out_dir_ok(outdir):
            print '[e] unable to access outdir:',outdir
            return

        for i,fname in enumerate(files):
            if not os.path.isfile(fname):
                print '[w] file not found:',fname
                continue
            foutname = '{}/out-{}.root'.format(outdir, i)
            a = ROOT.Analysis()
            a.AnalyzeFile(fname, foutname, nev)

if __name__ == '__main__':
        if is_arg_set('--dir'):
            cdir = get_arg_with('--dir')
            if cdir==None:
                cdir='<missing arg>'
            sname = get_arg_with('--name')
            if sname == None:
                sname = 'default-out'
            sname = sname + '-list'
            spatt = 'tree-*.root'
            if get_arg_with('--pattern'):
                spatt = get_arg_with('--pattern')
            if os.path.isdir(cdir):
                files = find_files(cdir, spatt)
                if len (files) < 1:
                    print '[i] no files with',spatt,'found...'
                with open(sname,'w') as f:
                    for fn in files:
                        print >> f,fn
                write_scripts([sname])
            else:
                print '[e]',cdir,'is not a dir'
            exit(0)
        if is_arg_set('--in') and is_arg_set('--out'):
            analyze()
        elif is_arg_set('--test'):
            main()
        else:
            write_scripts()

#!/usr/bin/env python

import pyutils as ut
import os
from pprint import pprint as pp

def main(spath='.'):

    valid_outputs = ['default_emctrig_out.root']

    valid_productions = [
            '2.76TeV/hardQCD/mult-0',
            '2.76TeV/photons/mult-0',
            '5TeV/hardQCD/mult-0',
            '5TeV/photons/mult-0'
        ]

    filesets = []
    for v in valid_productions:
        filesets.append([])
    #print filesets
            
    for i,v in enumerate(valid_productions):
        prod_idx = i
        prod_dir = os.path.join(spath, v)
        files    = ut.find_files(prod_dir, '*.root')
        #pp(filesets[prod_idx])        
        for vo in valid_outputs:
            outfname = os.path.join(v, vo).replace('/', '-')
            print '---', outfname,vo
            files_to_merge = []
            for f in files:
                if vo in f:
                    files_to_merge.append(f)
            cmnd = 'hadd -f {} {}'.format(outfname, ' '.join(files_to_merge))
            ut.call_cmnd(cmnd, True)

if __name__=="__main__":
    spath = ut.get_arg_with('--dir')
    if spath != None:
        main(spath)



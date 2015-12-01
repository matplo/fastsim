#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import draw_utils as du
import dlist
import ROOT
import os
import IPython
import math
import sys

import draw_ntuple

kOther=1
kCINT7=2
kEJ1=4
kEG1=8
kDJ1=16
kDG1=32

def get_jets(indir, var='', cuts='', bwidth=10, xlow= 0, xhigh=300):
	print '[i] get_jets:',var
	tu.getTempCanvas().cd()
	ntname = 't'	
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir(indir, ntname, var, cuts, bwidth, xlow, xhigh, 
								title='h', modname='', nev=-1, fpatt='Tree_*.root')
	return hl

def main(dname):
	ls = dlist.ListStorage('jets')

	hl = get_jets(dname, 'jets00.fE', '(trig.type && 4)')
	ls.append(hl)

	ls.draw_all(logy=True)
	ls.pdf()
	#ls.write_all(mod='modn:')

if __name__ == '__main__':
	tu.setup_basic_root()
	envdir = os.getenv('RUN2AESDDIR')
	libs = ['libEMCALTriggerFast', 'libRAnalyzeESD']
	for l in libs:
		lib = os.path.join(envdir, 'lib', l)
		ROOT.gSystem.Load(lib)
	dname = ut.get_arg_with('--in')
	if dname==None:
		dname = './'
	main(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

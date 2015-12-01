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

def get_jets(indir, var='', cuts='', bwidth=10, xlow= 0, xhigh=300):
	print '[i] get_jets:',var
	tu.getTempCanvas().cd()
	tname = 't'	
	refcuts = None
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir_filter(indir, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=-1, thr=5, fpatt='tree-*.root') #nev=10000, thr = 1 * bwidth/2.) #thr was 100!
	return hl

def main(dname):
	hl = get_jets('./', 't.jets00.fE', '(trig.type=0x1)')

if __name__ == '__main__':
	tu.setup_basic_root()
	dname = ut.get_arg_with('--in')
	if dname==None:
		dname = './'
	main(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

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

from array import *

def make_double_arr(n):
	retval = []
	for i in range(n):
		retval.append(0.0)
	return retval

## from REvent.
##"type/D:cent/D:totalE/D:maxjECAL/D:maxjDCAL/D:maxjECAL8x8/D:maxjDCAL8x8/D:maxgECAL/D:maxgDCAL/D:medjECAL/D:medjDCAL/D:medjECAL8x8/D:medjDCAL8x8/D:medgECAL/D:medgDCAL/D");

def main(dname):
	fin = ROOT.TFile(dname)
	t = fin.Get('t')
	tinfo = array('d', make_double_arr(15))
	t.SetBranchAddress('trig', tinfo)

	jets00E = array('d', make_double_arr(1000))
	t.SetBranchAddress('jets00.fE', jets00E)

	##for ev in fin.Get('t'):
	##	print ev.trig
	##	print ev.jets02

	#h = ROOT.TH1F('cent', 'cent', 101, 0, 101)
	h = ROOT.TH2F('centE', 'centE;centrality;jetEnergy', 101, 0, 101, 100, 0, 100)
	for i,ev in enumerate(t):
		t.GetEntry(i)
		#if int(tinfo[0]) & 2 and (int(tinfo[0]) > 1):
		if (int(tinfo[0]) & 2):
			if i % 10000 == 0:
				print i, tinfo
			#for j in ev.jets04:
			for j in ev.maxEjet04:
				h.Fill(tinfo[1], j.E())

	hl = dlist.dlist('cent')
	hl.add(h)
	hl.make_canvas()
	hl.draw()
	hl.self_legend()
	tu.gList.append(hl)

if __name__ == '__main__':
	tu.setup_basic_root()
	envdir = os.getenv('RUN2AESDDIR')
	libs = ['libEMCALTriggerFast', 'libRAnalyzeESD']
	for l in libs:
		lib = os.path.join(envdir, 'lib', l)
		ROOT.gSystem.Load(lib)
	dname = ut.get_arg_with('--in')
	if dname == None:
		dname = 'Tree_AnalysisResults.root'
	main(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

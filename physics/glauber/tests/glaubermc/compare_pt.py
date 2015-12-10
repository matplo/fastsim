#!/usr/bin/env python

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

def get_n_entries(fname):
	if '.txt' in fname:
		hltmp = draw_ntuple.h1d_from_ntuple_flist_file(fname, 't', 'head.xsec', '', bwidth=100, xlow=0, xhigh=1000)
		h = hltmp.sum().obj
	else:
		h = draw_ntuple.h1d_from_ntuple(fname, 't', 'head.xsec', '', bwidth=100, xlow=0, xhigh=1000)
	print 'entries in:',fname,h.GetEntries()
	return h.GetEntries()

def main(files = []):
	if len(files) < 2:
		return

	hl = dlist.dlist('compare_pt')
	#def h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title=None, modname='', nev=-1):
	for fname in files:
		ntname = 't'
		var = 'p.Pt()'
		cuts = 'head.xsec'
		bwidth = 1
		xlow = 0
		xhigh = 100
		title = fname
		if '.txt' in fname:
			print fname, ntname
			hltmp = draw_ntuple.h1d_from_ntuple_flist_file(fname, ntname, var, cuts, bwidth, xlow, xhigh)			
			h = hltmp.sum().obj
		else:
			h = draw_ntuple.h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh)
		h.Scale(1./get_n_entries(fname))
		hl.add(h, fname, 'hist')

	#hls = dlist.ListStorage('E-bias')
	hl.reset_axis_titles('particle pT', 'counts per NN collision')
	hl.make_canvas()
	hl.draw(logy=True)
	ROOT.gPad.SetLogy()
	hl.update()
	hl.self_legend()

	hr = hl.ratio_to()
	hr.make_canvas()
	hr.draw(logy=False, miny=0, maxy=2)
	hr.self_legend()

	hr.reset_axis_titles(None, 'ratio E-conserve / unbiased')

	tu.gList.append(hl)
	tu.gList.append(hr)

if __name__ == '__main__':
	fn1 = ut.get_arg_with('-1')
	if not fn1:
		fn1 = 'output_ncoll_1_1_nStart_0_nEv_1000.root'
	fn2 = ut.get_arg_with('-2')
	if not fn2:
		fn2 = '/data1/glauber/output_ncoll_10_20/flist.txt'
		#'output_ncoll_10_20/output_ncoll_10_20_nStart_0_nEv_100.root']
	files = []
	files.append(fn1)
	files.append(fn2)
	main(files)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

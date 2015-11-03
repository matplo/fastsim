#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math
import sys

import centrality
import tutils as tu
import hnutil

def get_j_pt_bins():
	jptbins = []
	for j in range(1, 10):
		jptbins.append([j*10, j*10 + 10])
	return jptbins

#tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title=None, modname=''):
def get_reoil_yield(fname, tname, uservar=None, usercut='(1)'):
	bwidth = 0.1
	xmax   = 0
	xmin   = ROOT.TMath.Pi() * 2.
	var    = 'abs(dphi)'
	if uservar != None:
		var = uservar
	pTbins = [	[20, 100],
				[40, 100] ]
	hl = dlist.dlist('recoil_jets_{}'.format(fname))
	for ptT in pTbins:
		for jpt in get_j_pt_bins():
			cutT   = '(ptT >= {} && ptT < {})'.format(ptT[0], ptT[1])
			cutTj  = '(jpt >= {} && jpt < {})'.format(jpt[0], jpt[1])
			cut = '({} && {} && {}) * (xsec)'.format(cutT, cutTj, usercut)
			h = tu.draw_h1d_from_ntuple(fname, tname, var, cut, bwidth, xmin, xmax)
			if h == None:
				continue
			htitle = '{} {}'.format(tname, cut)
			hl.add(h, htitle, 'p')
			print '[i]',htitle,h.GetEntries()
	tu.gList.append(hl)
	return hl

def main():
	tu.setup_basic_root()
	fname = tu.get_arg_with('--in')
	if fname == None:
		#fname = 'default-out-list.outputs/out-0.root'
		if '--pho' in sys.argv:
			fname = 'save/pho-mtune1.0-5TeV-list.outputs.root'
		else:
			fname = 'save/qcd-mtune1.0-5TeV-list.outputs.root'
	print fname
	#hl = get_reoil_yield(fname, 'tnpi0jet')
	hl = get_reoil_yield(fname, 'tngjet')
	hl.make_canvas()
	hl.draw()

if __name__ == '__main__':
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

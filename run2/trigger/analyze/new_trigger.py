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
import draw_ntuple

from trigutils import *

def get_entries(fname):
	fin = ROOT.TFile.Open(fname)
	t = fin.Get("t")
	return t.GetEntries()

def get_Ei_median(indir, var='tgEJE.fE-tg.medjDCAL8x8*4', bwidth=1, xlow=-50, xhigh=300):
	print '[i] get_Ei_median:',var
	tu.getTempCanvas().cd()
	tname = 't'
	cuts    = '(xsec)'
	#cuts    = '(1)'
	refcuts = '(1)'
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir_filter(indir, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=-1, thr=100, fpatt='tree-*.root') #nev=10000, thr = 1 * bwidth/2.)
	return hl

def main_patches(X = ''):
	#fname = './test/tree-default_emctrig_out_R_0.4_femcpar_mtune_1.2.root'
	#nentries = get_entries(fname)
	#print '[i] number of entries:', nentries

	ls = dlist.ListStorage('main')
	indir = './test'
	indir = './hardQCD/mtune1.2'

	dvars = [
		'tgXEJE.fE-tgX.medjDCAL8x8*4',
		'tgXEJE8x8.fE-tgX.medjDCAL8x8',
		'tgXDJE8x8.fE-tgX.medjECAL8x8',
		'tgXEGA.fE-tgX.medgDCAL',
		'tgXDGA.fE-tgX.medgECAL'		
	]

	print '[i] main_patches'
	for var in [v.replace('X',X) for v in dvars]:
		print '    main_patches:',var
		hl = get_Ei_median(indir, var)
		ls.append(hl)

	ls.draw_all(logy=True)
	ls.pdf()
	ls.write_all(mod='modn:')

def extra_smooth(hl, thr=5):
	for o in hl.l:
		h = o.obj
		for ib in range(2, h.GetNbinsX()):
			icl = h.GetBinContent(ib-1)
			ic0 = h.GetBinContent(ib)
			ich = h.GetBinContent(ib+1)
			if ic0 > thr * (icl + ich)/2.:
				print '    needs smooth bin ',h.GetTitle(),ib,ic0,h.GetBinCenter(ib)
				h.SetBinContent(ib, (icl + ich)/2.)
				err = (h.GetBinError(ib-1) + h.GetBinError(ib+1))/2.
				h.SetBinError(ib, err)

def main_rejections(X = ''):
	dvars = [
		'tgXEJE.fE-tgX.medjDCAL8x8*4',
		'tgXEJE8x8.fE-tgX.medjDCAL8x8',
		'tgXDJE8x8.fE-tgX.medjECAL8x8',
		'tgXEGA.fE-tgX.medgDCAL',
		'tgXDGA.fE-tgX.medgECAL'		
	]

	fdir = './patch_rfiles'

	hlname = fdir + ' ' + X
	hlname = ut.to_file_name(hlname)
	hl = dlist.dlist(hlname)

	print '[i] main_rejections'
	for var in [v.replace('X',X) for v in dvars]:
		fname = ut.to_file_name(var)
		print '    main_rejections:',var,fname
		flist = ut.find_files(fdir, '*'+fname+'*xsec*.root')
		#flist = ut.find_files(fdir, '*'+fname+'*1*.root')
		for fn in flist:
			print '    found file:',fn
			htitle = var.replace('tgX'.replace('X', X), '').replace('.fE', ' ').replace('.',' ')
			hl.add_from_file('o_0', fn, htitle, 'l')

	extra_smooth(hl)

	#hl.make_canvas()
	#hl.draw(logy=True)
	#hl.self_legend()
	#hl.update(logy=True)
	tu.gList.append(hl)

	hlr = dlist.fractional_yats(hl)
	hlr.make_canvas(600,600)
	hlr.draw(logy=True, miny=1e-5, maxy=3e2)
	rejection_table(hlr, 8./8000.)
	rejection_table(hlr, 30./8000.)
	hlr.zoom_axis(0, -5, 45)
	hlr.reset_axis_titles('E_{i}^{A} - median{E_{j}^{B}} (GeV)', 'rejection')
	hlr.self_legend(1, 'dead channel map [{}]'.format(X), x1=0.2,x2=0.9)
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hlr.update(logy=True)
	hlr.pdf()
	tu.gList.append(hlr)

def main_centrality_patch(X = ''):
	pass

def main_overlap(X = ''):
	pass

if __name__ == '__main__':
	tu.setup_basic_root()
	variants = ['', '1', '2', '3']
	for v in variants:
		if '--patches' in sys.argv:
			main_patches(v)
		if '--rejections' in sys.argv:
			main_rejections(v)

	if not ut.is_arg_set('-b'):
		IPython.embed()	

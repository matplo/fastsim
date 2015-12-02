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

kOther = 1
kCINT7 = 2
kEJ1   = 4
kEG1   = 8
kDJ1   = 16
kDG1   = 32

def tbit(ttype):
	d = dict([('kOther' , 1),('kCINT7' , 2),('kEJ1' , 4),('kEG1' , 8),('kDJ1' , 16), ('kDG1' , 32)])
	return d[ttype]

def main(dname):

	hl = dlist.dlist('medians')
	hlp = dlist.dlist('medians1d')

	ch = ROOT.TChain('t')
	flist = ut.find_files(dname, "Tree_*.root")
	for fn in flist:
		ch.AddFile(fn)

	for ij,var in enumerate(['medjECAL8x8:medjDCAL8x8']):
		for ttype in ['kCINT7', 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
			print ttype

			bit = tbit(ttype)
			nbins = 60
			xlow  = 0
			xhigh = 30
			hname_tmp = 'htmp({0},{1},{2},{0},{1},{2})'.format(nbins, xlow, xhigh)
			svar = '{}>>{}'.format(var, hname_tmp)
			condition = '(trig.type & {})'.format(bit)
			tc = du.canvas(ut.to_file_name(svar+condition), ut.to_file_name(svar+condition), 600, 600)
			ch.Draw(svar, condition, 'colz')
			ROOT.gPad.SetLogz()
			ROOT.gPad.SetGridx()
			ROOT.gPad.SetGridy()
			tu.gList.append(tc)
			hret = ROOT.gDirectory.Get('htmp')
			hret.SetDirectory(0)
			hret.GetXaxis().SetTitle('medjDCAL8x8')
			hret.GetYaxis().SetTitle('medjECAL8x8')
			hl.add(hret, 'median', 'colz')
			tc.pdf()

			for vs in var.split(':'):
				xlow = 0
				xhigh = 30
				nbins = 120
				hname_tmp = 'htmp({0},{1},{2})'.format(nbins, xlow, xhigh)
				svar = '{}>>{}'.format(vs, hname_tmp)
				condition = '(trig.type & {})'.format(bit)
				tu.getTempCanvas()
				ch.Draw(svar, condition, 'colz')
				hret = ROOT.gDirectory.Get('htmp')
				hret.SetDirectory(0)
				hlp.add(hret, '{} {}'.format(vs, ttype), 'hist')

	tu.gList.append(hl)

	hlp.make_canvas(600,600)
	hlp.tcanvas.cd()
	hlp.reset_axis_titles('median', 'counts')
	hlp.draw(logy=True)
	hlp.self_legend()
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hlp.update()
	hlp.pdf()
	tu.gList.append(hlp)

def subtr(fname):
	hs = [ 'histos/fEJ1subMedian', 'histos/fEG1subMedian', 'histos/fDJ1subMedian', 'histos/fDG1subMedian']
	hst = [ 'EJ1', 'EG1', 'DJ1', 'DG1']
	hl = dlist.dlist(fname)
	for i,hn in enumerate(hs):
		hl.add_from_file(hn, fname, hst[i], 'hist')
	hl.reset_axis_titles('Ei-median', 'counts')
	hl.zoom_axis(0, -30, 100)
	hl.make_canvas(w=600, h=600)
	hl.draw(logy=True)
	ROOT.gPad.SetLogy()
	hl.self_legend()
	hl.update()
	hl.pdf()
	tu.gList.append(hl)

	hlr = dlist.fractional_yats(hl)
	hlr.reset_axis_titles('[Ei-median] < thr', 'rejection')
	hlr.zoom_axis(0, -30, 100)
	hlr.make_canvas(w=600, h=600)
	hlr.draw(logy=True)
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()	
	hlr.self_legend()
	hlr.update()
	hlr.pdf()
	tu.gList.append(hlr)


if __name__ == '__main__':
	tu.setup_basic_root()
	envdir = os.getenv('RUN2AESDDIR')
	libs = ['libEMCALTriggerFast', 'libRAnalyzeESD']
	for l in libs:
		lib = os.path.join(envdir, 'lib', l)
		ROOT.gSystem.Load(lib)
	dname = ut.get_arg_with('--in')
	if dname==None:
		dname = './245146'
	if '--2d' in sys.argv:
		main(dname)
	if '--subtr' in sys.argv:
		if dname==None:
			dname = 'Hist.root'
		subtr(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

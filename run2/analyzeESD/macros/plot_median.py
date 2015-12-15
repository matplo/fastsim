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

	for ij,var in enumerate(['medjDCAL8x8:medjECAL8x8']): #, 'cent:medjECAL8x8']):
	#for ij,var in enumerate(['medjDCAL8x8:medjECAL8x8', 'cent:medjECAL8x8']):
		#for ttype in ['kCINT7']: #, 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
		for ttype in ['kCINT7', 'kEG1']: #, 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
			print ttype

			bit = tbit(ttype)
			nbins = 400
			xlow  = 0
			xhigh = 20
			if 'cent' in var:
				hname_tmp = 'htmp({0},{1},{2},{3},{4},{5})'.format(nbins, xlow, xhigh, 101, 0, 101)
			else:
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
			if hret==None:
				continue
			hret.SetDirectory(0)
			hret.GetXaxis().SetTitle('medjECAL8x8 (GeV)')
			if 'cent' in var:
				hret.GetYaxis().SetTitle('V0M centrality (%)')				
			else:
				hret.GetYaxis().SetTitle('medjDCAL8x8 (GeV)')
			hl.add(hret, 'median', 'colz')
			tc.pdf()

			for vs in var.split(':'):
				xlow = 0
				xhigh = 20
				nbins = 2000
				hname_tmp = 'htmp({0},{1},{2})'.format(nbins, xlow, xhigh)
				svar = '{}>>{}'.format(vs, hname_tmp)
				condition = '(trig.type & {})'.format(bit)
				tu.getTempCanvas()
				ch.Draw(svar, condition, 'colz')
				hret = ROOT.gDirectory.Get('htmp')
				hret.SetDirectory(0)
				hlp.add(hret, '{} {}'.format(vs, ttype), 'hist')

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
	hlp.png()
	#tu.gList.append(hlp)
	#tu.gList.append(hl)

	hls = dlist.ListStorage('medians')
	hls.append(hl)
	hls.append(hlp)
	hls.write_all('modn:')

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
	if '--2d' in sys.argv:
		if dname==None:
			dname = './245146'
		main(dname)
	if '--subtr' in sys.argv:
		if dname==None:
			dname = 'Hist.root'
		subtr(dname)
	if '--percent' in sys.argv:
		if dname == None:
			dname = 'medians1d.root'
		percentiles(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

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

def do_percentiles(hin, percent=10.):
	hlname = hin.GetName() + '-percentiles'
	hl = dlist.dlist(hlname)

	ncent = int(100./percent)
	print '[i] number of centrality bins:', ncent
	total = 0
	for ibx in range(1, hin.GetNbinsX()+1):
		total += hin.GetBinContent(ibx)
	print '    total:', total

	cbins = []

	ibx = hin.GetNbinsX()
	for n in range(0, ncent):
		ibstart = ibx
		thisbin = 0.0
		thisbin_pc = thisbin / total
		while thisbin_pc < (percent/100.):
			if ibx < 1:
				break
			thisbin    = thisbin + hin.GetBinContent(ibx)
			thisbin_pc = thisbin / total
			ibx = ibx - 1
		print '    cent bin:',n, ' bins in hist:', ibstart, ibx, ' % of the total', thisbin_pc
		cbins.append([hin.GetBinLowEdge(ibstart), hin.GetBinLowEdge(ibx) + hin.GetBinWidth(ibx)])
	return cbins

def percentiles_from_median(fname = 'medians1d.root'):
	hl = dlist.dlist('medians min. bias')
	hl.add_from_file('o_0', fname, 'EMCal', 'hist')
	hl.add_from_file('o_1', fname, ' DCal', 'hist')
	#hl.normalize_self(modTitle=True)

	arrname = ['Bins', 'Bins']
	outname = ['EMCalCentrality.py', 'DCalCentrality.py']
	for i,o in enumerate(hl.l):
		cbins = do_percentiles(o.obj, 10.)
		with open(outname[i], 'w') as f:
			print >> f,arrname[i],'=',cbins
			print arrname[i],'=',cbins
		f.close()

	hls = dlist.ListStorage('medians-percent')
	hls.append(hl)
	hls.draw_all(logy=True)

def percentiles_from_totalE(dname):
	# dump the totalE into a single histogram for MinBias -> gets the percentiles
	ch = ROOT.TChain('t')
	flist = ut.find_files(dname, "Tree_*.root")
	for fn in flist:
		ch.AddFile(fn)

	for t in ['kCINT7', 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
		hlp = dlist.dlist('totalE_{}'.format(t))
		xlow = 0
		xhigh = 30
		nbins = 3000
		hname_tmp = 'htmp({0},{1},{2})'.format(nbins, xlow, xhigh)
		svar = '{}>>{}'.format('trig.totalE', hname_tmp)
		bit = tbit(t)
		condition = '(trig.type & {})'.format(bit)
		tu.getTempCanvas()
		ch.Draw(svar, condition, 'colz')
		hret = ROOT.gDirectory.Get('htmp')
		hret.SetDirectory(0)
		hlp.add(hret, '{}'.format(t), 'hist')

	hlp.make_canvas()
	hlp.draw(logy=True)
	hlp.self_legend()
	ROOT.gPad.SetLogy()
	hlp.update()

	tu.gList.append(hlp)

if __name__ == '__main__':
	tu.setup_basic_root()
	envdir = os.getenv('RUN2AESDDIR')
	libs = ['libEMCALTriggerFast', 'libRAnalyzeESD']
	for l in libs:
		lib = os.path.join(envdir, 'lib', l)
		ROOT.gSystem.Load(lib)
	dname = ut.get_arg_with('--in')
	if '--percent' in sys.argv:
		if dname == None:
			dname = 'medians1d.root'
		percentiles(dname)
	if '--totalE' in sys.argv:
		if dname == None:
			dname = './output000245146'
		percentiles_from_totalE(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

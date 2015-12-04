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

	ibx = hin.GetNbinsX() - 1
	for n in range(0, ncent):
		ibstart = ibx + 1
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
	ch = tu.tchain_from_dir('t', dname, 'Tree_*.root')

	hlp = dlist.dlist('totalE_'+os.path.basename(dname))
	for t in ['kCINT7', 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
		xlow = 0
		xhigh = 2000
		nbins = 10000
		hname_tmp = 'htmp({0},{1},{2})'.format(nbins, xlow, xhigh)
		svar = '{}>>{}'.format('trig.totalE', hname_tmp)
		bit = tbit(t)
		condition = '(trig.type & {})'.format(bit)
		tu.getTempCanvas()
		print '[i] percentiles_from_totalE: draw:',svar, condition
		ch.Draw(svar, condition, 'colz')
		hret = ROOT.gDirectory.Get('htmp')
		hret.SetDirectory(0)
		if hret.GetEntries() > 1e5:
			hlp.add(hret, '{} [{:1.2f} M]'.format(t, hret.GetEntries() / 1.e6), 'hist')
		else:
			hlp.add(hret, '{} [{:1.2f} k]'.format(t, hret.GetEntries() / 1.e3), 'hist')
	hlp.reset_axis_titles('total E+DCal energy (GeV)', 'N events')
	hlp.make_canvas(w=600,h=600)
	hlp.draw(logy=True)
	hlp.self_legend()
	hlp.zoom_axis(0, 0, 1200)
	ROOT.gPad.SetLogy()
	hlp.update()
	hlp.pdf()
	hlp.write_to_file(name_mod='modn:')
	tu.gList.append(hlp)

def percentiles_from_totalE_cent(fname):
	hl = dlist.dlist('totalE min. bias. centrality')
	hl.add_from_file('o_0', fname)

	arrname = ['Bins']
	outname = ['TotalECentrality.py']
	for i,o in enumerate(hl.l):
		cbins = do_percentiles(o.obj, 10.)
		with open(outname[i], 'w') as f:
			print >> f,arrname[i],'=',cbins
			print arrname[i],'=',cbins
		f.close()

	hls = dlist.ListStorage('medians-percent')
	hls.append(hl)
	hls.draw_all(logy=True)

def show_percentiles_from_totalE(fname):
	print '[i] show_percentiles_from_totalE:',fname
	hl = dlist.load_file(fname, names_not_titles=False, draw_opt='')
	print hl
	hl.make_canvas()
	hl.draw(logy=True)
	hl.self_legend()
	ROOT.gPad.SetLogy()
	hl.update()
	tu.gList.append(hl)

	import TotalECentrality as cent

	fractions = []
	for ib,b in enumerate(cent.Bins):
		print '    bin',ib,b[1],b[0]
		nmb = 0
		for i,o in enumerate(hl.l):
			h = o.obj
			xmin = h.FindBin(b[1])
			xmax = h.FindBin(b[0])
			nev = h.Integral(xmin, xmax)
			if i==0:
				nmb = nev
			else:
				fraction = nev / nmb
				fractions.append([h.GetTitle(), ib, fraction])
	print fractions

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
		if '--make' in sys.argv:
			if dname == None:
				dname = './output000245146'
			percentiles_from_totalE(dname)
		else:
			if dname == None:
				dname = 'totalE_output000245146.root'
			if '--show' in sys.argv:
				show_percentiles_from_totalE(dname)				
			else:
				percentiles_from_totalE_cent(dname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

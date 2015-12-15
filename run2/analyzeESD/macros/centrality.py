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
	#hl = dlist.dlist('medians min. bias')
	#hl.add_from_file('o_0', fname, 'EMCal', 'hist')
	#hl.add_from_file('o_1', fname, ' DCal', 'hist')
	#hl.normalize_self(modTitle=True)
	hl = dlist.load_file(fname, names_not_titles=False, draw_opt='')

	arrname = ['Bins', 'Bins']
	outname = ['EMCalCentrality.py', 'DCalCentrality.py']
	for i,o in enumerate(hl.l):
		if i > 1:
			continue
		cbins = do_percentiles(o.obj, 10.)
		with open(outname[i], 'w') as f:
			print >> f,arrname[i],'=',cbins
			print arrname[i],'=',cbins
		f.close()

	hls = dlist.ListStorage('medians-percent')
	hl.rebin(5)
	hls.append(hl)
	hls.draw_all(logy=True)

def percentiles_from_median_det(fname = 'medians1d.root', idet = 0):
	hlc = dlist.load_file(fname, names_not_titles=False, draw_opt='')
	arrname = ['Bins', 'Bins']
	outname = ['EMCalCentrality.py', 'DCalCentrality.py']
	h = hlc.l[idet].obj
	cbins = do_percentiles(h, 10.)
	with open(outname[idet], 'w') as f:
		print >> f,arrname[idet],'=',cbins
		print arrname[idet],'=',cbins
	f.close()

	hls = dlist.ListStorage('medians-percent')
	#hl.rebin(5)
	hls.append(hlc)
	hls.draw_all(logy=True)

	import importlib
	cent = importlib.import_module(outname[idet].replace('.py',''))

	hl = dlist.load_file(fname, names_not_titles=False, draw_opt='')
	hlcent = dlist.dlist(hl.name + '_cent det {}'.format(idet) )
	for i,o in enumerate(hl.l):
		if i % 2 != idet:
			continue
		h     = o.obj
		title = h.GetTitle()
		name  = h.GetName() + '_cent'
		nbins = len(cent.Bins)
		hnew  = ROOT.TH1D(name, title, nbins, 0, nbins * 10.)
		hlcent.add(hnew, '', 'hist +l1')
	hlcent.reset_axis_titles('centrality bins in % from median patches', 'fraction of events')

	fractions = []
	for ib,b in enumerate(cent.Bins):
		print '    bin',ib,b[1],b[0]
		nmb = 0
		ic = 0
		for i,o in enumerate(hl.l):
			if i % 2 != idet:
				continue
			ic   = i / 2
			h    = o.obj
			xmin = h.FindBin(b[1])
			xmax = h.FindBin(b[0])
			nev  = h.Integral(xmin, xmax)
			if i == idet:
				nmb = nev
			fraction = nev / nmb
			fractions.append([h.GetTitle(), ib, fraction])
			hlcent.l[ic].obj.SetBinContent(ib+1, fraction)
			ic += 1

	hlcent.make_canvas(w=600,h=600)
	hlcent.draw(logy=True, maxy=2, miny=1e-4)
	for i,o in enumerate(hlcent.l):
		if i == 0:
			continue
		h    = o.obj
		mean = h.GetMean()
		x1   = mean
		x2   = mean
		y1   = 1e-4
		y2   = 1
		col  = h.GetLineColor()
		du.draw_line(x1, y1, x2, y2, col, style=7, width=3, alpha=0.7)
		newtitle = h.GetTitle() + ' average: {:1.1f} %'.format(mean)
		h.SetTitle(newtitle)
	hlcent.self_legend(x1=0.5, y1=0.7, y2=0.85)		
	ROOT.gPad.SetGridy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetLogy()
	hlcent.update()
	tu.gList.append(hlcent)
	hlcent.pdf()

### TOTAL E ############################################

def cent_totalE(dname):
	ch = tu.tchain_from_dir('t', dname, 'Tree_*.root')
	hlp = dlist.dlist('cent_totalE_'+os.path.basename(dname))
	for t in ['kCINT7']:
		for svarx in ['trig.totalE', 'trig.cent']:
			xlow = 0
			xhigh = 2000
			nbins = 10000 #2000
			if 'cent' in svarx:
				xlow = 0
				xhigh = 101
				nbins = 101
			hname_tmp = 'htmp({0},{1},{2})'.format(nbins, xlow, xhigh)
			svar = '{}>>{}'.format('{}', hname_tmp).format(svarx)
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

	for t in ['kCINT7']:
		xlow = 0
		xhigh = 2000
		nbins = 10000
		hname_tmp = 'htmp({0},{1},{2},{3},{4},{5})'.format(nbins, xlow, xhigh, 101, 0, 101)
		svar = '{}>>{}'.format('trig.cent:trig.totalE', hname_tmp)
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

	hlp.reset_axis_titles('total E+DCal energy (GeV)', 'V0M centrality')
	hlp.make_canvas(w=600,h=600)
	hlp.draw(logy=True)
	hlp.self_legend()
	hlp.zoom_axis(0, 0, 1200)
	ROOT.gPad.SetLogy()
	hlp.update()
	hlp.pdf()
	hlp.write_to_file(name_mod='modn:')
	tu.gList.append(hlp)

def draw_cent_totalE(fname):
	for i in range(3):
		hl = dlist.dlist('cent_totalE_{}'.format(i))
		dopt = 'hist'
		if i == 2:
			dopt = 'colz'
		hl.add_from_file('o_{}'.format(i), fname, '', dopt)
		hl.reset_axis_titles('total E+DCal energy (GeV)', 'N events')
		if i == 1:
			hl.reset_axis_titles('V0M centrality (%)', 'N events')
		if i == 2:
			hl.reset_axis_titles('Total E+DCal energy (GeV)', 'V0M centrality (%)')
		if i==1:
			hl.zoom_axis(0, 0, 1200)
		if i==0:
			miny = 1
			maxy = 1e6
		h=600
		if i<2:
			h=300
		hl.make_canvas(w=600,h=h)
		hl.draw(miny=miny, maxy=maxy, logy=True)
		#hl.self_legend()
		if i!=2:
			ROOT.gPad.SetLogy()
		else:
			ROOT.gPad.SetLogz()
		hl.update()
		hl.pdf()
		hl.png()
		tu.gList.append(hl)


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

	hls = dlist.ListStorage('totalE-percent')
	hls.append(hl)
	hls.draw_all(logy=True)

def show_percentiles_from_totalE(fname):
	print '[i] show_percentiles_from_totalE:',fname
	hl = dlist.load_file(fname, names_not_titles=False, draw_opt='')
	print hl
	hl.make_canvas(w=600, h=600)
	hl.rebin(10)
	hl.scale(1/10.)
	hl.draw(logy=True)
	hl.self_legend()
	ROOT.gPad.SetLogy()
	hl.update()
	hl.pdf()
	tu.gList.append(hl)

	import TotalECentrality as cent

	hlcent = dlist.dlist(hl.name + '_cent')
	for i,o in enumerate(hl.l):
		h = o.obj
		title = h.GetTitle()
		name = h.GetName() + '_cent'
		nbins = len(cent.Bins)
		hnew = ROOT.TH1D(name, title, nbins, 0, nbins * 10.)
		hlcent.add(hnew, '', 'hist +l1')
	hlcent.reset_axis_titles('centrality bins in % from total energy in E+DCal', 'fraction of events')

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
			fraction = nev / nmb
			fractions.append([h.GetTitle(), ib, fraction])
			hlcent.l[i].obj.SetBinContent(ib+1, fraction)

	hlcent.make_canvas(w=600,h=600)
	hlcent.draw(logy=True, maxy=2, miny=1e-4)
	for i,o in enumerate(hlcent.l):
		if i == 0:
			continue
		h = o.obj
		mean = h.GetMean()
		x1 = mean
		x2 = mean
		y1 = 1e-4
		y2 = 1
		col = h.GetLineColor()
		du.draw_line(x1, y1, x2, y2, col, style=7, width=3, alpha=0.7)
		newtitle = h.GetTitle() + 'average: {:1.1f} %'.format(mean)
		h.SetTitle(newtitle)
	hlcent.self_legend(x1=0.55, y1=0.7, y2=0.85)		
	ROOT.gPad.SetGridy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetLogy()
	hlcent.update()
	tu.gList.append(hlcent)
	hlcent.pdf()
	#print fractions

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
		#percentiles_from_median(dname)
		percentiles_from_median_det(dname, 0)
		percentiles_from_median_det(dname, 1)
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
	if '--cent' in sys.argv:
		if '--make' in sys.argv:
			if dname == None:
				dname = './output000245146'
			cent_totalE(dname)
		else:
			if dname == None:
				dname = 'cent_totalE_output000245146.root'
			draw_cent_totalE(dname)

	if not ut.is_arg_set('-b'):
		IPython.embed()	

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
from je_plot_trigger import *
from ga_plot_trigger import *

def get_entries(fname):
	nentries = 0
	flist = ut.find_files(fname, '*.root')
	for f in flist:
		fr = ROOT.TFile.Open(f)
		tn = fr.Get('tn')
		nentries += tn.GetEntries()
		fr.Close()
	nentries = nentries/len(flist)		
	print 'nentries=',nentries
	return nentries

def get_xsec_je(fname, which='EMC', R=0.4, usercut='(1)', bwidth=1, scalebw=True):
	tname = 'tnjet'
	if R==0.2:
		tname = 'tnjetr'
	if which=='EMC':
		cal = 0
		keepOutFactor = EMCalKeepOutFactor(R)
	else:
		cal = 1
		keepOutFactor = DCalKeepOutFactor(R)
	var    = 'pt'
	xlow   = 0
	if '--lowpt' in sys.argv:
		xhigh  = 100
		bwidth = 10
	else:
		xhigh  = 200
	tu.getTempCanvas().cd()
	cuts = '(xsec)*( ({}) && (cal=={}) )'.format(usercut, cal)
	#h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	refcuts = '( ({}) && (cal=={}) )'.format(usercut, cal)
	hl = draw_ntuple.h1d_from_ntuple_dir_filter(fname, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=-1, thr=1*bwidth/2) #nev=10000, thr = 1 * bwidth/2.)
	#h = hl.last().obj
	h = hl[0].obj.Clone(hl[0].name + 'clone')
	#cuts = '( ({}) && (cal=={}))'.format(usercut, cal)
	#href = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	#tu.filter_single_entries(h, href, 3)
	#print keepOutFactor
	#h.Scale(1./get_nev(fname)*keepOutFactor)
	#h.Scale(1./get_nev(fname)/bwidth*keepOutFactor)
	nentries = get_entries(fname)
	if scalebw == True:
		h.Scale(1./nentries/bwidth*keepOutFactor)
	else:
		h.Scale(1./nentries*keepOutFactor)		
	return h

def get_yields_je_bin_by_bin(fname, nev=150.e6, which='EMC', R=0.4, usercut='(1)', bwidth=1, scalebw=False):
	hlname = 'yields_{}_{}_{:1.1f}M_events'.format(which, str(R), nev/1.e6)
	if '--lowpt' in sys.argv:
		hlname = hlname + '-lowpt'
	hl = dlist.dlist(hlname)
	cent = centrality.Centrality()
	hmb  = get_xsec_je(fname, which, R, usercut, bwidth, scalebw=scalebw)
	hmb.Scale(cent.TAAmb() * nev)
	htitle = 'min. bias [{:1.1f}M]'.format(nev/1.e6)
	hl.add(hmb, htitle, 'p')
	for i,taa in enumerate(cent.TAAs()):
		print cent.Label(i), taa, nev * cent.BinWidth(i)
		h = get_xsec_je(fname, which, R, usercut, bwidth, scalebw=scalebw)
		h.Scale(taa * nev * cent.BinWidth(i))
		htitle = '{} R={} {} [{}M]'.format(which, R, cent.Label(i), nev * cent.BinWidth(i)/1e6)
		hl.add(h, htitle, 'p')
	if scalebw == True:		
		hl.reset_axis_titles('jet p_{T} (GeV/c)', 'dN/dp_{T} (c/GeV)')
		yscale = 1.
	else:
		yaxtitle = 'N_{jets} in bwidth GeV/c bin'
		yaxtitle = yaxtitle.replace('bwidth', str(bwidth))
		hl.reset_axis_titles('jet p_{T} (GeV/c)', yaxtitle)
		yscale = bwidth

	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 0, 350)
	hl.draw(logy=True, miny=1e-3 * yscale, maxy=1e8 * yscale)
	hl.self_legend(1, '{} R={}'.format(which, R))
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()	
	hl.update()
	tu.gList.append(hl)	
	if '--print' in sys.argv:
		hl.pdf()
	if '--write' in sys.argv:
		hl.write_to_file(name_mod='modn:')
	return hl

def get_yields_je(fname, nev=150.e6, which='EMC', R=0.4, usercut='(1)', bwidth=1, scalebw=False):
	hlname = 'yields_{}_{}_{:1.1f}M_events'.format(which, str(R), nev/1.e6)
	if '--lowpt' in sys.argv:
		hlname = hlname + '-lowpt'
	hl      = dlist.dlist(hlname)
	cent    = centrality.Centrality()
	hjexsec = get_xsec_je(fname, which, R, usercut, bwidth, scalebw=scalebw)
	hmb     = tu.clone(hjexsec, 'jemb', which, R)
	hmb.Scale(cent.TAAmb() * nev)
	htitle = 'min. bias [{:1.1f}M]'.format(nev/1.e6)
	hl.add(hmb, htitle, 'p')
	for i,taa in enumerate(cent.TAAs()):
		print cent.Label(i), taa, nev * cent.BinWidth(i)
		#h = get_xsec_je(fname, which, R, usercut, bwidth, scalebw=scalebw)
		h = tu.clone(hjexsec, 'je', which, R, cent.Label(i))
		h.Scale(taa * nev * cent.BinWidth(i))
		htitle = '{} R={} {} [{}M]'.format(which, R, cent.Label(i), nev * cent.BinWidth(i)/1e6)
		hl.add(h, htitle, 'p')
	if scalebw == True:		
		hl.reset_axis_titles('jet p_{T} (GeV/c)', 'dN/dp_{T} (c/GeV)')
		yscale = 1.
	else:
		yaxtitle = 'N_{jets} in bwidth GeV/c bin'
		yaxtitle = yaxtitle.replace('bwidth', str(bwidth))
		hl.reset_axis_titles('jet p_{T} (GeV/c)', yaxtitle)
		yscale = bwidth

	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 0, 350)
	hl.draw(logy=True, miny=1e-1 * yscale, maxy=1e9 * yscale)
	hl.self_legend(1, '{} R={}'.format(which, R))
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()	
	hl.update()
	tu.gList.append(hl)	
	if '--print' in sys.argv:
		hl.pdf()
	if '--write' in sys.argv:
		hl.write_to_file(name_mod='modn:')
	return hl

def plot_xsec_je(fname, bwidth=20):
	hlname = 'xsection'
	hl = dlist.dlist(hlname)
	h = get_xsec_je(fname, 'EMC', R=0.4, bwidth=bwidth)
	hl.add(h, 'R=0.4 EMCal', 'p')
	h = get_xsec_je(fname, 'EMC', R=0.2, bwidth=bwidth)
	hl.add(h, 'R=0.2 EMCal', 'p')
	h = get_xsec_je(fname, 'DMC', R=0.2, bwidth=bwidth)
	hl.add(h, 'R=0.2 DCal', 'p')
	hl.reset_axis_titles('jet p_{T} (GeV/c)', 'd#sigma/dp_{T} (mb c/GeV)')
	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 0, 350)
	hl.draw(logy=True, miny=1e-10, maxy=1e-1)
	hl.self_legend()
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()	
	hl.update()
	tu.gList.append(hl)	
	if '--print' in sys.argv:
		hl.pdf()
	if '--write' in sys.argv:
		hl.write_to_file(name_mod='modn:')

	#hlr = dlist.make_ratio(hl[1].obj, hl[0].obj)
	#hlr.make_canvas(600,600)
	#hlr.draw(miny=0, maxy=1.2)
	#hlr.self_legend()
	#tu.gList.append(hlr)

def get_xsec_gapi(fname, which='EMC', gapi='g', usercut='(1)', bwidth=1):
	tname = 'tng'
	if gapi=='pi0':
		tname = 'tnpi0'
	if which=='EMC':
		cal = 0
	else:
		cal = 1
	var    = 'pt'
	xlow   = 0
	xhigh  = 50
	if gapi=='pi0':
		xhigh = 100
	tu.getTempCanvas()
	cuts = '(xsec)*( ({}) && (cal=={}))'.format(usercut, cal)
	h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	#cuts = '( ({}) && (cal=={}))'.format(usercut, cal)
	#href = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	#tu.filter_single_entries(h, href, 3)
	h.Scale(1./get_nev(fname)/bwidth)
	return h

def get_yields_gapi(fname, nev=150.e6, which='EMC', gapi='g', usercut='(1)', bwidth=1):
	hlname = 'yields_{}_{}_{:1.1f}M_events'.format(which, gapi, nev/1.e6)
	hl = dlist.dlist(hlname)
	cent = centrality.Centrality()
	hmb  = get_xsec_gapi(fname, which, gapi, usercut, bwidth)
	hmb.Scale(cent.TAAmb() * nev)
	htitle = 'min. bias [{:1.1f}M]'.format(nev/1.e6)
	hl.add(hmb, htitle, 'p')
	for i,taa in enumerate(cent.TAAs()):
		print cent.Label(i), taa, nev * cent.BinWidth(i)
		h = get_xsec_gapi(fname, which, gapi, usercut, bwidth)
		h.Scale(taa * nev * cent.BinWidth(i))
		htitle = '{} {} {} [{}M]'.format(which, gapi, cent.Label(i), nev * cent.BinWidth(i)/1e6)
		hl.add(h, htitle, 'p')
	hl.reset_axis_titles('p_{T} (GeV/c)', 'dN/dp_{T} (c/GeV)')
	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 0, 350)
	hl.draw(logy=True, miny=1e-2, maxy=1e6)
	hl.self_legend()
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()	
	hl.update()
	tu.gList.append(hl)	
	if '--print' in sys.argv:
		hl.pdf()
	return hl

def compare_to_atlas(fname='/Users/ploskon/devel/sandbox/run2/trigger/generate/7TeV/default-out-list.outputs/out.root'):
	import sevenTeV.atlas_jets as atlas
	hl = dlist.dlist('py_to_atlas')
	atlas = atlas.AtlasJets()
	h = get_xsec(fname, bwidth=30)
	h.Scale(EMCalUpScaleAtlas() * 1.e9 / 1.4) #mili to pico and dy
	hl.add(h, 'Pythia8 ak_{T} R=0.4, 7 TeV', 'p')
	hl.reset_axis_titles('jet p_{T} (GeV/c)', 'd#sigma/dy/dp_{T} (pb c/GeV)')
	hl.add_list(atlas.get())
	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 0, 350)
	hl.draw(logy=True, miny=1, maxy=3e8)
	hl.self_legend()
	ROOT.gPad.SetLogy()
	hl.update()
	tu.gList.append(hl)	
	if '--print' in sys.argv:
		hl.pdf()

def draw_bias(fname, rej=1e-3, thr=[29, 18, 19]):

	bwidth = 10	

	hlr = dlist.dlist(tu.make_unique_name('bias', rej, thr))

	dopt = 'l hist'

	#R=0.4 16x16 patch
	h  = get_xsec_je(fname, which='EMC', R=0.4, usercut='(1)', bwidth=bwidth)
	hc = get_xsec_je(fname, which='EMC', R=0.4, usercut='((maxJE-medJE * 4.) > {})'.format(thr[0]), bwidth=bwidth)
	hlr1 = dlist.make_ratio(hc, h)
	hlr.add(hlr1[0].obj, 'EMC R=0.4 (maxJE[16x16]-medJE[8x8] * 4) > {} GeV'.format(thr[0]), dopt)

	#R=0.2 16x16 patch
	h  = get_xsec_je(fname, which='EMC', R=0.2, usercut='(1)', bwidth=bwidth)
	hc = get_xsec_je(fname, which='EMC', R=0.2, usercut='((maxJE-medJE * 4.) > {})'.format(thr[0]), bwidth=bwidth)
	hlr2 = dlist.make_ratio(hc, h)
	hlr.add(hlr2[0].obj, 'EMC R=0.2 (maxJE[16x16]-medJE[8x8] * 4) > {} GeV'.format(thr[0]), dopt)

	#R=0.2 DMC 8x8 patch
	h  = get_xsec_je(fname, which='DMC', R=0.2, usercut='(1)', bwidth=bwidth)
	hc = get_xsec_je(fname, which='DMC', R=0.2, usercut='((maxJE8x8-medJE) > {})'.format(thr[1]), bwidth=bwidth)
	hlr3 = dlist.make_ratio(hc, h)
	hlr.add(hlr3[0].obj, 'DMC R=0.2 (maxJE[8x8]-medJE[8x8]) > {} GeV'.format(thr[1]), dopt)

	if '--optional' in sys.argv:
		#R=0.4 EMC 8x8 patch
		h  = get_xsec_je(fname, which='EMC', R=0.4, usercut='(1)', bwidth=bwidth)
		hc = get_xsec_je(fname, which='EMC', R=0.4, usercut='((maxJE8x8-medJE) > {})'.format(thr[2]), bwidth=bwidth)
		hlr1 = dlist.make_ratio(hc, h)
		hlr.add(hlr1[0].obj, 'EMC R=0.4 (maxJE[8x8]-medJE[8x8]) > {} GeV'.format(thr[2]), dopt)
		#R=0.2 EMC 8x8 patch
		h  = get_xsec_je(fname, which='EMC', R=0.2, usercut='(1)', bwidth=bwidth)
		hc = get_xsec_je(fname, which='EMC', R=0.2, usercut='((maxJE8x8-medJE) > {})'.format(thr[2]), bwidth=bwidth)
		hlr2 = dlist.make_ratio(hc, h)
		hlr.add(hlr2[0].obj, 'EMC R=0.2 (maxJE[8x8]-medJE[8x8]) > {} GeV'.format(thr[2]), dopt)

	hlr.make_canvas(600, 600)
	hlr.reset_axis_titles('p_{T}', 'ratio:  triggered /min. bias')
	hlr.draw(miny=0, maxy=2)
	hlr.self_legend(1, 'Rejection {:1.0e}'.format(rej), x1=0.3)
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()		
	hlr.update()

	tu.gList.append(hlr)

def main():
	fname = tu.get_arg_with('--in')
	if fname == None:
		print "usage:",__file__,'--in <file.root>'
		return

	if '--mtune1.2' in sys.argv:
		fname = fname.replace('mtune1.0', 'mtune1.2')

	if '--patches' in sys.argv:
		plot_patches_je(fname)

	if '--xsec' in sys.argv:
		plot_xsec_je(fname, bwidth=20)

	effiRAA = 1.
	#if '--noeffiRAA':
	if '--effiRAA' in sys.argv:
		effiRAA = 0.5 * 0.25 

	if '--yields' in sys.argv:
		bwidth = 10
		if '--mb' in sys.argv:
			nev = 150.e6 * effiRAA
		else:
			sigmaPbPb = 7.7
			intLumi = 220. * 1.e6 * effiRAA
			nev = intLumi * sigmaPbPb
		get_yields_je(fname, nev=nev, which='EMC', R=0.4, usercut='(1)', bwidth=bwidth)
		get_yields_je(fname, nev=nev, which='EMC', R=0.2, usercut='(1)', bwidth=bwidth)
		get_yields_je(fname, nev=nev, which='DMC', R=0.2, usercut='(1)', bwidth=bwidth)

	rejection = 1.0
	if '--rej1e-3' in sys.argv:
		thrs=[23, 15, 16] # last is optional 8x8 EMC	#thrs=[29, 18, 19] # last is optional 8x8 EMC
		if '--any' in sys.argv:
			thrs = [15, 9, 8]
		rejection = 1e-3
	if '--rej3e-3' in sys.argv:
		thrs=[22, 13, 14] # last is optional 8x8 EMC#thrs=[27, 16, 17] # last is optional 8x8 EMC
		if '--any' in sys.argv:
			thrs = [12, 7, 7]
		rejection = 3e-3

	if '--bias' in sys.argv:
		if rejection < 1:
			draw_bias(fname, rejection, thrs)

	if '--gapiy' in sys.argv:
		bwidth = 10
		if '--mb' in sys.argv:
			nev = 150.e6
		else:
			sigmaPbPb = 7.7
			intLumi = 220. * 1.e6
			nev = intLumi * sigmaPbPb
		gapi = 'gamma'
		if '--pi0' in sys.argv:
			gapi='pi0'
		get_yields_gapi(fname, nev=nev, which='EMC', gapi=gapi, usercut='(1)', bwidth=bwidth)
		get_yields_gapi(fname, nev=nev, which='DMC', gapi=gapi, usercut='(1)', bwidth=bwidth)

	if '--atlas' in sys.argv:
		#compare_to_atlas(fname)
		compare_to_atlas()

	if '--rejections' in sys.argv:
		#plot_rejections_je(fname, usercut="cent<=10")
		plot_rejections_je(fname)
		plot_rejections_ga(fname)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

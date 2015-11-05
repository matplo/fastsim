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

from trigutils import *
from je_plot_trigger import *
from ga_plot_trigger import *

def get_xsec_je(fname, which='EMC', R=0.4, usercut='(1)', bwidth=1):
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
		xhigh = 100
		bwidth = 10
	else:
		xhigh  = 260
	tu.getTempCanvas().cd()
	cuts = '(xsec)*( ({}) && (cal=={}))'.format(usercut, cal)
	h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	#cuts = '( ({}) && (cal=={}))'.format(usercut, cal)
	#href = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	#tu.filter_single_entries(h, href, 3)
	h.Scale(1./get_nev(fname)/keepOutFactor/bwidth)
	return h

def get_yields_je(fname, nev=150.e6, which='EMC', R=0.4, usercut='(1)', bwidth=1):
	hlname = 'yields_{}_{}_{:1.1f}M_events'.format(which, str(R), nev/1.e6)
	if '--lowpt' in sys.argv:
		hlname = hlname + '-lowpt'
	hl = dlist.dlist(hlname)
	cent = centrality.Centrality()
	hmb  = get_xsec_je(fname, which, R, usercut, bwidth)
	hmb.Scale(cent.TAAmb() * nev)
	htitle = 'min. bias [{:1.1f}M]'.format(nev/1.e6)
	hl.add(hmb, htitle, 'p')
	for i,taa in enumerate(cent.TAAs()):
		print cent.Label(i), taa, nev * cent.BinWidth(i)
		h = get_xsec_je(fname, which, R, usercut, bwidth)
		h.Scale(taa * nev * cent.BinWidth(i))
		htitle = '{} R={} {} [{}M]'.format(which, R, cent.Label(i), nev * cent.BinWidth(i)/1e6)
		hl.add(h, htitle, 'p')
	hl.reset_axis_titles('jet p_{T} (GeV/c)', 'dN/dp_{T} (c/GeV)')
	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 0, 350)
	hl.draw(logy=True, miny=1e-3, maxy=1e8)
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

def main():
	fname = tu.get_arg_with('--in')
	if fname == None and not '--ycut1' in sys.argv:
		print "usage:",__file__,'--in <file.root>'
		return

	if '--patches' in sys.argv:
		plot_patches_je(fname)

	if '--xsec' in sys.argv:
		plot_xsec_je(fname, bwidth=20)

	effiRAA = 0.5 * 0.25 
	if '--noeffiRAA':
		effiRAA = 1.

	if '--yields' in sys.argv:
		bwidth = 20
		if '--mb' in sys.argv:
			nev = 150.e6 * effiRAA
		else:
			sigmaPbPb = 7.7
			intLumi = 220. * 1.e6 * effiRAA
			nev = intLumi * sigmaPbPb
		get_yields_je(fname, nev=nev, which='EMC', R=0.4, usercut='(1)', bwidth=bwidth)
		get_yields_je(fname, nev=nev, which='EMC', R=0.2, usercut='(1)', bwidth=bwidth)
		get_yields_je(fname, nev=nev, which='DMC', R=0.2, usercut='(1)', bwidth=bwidth)

	if '--ycut1' in sys.argv:
		fname = './qcd-mtune1.2-list.outputs.root'
		bwidth = 10
		if '--mb' in sys.argv:
			nev = 150.e6 * effiRAA
		else:
			sigmaPbPb = 7.7
			intLumi = 220. * 1.e6 * effiRAA
			nev = intLumi * sigmaPbPb
		#hl1 = get_yields_je(fname, nev=nev, which='EMC', R=0.4, usercut='(1)', bwidth=bwidth)
		#hl2 = get_yields_je(fname, nev=nev, which='EMC', R=0.2, usercut='(1)', bwidth=bwidth)
		#hl3 = get_yields_je(fname, nev=nev, which='DMC', R=0.2, usercut='(1)', bwidth=bwidth)

		#hl1c = get_yields_je(fname, nev=nev, which='EMC', R=0.4, usercut='((maxJE-medJE)>14)', bwidth=bwidth)
		#hl2c = get_yields_je(fname, nev=nev, which='EMC', R=0.2, usercut='((maxJE-medJE)>14)', bwidth=bwidth)
		#hl3c = get_yields_je(fname, nev=nev, which='DMC', R=0.2, usercut='((maxJE-medJE)>9)', bwidth=bwidth)

		#hlr1 = divide_lists(hl1c, hl1)
		#hlr2 = divide_lists(hl2c, hl2)
		#hlr3 = divide_lists(hl3c, hl3)

		hlr = dlist.dlist('bias')
		h  = get_xsec_je(fname, which='EMC', R=0.4, usercut='(1)', bwidth=bwidth)
		hc = get_xsec_je(fname, which='EMC', R=0.4, usercut='((maxJE-medJE)>18)', bwidth=bwidth)
		hlr1 = dlist.make_ratio(hc, h)
		hlr.add(hlr1[0].obj, 'EMC R=0.4 (maxJE-medJE)>18', 'l hist')

		h  = get_xsec_je(fname, which='EMC', R=0.2, usercut='(1)', bwidth=bwidth)
		hc = get_xsec_je(fname, which='EMC', R=0.2, usercut='((maxJE-medJE)>18)', bwidth=bwidth)
		hlr2 = dlist.make_ratio(hc, h)
		hlr.add(hlr2[0].obj, 'EMC R=0.2 (maxJE-medJE)>18', 'l hist')

		h  = get_xsec_je(fname, which='DMC', R=0.2, usercut='(1)', bwidth=bwidth)
		hc = get_xsec_je(fname, which='DMC', R=0.2, usercut='((maxJE-medJE)>11)', bwidth=bwidth)
		hlr3 = dlist.make_ratio(hc, h)
		hlr.add(hlr3[0].obj, 'DMC R=0.2 (maxJE-medJE)>11', 'l hist')

		hlr.make_canvas(600, 600)
		hlr.reset_axis_titles('p_{T}', 'ratio:  triggered /min. bias')
		hlr.draw(miny=0, maxy=2)
		hlr.self_legend(x1=0.3)
		hlr.update()

		tu.gList.append(hlr)

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
		plot_rejections_je(fname)
		plot_rejections_ga(fname)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

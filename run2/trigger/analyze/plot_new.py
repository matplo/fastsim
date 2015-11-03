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

def to_file_name(s):
	return "".join([x if x.isalnum() else "_" for x in s])

def rejection_table(hl, rej = 1.e-3):
        print '[i] rejections for', hl.name, 'rej:',rej
        retvals = []
        for o in hl.l:
                h = o.obj
                for ib in range(1, h.GetNbinsX()):
                        if h.GetBinContent(ib) <= rej:
                                print '    ', h.GetTitle(), h.GetBinLowEdge(ib), h.GetBinContent(ib)
                                newtitle = '{} [{:.0e}@{:.1f}]'.format(h.GetTitle(), rej, h.GetBinLowEdge(ib))
                                h.SetTitle(newtitle)
                                retvals.append(h.GetBinLowEdge(ib))
                                break
        return retvals

def get_nev(fname):
	h = tu.get_object_from_file('hNev', fname)
	return h.GetBinContent(1)

def make_cent_slices(h2d):
	# assuming centrality is a Y-axis
	axis = 0
	hname = h2d.GetName()
	hl    = dlist.dlist(hname + '-cent')
	cent  = centrality.Centrality()
	for ic in range(cent.nbins()+1):
		hname = '{}-{}'.format(h2d.GetName(), ic)
		if ic == 0:
			ixmin = 0
			ixmax = 101
			htitle = 'min. bias'
		else:
			ixmin = cent.BinRange(ic-1)[0]
			ixmax = cent.BinRange(ic-1)[1]
			htitle = 'centrality: {} {}'.format(ixmin, ixmax)
		proj = hnutil.get_projection_axis(hname, h2d, axis, ixmin, ixmax)
		hl.add(proj, htitle, 'hist l')
	return hl

def get_cent_slices(fname, hname):
	h2d = tu.get_object_from_file(hname, fname)
	if h2d==None:
		print '[error] no object named',hname,'in',fname
	hl = make_cent_slices(h2d)
	hl.scale(1./get_nev(fname))
	return hl

def show_cent_slices_noyats(fname, hname, logy=False, xmin=None, xmax=None, ymin=None, ymax=None):
	hl = get_cent_slices(fname, hname)
	hl.draw(miny=ymin, maxy=ymax, logy=logy)
	hl.zoom_axis(0, xmin, xmax)
	hl.self_legend()
	hl.update(logy=logy)
	tu.gList.append(hl)

def show_cent_slices(fname, hname, logy=False, xmin=None, xmax=None, ymin=None, ymax=None):
	lstore = dlist.ListStorage(fname+hname+'store')
	hl = get_cent_slices(fname, hname)
	hl.adjust_maxima(1e-5, 1e4, logy=True)
	#hl.rebin(2)
	hly = dlist.fractional_yats(hl)
	hly.adjust_maxima(1e-5, 2., logy=True)
	lstore.append(hl)
	lstore.append(hly)
	lstore.draw_all(logy=True)
	lstore.zoom_axis(0, xmin, xmax)
	lstore.set_grid_x()
	lstore.set_grid_y()
	lstore.set_log_axis('y')

def show_patches(fname, hnames, xmin=0, xmax=150):
	hlname = to_file_name(fname + 'show_patches' + '-'.join(hnames))
	ls 	= dlist.ListStorage(hlname)
	hlname = to_file_name(fname + 'show_patches' + '-'.join(hnames) + 'y')
	lsy = dlist.ListStorage(hlname)
	for hn in hnames:
		hl = get_cent_slices(fname, hn)
		ls.append(hl)	
		hly = dlist.fractional_yats(hl)
		lsy.append(hly)
		rejection_table(hly, rej=1e-3)
		#rejection_table(hly, rej=1e-2)

	if '--show-all' in sys.argv:
		ls.draw_all(logy=True)
		ls.zoom_axis(0, 0, 150)
		ls.set_grid_x()
		ls.set_grid_y()
		ls.set_log_axis('y')

	lsy.legend_position(x1=0.4,y1=0.5,x2=0.8,y2=0.87)
	lsy.draw_all(logy=True, miny=5e-5, maxy=5)
	lsy.zoom_axis(0, xmin, xmax)
	lsy.set_grid_x()
	lsy.set_grid_y()
	lsy.set_log_axis('y')

	if '--print' in sys.argv:
		lsy.pdf()

def show_2d(fname, hnames, thr=[18,14,11,8,7,10]):
	cent = [5,15,30,50,70,90]
	gr = dlist.make_graph_xy('thresholds'+fname, thr, cent)
	for hn in hnames:
		h = tu.get_object_from_file(hn, fname)
		hlname = fname + '-' + hn + '-' + '-'.join(str(t) for t in thr) 
		hlname = to_file_name(hlname)
		hl = dlist.dlist(hlname)
		hl.make_canvas()
		hl.add(h, hn, 'colz')
		hl.zoom_axis(0, -25, 30)
		hl.draw(miny=1e-3, maxy=1e8)
		ROOT.gPad.SetLogz()
		ROOT.gPad.Update()
		tu.gList.append(hl)
		gr.SetLineColor(2)
		gr.SetLineWidth(2)
		gr.Draw('L')
		tu.gList.append(gr)
		ROOT.gPad.Update()
		if '--print' in sys.argv:
			hl.pdf()


def show_mb_stats(fname, nev=150.e6, thr=[14, 18, 14, 11, 8, 7, 10]):
	cent = centrality.Centrality()
	hlname = fname + '-mb-stats'
	hlname = to_file_name(hlname)
	hl = dlist.dlist(hlname)
	nevgen = get_nev(fname)
	irebin = 10
	for i in range(0, 7):
		hname = 'hEptC{}diffjw'.format(i)
		print hname
		h2d = tu.get_object_from_file(hname, fname)
		ixmin = thr[i]
		ixmax = 300
		axis  = 0
		hname1 = '{}-{}-cut'.format(hname, i)
		proj1 = hnutil.get_projection_axis(hname1, h2d, axis, ixmin, ixmax)
		proj1.Rebin(irebin)
		hname2 = '{}-{}-uncut'.format(hname, i)
		proj2 = hnutil.get_projection_axis(hname2, h2d, axis, h2d.GetYaxis().GetXmin(), h2d.GetYaxis().GetXmax())
		proj2.Rebin(irebin)
		if i == 0:
			cs = 'min. bias [{:1.1f}M]'.format(nev/1e6)
			print 'TAAmb is',cent.TAAmb()
			proj1.Scale(1./irebin * cent.TAAmb() * nev / nevgen)
			proj2.Scale(1./irebin * cent.TAAmb() * nev / nevgen)			
		else:
			cs = cent.Label(i-1)
			proj1.Scale(1./irebin * cent.TAA(i-1) * nev / nevgen)
			proj2.Scale(1./irebin * cent.TAA(i-1) * nev / nevgen)			
		hl.add(proj1, cs, 'l')
		#hl.add(proj2, cs, 'l noleg -k -l')
	hl.make_canvas(600,600)
	hl.zoom_axis(0, 20, 140)
	hl.draw(miny=1e-1, maxy=5e5)
	ROOT.gPad.SetLogy()
	hl.reset_axis_titles('jet p_{T}', 'dN/dp_{T}')
	hl.self_legend(y1=0.55, y2=0.8)
	ROOT.gPad.SetGridy()
	ROOT.gPad.SetGridx()	
	ROOT.gPad.Update()
	tu.gList.append(hl)
	if '--print' in sys.argv:
		hl.pdf()

def show_bias(fname, thr=[14, 18, 14, 11, 8, 7, 10]):
	cent = centrality.Centrality()
	hlname = fname + '-bias-' + '-'.join(str(t) for t in thr) 
	hlname = to_file_name(hlname)
	hl = dlist.dlist(hlname)
	for i in range(0, 7):
		hname = 'hEptC{}diffjw'.format(i)
		print hname
		h2d = tu.get_object_from_file(hname, fname)
		ixmin = thr[i]
		ixmax = 300
		axis  = 0
		hname1 = '{}-{}-cut'.format(hname, i)
		proj1 = hnutil.get_projection_axis(hname1, h2d, axis, ixmin, ixmax)
		proj1.Rebin(10)
		hname2 = '{}-{}-uncut'.format(hname, i)
		proj2 = hnutil.get_projection_axis(hname2, h2d, axis, h2d.GetYaxis().GetXmin(), h2d.GetYaxis().GetXmax())
		proj2.Rebin(10)
		hlr   = dlist.make_ratio(proj1, proj2)
		if i == 0:
			cs = 'min. bias [{}]'.format(ixmin)
		else:
			cs = cent.Label(i-1) + ' [{}]'.format(ixmin)
		hl.add(hlr[0].obj, cs, 'l')

	hl.make_canvas(600,600)
	hl.zoom_axis(0, 0, 140)
	#hl.draw(miny=1e-5, maxy=1e8)
	hl.draw(miny=0, maxy=1.2)
	#ROOT.gPad.SetLogy()
	hl.reset_axis_titles('jet p_{T}', 'cut / unbiased')
	hl.self_legend(y1=0.35, y2=0.6)
	ROOT.gPad.SetGridy()
	ROOT.gPad.SetGridx()	
	ROOT.gPad.Update()
	tu.gList.append(hl)
	if '--print' in sys.argv:
		hl.pdf()


def show_some_patches(fname):
	hnames = [
		'hEJEcentw', # all patches
		#'hEJEdiffcentw', # all patches: Ei-median
		#'hEJEmaxw', # max - single per event
		'hEJEmedw', # median - single per event
		'hDJEmedw', # median - single per event		
		#'hEJEdiffmaxmedw' # max-median - single per event
		]
	for i, hn in enumerate(hnames):
		show_cent_slices(fname, hn, logy=True, xmin=-20, xmax=60)

def show_stats(fname, nev=150.e6, tname='tnjet', title='jets EMC', cal=0, xmax=200):
	cent = centrality.Centrality()
	hlname = fname + '-{:1.1f}'.format(nev/1.e6)
	hlname = to_file_name('-'.join([hlname, tname, str(cal)]))
	hl = dlist.dlist(hlname)
	nevgen = get_nev(fname)
	irebin = 10
	hl.make_canvas(600,600)
	nevgen = get_nev(fname)	
	for i,taa in enumerate(cent.TAAs()):
		print taa, i
		cut = '(cent >= {} && cent < {} && cal=={}) * (xsec)'.format(cent.BinLow(i), cent.BinHigh(i), cal)
		print cut
		var = 'jpt'
		bwidth = 20.
		xmin = 0
		h = tu.draw_h1d_from_ntuple(fname, tname, var, cut, bwidth, xmin, xmax)
		if h == None:
			continue
		h.Scale(taa * nev / nevgen / cent.BinWidth(i))
		#htitle = '{} {}'.format(tname, cut)
		htitle = '{} {} [{:1.0f} M]'.format(cent.BinLow(i), cent.BinHigh(i), nev * cent.BinWidth(i)/1.e6)
		hl.add(h, htitle, 'hist l')
		print '[i]',htitle,h.GetEntries()
	hl.draw(logy=True, maxy=8e8)
	hl.reset_axis_titles('p_{T}', 'dN/dp_{T}')
	hl.self_legend(1, title)
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hl.update(logy=True)
	tu.gList.append(hl)		
	if '--print' in sys.argv:
		hl.pdf()

if __name__ == '__main__':
	tu.setup_basic_root()
	fname = tu.get_arg_with('--in')
	if fname == None:
		#fname = './test-list.outputs/out-0.root'
		print "usage:",__file__,'--in <file.root>'
		exit(1)

	if '--patch' in sys.argv:
		hnames = [ 	'hEJEcentw', 'hDJEcentw', 
					'hEGAcentw', 'hDGAcentw']
		show_patches(fname, hnames, 0., 150)
		hnames = [	'hEJEmedw', 'hDJEmedw',
					'hEJEmaxw', 'hDJEmaxw']
		show_patches(fname, hnames, 0., 150)				

		hnames = [ 	'hEJEdiffcentw', 'hDJEdiffcentw',
					'hEJEdiffmaxmedw', 'hDJEdiffmaxmedw']
		show_patches(fname, hnames, -10., 150)

	if '--bias' in sys.argv:
		hnames = [ 'hEJEdiffcentw' ]
		if 'mtune1.2' in fname:
			show_2d(fname, hnames, thr=[23, 19, 14, 9, 8, 11])
			show_bias(fname, thr=[18, 23, 19, 14, 9, 8, 11])
		else:
			show_2d(fname, hnames, thr=[18, 14, 11, 8, 7, 10])
			show_bias(fname, thr=[14, 18, 14, 11, 8, 7, 10])

	#show_mb_stats(fname)
	#show_stats(fname)
	sigmaPbPb = 7.7 # barns
	intLumi = 220. * 1.e6 # 1/b
	nevPbPb = intLumi * sigmaPbPb
	show_stats(fname, nevPbPb, 'tnjet', 'anti-kT R=0.4 EMC', 0)
	show_stats(fname, nevPbPb, 'tnjet', 'anti-kT R=0.4 DMC', 1)
	show_stats(fname, nevPbPb, 'tnjetr', 'anti-kT R=0.2 EMC', 0)
	show_stats(fname, nevPbPb, 'tnjetr', 'anti-kT R=0.2 DMC', 1)

	show_stats(fname, nevPbPb, 'tnpi0', '#pi^{0} EMC', 0, 100)
	show_stats(fname, nevPbPb, 'tnpi0', '#pi^{0} DMC', 1, 100)

	fname = fname.replace('qcd-', 'pho-')
	show_stats(fname, nevPbPb, 'tng', '#gamma EMC', 0, 100)
	show_stats(fname, nevPbPb, 'tng', '#gamma DMC', 1, 100)

	#show_cent_slices(fname, 'hEJEcentw', logy=True, xmin=0, xmax=70, ymin=1e-1, ymax=1e6)
	#show_cent_slices(fname, 'hEJEcentn', logy=True, xmin=0, xmax=70, ymin=1e-2, ymax=1e4)

	if not ut.is_arg_set('-b'):
		IPython.embed()

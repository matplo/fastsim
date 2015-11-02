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

def show_patches(fname, hnames):
	ls 	= dlist.ListStorage(fname + 'show_patches' + '-'.join(hnames))
	lsy = dlist.ListStorage(fname + 'show_patches' + '-'.join(hnames) + 'y')
	for hn in hnames:
		hl = get_cent_slices(fname, hn)
		ls.append(hl)	
		hly = dlist.fractional_yats(hl)
		lsy.append(hly)

	if '--show-all' in sys.argv:
		ls.draw_all(logy=True)
		ls.zoom_axis(0, 0, 150)
		ls.set_grid_x()
		ls.set_grid_y()
		ls.set_log_axis('y')

	lsy.legend_position(x1=0.6,y1=0.5,x2=0.8,y2=0.87)
	lsy.draw_all(logy=True, miny=5e-5, maxy=5)
	lsy.zoom_axis(0, 0, 80)
	lsy.set_grid_x()
	lsy.set_grid_y()
	lsy.set_log_axis('y')

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

if __name__ == '__main__':
	tu.setup_basic_root()
	fname = tu.get_arg_with('--in')
	if fname == None:
		#fname = './test-list.outputs/out-0.root'
		print "usage:",__file__,'--in <file.root>'
		exit(1)
	print fname
	hnames = [	'hEJEmedw', 'hDJEmedw',
				'hEJEmaxw', 'hDJEmaxw']
	show_patches(fname, hnames)				
	hnames = [ 	'hEJEcentw', 'hDJEcentw', 
				'hEJEdiffcentn', 'hDJEdiffcentn']				
	show_patches(fname, hnames)

	#show_cent_slices(fname, 'hEJEcentw', logy=True, xmin=0, xmax=70, ymin=1e-1, ymax=1e6)
	#show_cent_slices(fname, 'hEJEcentn', logy=True, xmin=0, xmax=70, ymin=1e-2, ymax=1e4)

	if not ut.is_arg_set('-b'):
		IPython.embed()

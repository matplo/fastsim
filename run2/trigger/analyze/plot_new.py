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
		hl.add(proj, htitle, 'p')
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
	hly = dlist.fractional_yats(hl)
	lstore.append(hl)
	lstore.append(hly)
	lstore.draw_all(logy=True)
	lstore.zoom_axis(0, xmin, xmax)
	lstore.set_grid_x()
	lstore.set_grid_y()
	lstore.update(logy=True)
	
def show_patches(fname):
	hnames = [
		'hEJEcentw',
		'hEJEmedw',
		'hEJEdiffcentw',
		'hEJEdiffmaxmedw',
		'hEGAcentw',
		'hEGAdiffcentw']
	for i, hn in enumerate(hnames):
		show_cent_slices(fname, hn, logy=True, xmin=0, xmax=None)

if __name__ == '__main__':
	fname = './test-list.outputs/out-0.root'
	show_patches(fname)
	#show_cent_slices(fname, 'hEJEcentw', logy=True, xmin=0, xmax=70, ymin=1e-1, ymax=1e6)
	#show_cent_slices(fname, 'hEJEcentn', logy=True, xmin=0, xmax=70, ymin=1e-2, ymax=1e4)

	if not ut.is_arg_set('-b'):
		IPython.embed()

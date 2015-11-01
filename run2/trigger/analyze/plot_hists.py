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
import hnutil
import tutils as tu

def n2w(s, w=True):
	if w==True:
		s = s[:-1] + 'w'
	else:
		s = s[:-1] + 'n'
	return s

def E2D(s, which='EMC'):
	idx = len(s) - 2
	if which=='EMC':
		s = 'hE' + s[-idx:]
	else:
		s = 'hD' + s[-idx:]
	return s

def ptjets(fname, which='EMC', trig='JE', w=True):
	hnamesJE = ['hEptcentmedjn',
				'hEptcentmaxjn']
	hnamesGA = ['hEptcentmedgn',
				'hEptcentmaxgn']
	hnames = hnamesJE
	if trig == 'GA':
		hnames = hnamesGA
	cent = centrality.Centrality()
	for hn in hnames:
		hn = n2w(hn, w)
		hn = E2D(hn, which)
		print '[i] ::ptjets', hn
		h3d = tu.get_object_from_file(hn, fname, hn)
		hl = hnutil.Proj3to1d(h3d)
		y = [ [0, 100 ] ]
		z = [ [0, 1000] ]
		#jthr = [33, 27, 21, 16, 14, 13]
		jthr = [0, 10, 10, 10, 10, 10, 10]
		for i,cL in enumerate(cent.Labels()):
			#print cL
			y.append(cent.BinRange(i))
			z.append([jthr[i], 1000])
		hl.get_projections_axis(0, y, z, nrebin=2)
		for i,h in enumerate(hl.ls.lists[-1].l):
			if i==0:
				continue
			h.obj.Scale(1./cent.BinWidth(i+1))
		hl.ls.lists[-1].zoom_axis(0, 0, 70)
		hl.ls.lists[-1].adjust_maxima(1e7, 1e-3)

		hl.ls.append(hl.ls.lists[-1].ratio_to(0))
		hl.ls.lists[-1].zoom_axis(0, 0, 70)
		hl.ls.lists[-1].adjust_maxima(0, 2)

		hl.ls.legend_position(0.25, 0.5, 0.8, 0.9)
		hl.ls.draw_all(logy=False)
		for ip in [ hl.ls.tcanvas.cd(i+1) for i in range(len(hl.ls.lists)) ]:
			ip.SetGridx()
			ip.SetGridy()
		hl.ls.update()
		#show ratios here

def patches(fname, which='EMC', trig='JE', w=True):
	hnames = ['hEJEcentn']
	cent = centrality.Centrality()
	for hn in hnames:
		h2d = tu.get_object_from_file(hn, fname, hn)
		hl = hnutil.Proj3to1d(h2d)
		y = []
		for i,cL in enumerate(cent.Labels()):
			y.append(cent.BinRange(i))
			#y.append([0,100])
		hl.get_projections_axis(0, y, None, nrebin=1)
		hl.ls.lists[-1].zoom_axis(0, 0, 70)
		hl.ls.append(hnutil.fractional_yats(hl.ls.lists[-1]))
		hl.ls.lists[-1].zoom_axis(0, 0, 70)

		hl.ls.legend_position(0.25, 0.5, 0.8, 0.9)
		hl.ls.draw_all(logy=True)
		for ip in [ hl.ls.tcanvas.cd(i+1) for i in range(len(hl.ls.lists)) ]:
			ip.SetGridx()
			ip.SetGridy()
		hl.ls.lists[-2].adjust_maxima(1., 1e9)
		hl.ls.lists[-1].adjust_maxima(1e-7, 10)
		hl.ls.update()

def main():
	hardQCDfile = '/Users/ploskon/data/2015-10-31/mtune1/hardQCD.root';
	ptjets(hardQCDfile)
	#patches(hardQCDfile)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

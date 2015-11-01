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
		y = []
		z = []
		jthr = [33, 27, 21, 16, 14, 13]
		for i,cL in enumerate(cent.Labels()):
			#print cL
			y.append(cent.BinRange(i))
			z.append([jthr[i], 1000])
		hl.get_projections_axis(0, y, z, nrebin=10)
		hl.ls.legend_position(0.25, 0.5, 0.8, 0.9)
		hl.ls.draw_all()
		ROOT.gPad.SetLogy()
		hl.ls.update()
		#show ratios here
		
def main():
	hardQCDfile = '/Users/ploskon/data/2015-10-31/mtune1/hardQCD.root';
	ptjets(hardQCDfile)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

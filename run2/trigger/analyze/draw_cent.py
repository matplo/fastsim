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
import draw_utils as du

from plots_23Oct2015 import *
from plots import *

def med_correl(fname, vary='medj', ntname = 'jets_hard_EMCc', maxy=100, centbins=True, modname=''):

	var = '{}:npart'.format(vary)
	xbwidth = 1
	xlow = 0
	xhigh = 100
	ybwidth = 1
	ylow = 0
	yhigh = maxy
	cuts = '(1)*(xsec)'
	title = cuts + ';centrality;{}'.format(vary)
	modnames = cuts + modname
	tu.getTempCanvas().cd()
	h2all = tu.draw_h2d_from_ntuple(fname, ntname, var, cuts, 
    	       	        	      	xbwidth, xlow, xhigh, 
	    	        	    		ybwidth, ylow, yhigh,                          
            	    	        	title, modnames)
	tu.gList.append(h2all)
	title = '{}_centrality: {}%-{}% {} {} {}'.format(var, 0, 100, ntname, vary, modname)
	tc = du.canvas(title, title, 600, 600)
	tc.tcanvas.cd()
	h2all.GetYaxis().SetTitleOffset(1.2)
	h2all.Draw('colz')

	du.draw_comment('centrality: {}%-{}%'.format(0, 100))
	ROOT.gPad.SetLogz()
	ROOT.gPad.Update()

	if centbins==False:
		return h2all, tc

	cent = centrality.Centrality()
	for ib,taa in enumerate(cent.TAAs()):
		usercut='((npart >= {}) && (npart < {}))'.format(cent.BinLow(ib), cent.BinHigh(ib))	
		cuts = '({})*(xsec)'.format(usercut)
		title = cuts + 'centrality;{}'.format(vary)
		modname = cuts
		tu.getTempCanvas().cd()
		h2allc = tu.draw_h2d_from_ntuple(fname, ntname, var, cuts, 
    		       	        	      	xbwidth, xlow, xhigh, 
	    		        	    		ybwidth, ylow, yhigh,                          
            		    	        	title, modname)
		h2allc.SetLineColor(2)
		tu.gList.append(h2allc)
		title = '{}_centrality: {}%-{}% {} {}'.format(var, cent.BinLow(ib), cent.BinHigh(ib), ntname, vary)
		title = to_file_name(title)
		tc = du.canvas(title, title, 600, 600)
		tc.tcanvas.cd()
		h2all.GetYaxis().SetTitleOffset(1.2)
		h2all.Draw('colz')
		h2allc.Draw('cont2 same')
		du.draw_comment('centrality: {}%-{}%'.format(cent.BinLow(ib), cent.BinHigh(ib)))
		ROOT.gPad.SetLogz()
		ROOT.gPad.Update()

		if '--print' in sys.argv:
			tc.pdf()

	if '--print' in sys.argv:
		tc.pdf()

	return h2all

def max_med_correl(fname, varx='medj', vary='maxj', ntname = 'jets_hard_EMCc'):

	var = '{}:{}'.format(vary,varx)
	xbwidth = 1
	xlow = 0
	xhigh = 100
	ybwidth = 1
	ylow = 0
	yhigh = 100
	cuts = '(1)*(xsec)'
	#title = cuts + ';median {JE_{DCal_{i}}}; max {JE_{EMCal_{i}}}'
	title = cuts + ';{};{}'.format(varx, vary)
	modname = cuts
	tu.getTempCanvas().cd()
	h2all = tu.draw_h2d_from_ntuple(fname, ntname, var, cuts, 
    	       	        	      	xbwidth, xlow, xhigh, 
	    	        	    		ybwidth, ylow, yhigh,                          
            	    	        	title, modname)
	#h2all.SetMinimum(1e-3)
	tu.gList.append(h2all)
	title = 'max_med_centrality: {}%-{}% {} {}:{}'.format(0, 100, ntname, varx, vary)
	tc = du.canvas(title, title, 600, 600)
	tc.tcanvas.cd()
	h2all.GetYaxis().SetTitleOffset(1.2)
	h2all.Draw('colz')

	du.draw_comment('centrality: {}%-{}%'.format(0, 100))
	ROOT.gPad.SetLogz()
	ROOT.gPad.Update()
	if '--print' in sys.argv:
		tc.pdf()

	cent = centrality.Centrality()
	for ib,taa in enumerate(cent.TAAs()):
		usercut='((npart >= {}) && (npart < {}))'.format(cent.BinLow(ib), cent.BinHigh(ib))	
		cuts = '({})*(xsec)'.format(usercut)
		#title = cuts + ';median {JE_{DCal_{i}}}; max {JE_{EMCal_{i}}}'
		title = cuts + ';{};{}'.format(varx, vary)
		modname = cuts
		tu.getTempCanvas().cd()
		h2allc = tu.draw_h2d_from_ntuple(fname, ntname, var, cuts, 
    		       	        	      	xbwidth, xlow, xhigh, 
	    		        	    		ybwidth, ylow, yhigh,                          
            		    	        	title, modname)
		#h2allc.SetMinimum(1e-3)
		h2allc.SetLineColor(2)
		tu.gList.append(h2allc)
		title = 'max_med_centrality: {}%-{}% {} {}:{}'.format(cent.BinLow(ib), cent.BinHigh(ib), ntname, varx, vary)
		title = to_file_name(title)
		tc = du.canvas(title, title, 600, 600)
		tc.tcanvas.cd()
		h2all.GetYaxis().SetTitleOffset(1.2)
		h2all.Draw('colz')
		h2allc.Draw('cont2 same')
		du.draw_comment('centrality: {}%-{}%'.format(cent.BinLow(ib), cent.BinHigh(ib)))
		ROOT.gPad.SetLogz()
		ROOT.gPad.Update()

		if '--print' in sys.argv:
			tc.pdf()

def special():
	h2d,tc = med_correl(fname, 'maxj-medj', maxy=50, centbins=False)
	hl  = draw_thresholds('JE', True, noxe=True, dopt='l')
	hl.draw(maxy=50, miny=0)
	hl.self_legend()
	if '--print' in sys.argv:
		hl.pdf()
	h2d.Draw('same col')
	for o in hl.l:
		o.obj.Draw('same l')
	hl.self_legend()
	ROOT.gPad.SetLogz()
	if '--print' in sys.argv:
		hl.name = hl.name + '2d'
		hl.pdf()

def specialGA():
	h2d,tc = med_correl(fname, 'maxg-medj/16.', maxy=50, centbins=False)
	hl  = draw_thresholds('GA', True, noxe=True, dopt='l')
	hl.draw(maxy=15, miny=0)
	hl.self_legend()
	if '--print' in sys.argv:
		hl.pdf()
	h2d.Draw('same col')
	for o in hl.l:
		o.obj.Draw('same l')
	hl.self_legend()
	ROOT.gPad.SetLogz()
	if '--print' in sys.argv:
		hl.name = hl.name + '2d'
		hl.pdf()

if __name__ == '__main__':
	tu.setup_basic_root()

	bdir = ''
	bdir = tu.get_arg_with('--dir')

	ntfs  = NTFiles(bdir)
	photons = False
	femc = 0.3
	#femc = 1.0
	R=0.4
	usercut='(1)'
	cal='all'
	var='pT'
	fname = ntfs.get_file(femc, photons, R)

	if '--special' in sys.argv:
		special()
		specialGA()

	#med_correl(fname, 'medj')
	#med_correl(fname, 'maxj')
	#med_correl(fname, 'maxg')
	#med_correl(fname, 'maxj-medj')

	#max_med_correl(fname, 'medj', 'maxj')
	##max_med_correl(fname, 'medj', 'pT + medj')
	##max_med_correl(fname, 'maxj', 'pT+rho*0.5')

	#max_med_correl(fname, 'JEmedDCAL', 'JEmaxECAL', 'triggers')

	if not ut.is_arg_set('-b'):
		IPython.embed()

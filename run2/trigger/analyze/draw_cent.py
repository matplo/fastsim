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

class NTFiles(object):
	def __init__(self, adir=''):
		self.basedir = adir
		if adir=='' or adir==None:
			self.basedir=self._guess_dir()
		print '[i] basedir:',self.basedir
		if os.path.isdir(self.basedir)==False:
			print >> sys.stderr, '[w] basedir is not a directory:',self.basedir
		self.files= [
			'default_emctrig_out_R_0.4_femc_0.3.root',
			'default_emctrig_out_R_0.4_femc_1.0.root'
			]

	def _guess_dir(self):
		sdirs = [
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-26',
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-23/5TeV/hardQCD',
			'/Volumes/MP/data/run2/trigger/2015-10-23/5TeV/hardQCD',
			'/Users/ploskon/devel/sandbox/run2/trigger/generate/5TeV/hardQCD/mult-0',
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-22/5TeV',
			'/Volumes/MP/data/run2/trigger/2015-10-22/5TeV' 
			]
		for s in sdirs:
			if os.path.isdir(s):
				print '[i] NTFiles: basedir guessed:',s
				return s
		print >> sys.stderr, '[w] NTFiles: basedir not guessed. set :basedir manually. using os.getcwd()'
		return os.getcwd()

	def nfiles(self):
		return len(self.files)

	def get_file(self, femc=1.0, photons=False, R=0.4):
		retval = os.path.join(self.basedir, self.files[0])
		if femc < 1.0:
			retval = retval.replace("femc_1.0", "femc_{}".format(femc))
		if photons == True:
			retval = retval.replace("_hardQCD_", "_photons_")
		if R!=0.4:
			retval = retval.replace("_R_0.4_", "_R_0.2_")
		if os.path.isfile(retval)==False:
			print >> sys.stderr,'[e] not a file:',retval
			raise IOError(retval)
			retval = None
		return retval

def to_file_name(s):
	return "".join([x if x.isalnum() else "_" for x in s])

def med_correl(fname, vary='medj', ntname = 'jets_hard_EMCc'):

	var = '{}:npart'.format(vary)
	xbwidth = 1
	xlow = 0
	xhigh = 100
	ybwidth = 1
	ylow = 0
	yhigh = 100
	cuts = '(1)*(xsec)'
	title = cuts + ';centrality;{}'.format(vary)
	modname = cuts
	tu.getTempCanvas().cd()
	h2all = tu.draw_h2d_from_ntuple(fname, ntname, var, cuts, 
    	       	        	      	xbwidth, xlow, xhigh, 
	    	        	    		ybwidth, ylow, yhigh,                          
            	    	        	title, modname)
	tu.gList.append(h2all)
	title = '{}_centrality: {}%-{}% {} {}'.format(var, 0, 100, ntname, vary)
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

	med_correl(fname, 'medj')
	med_correl(fname, 'maxj')
	#med_correl(fname, 'maxj-medj')
	max_med_correl(fname, 'medj', 'maxj')
	#max_med_correl(fname, 'medj', 'pT + medj')
	#max_med_correl(fname, 'maxj', 'pT+rho*0.5')

	max_med_correl(fname, 'JEmedDCAL', 'JEmaxECAL', 'triggers')

	if not ut.is_arg_set('-b'):
		IPython.embed()

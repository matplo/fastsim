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

def get_var(h, cut=False):
	hname = h.GetName() + '_var'
	htitle = hname
	sum 	= 0
	nbins 	= 0
	for ibx in range(1, h.GetNbinsX() + 1):
		sum += h.GetBinContent(ibx)
		if h.GetBinContent(ibx) > 0:
			nbins += 1
	mean = sum / nbins
	print sum, nbins, mean

	minv = 0
	maxv = 0
	for ibx in range(1, h.GetNbinsX() + 1):
		if h.GetBinContent(ibx) > 0:
			v = h.GetBinContent(ibx) - mean
			if v < minv:
				minv = v
			if v > maxv:
				maxv = v

	hout = ROOT.TH1D(hname, htitle, int(nbins + 1) / 10, minv, maxv)
	for ibx in range(1, h.GetNbinsX() + 1):
		if h.GetBinContent(ibx) > 0:
			#v = ROOT.TMath.Power(h.GetBinContent(ibx) - mean, 2.)
			v = h.GetBinContent(ibx) - mean
			hout.Fill(v)

	print '[i] bad channels from:',h.GetName()
	rmscut = hout.GetRMS() * 3.
	newname = h.GetName() + '_map'
	hc = h.Clone(newname)
	for ibx in range(1, h.GetNbinsX() + 1):
		if h.GetBinContent(ibx) > 0:
			v = h.GetBinContent(ibx) - mean
			if v > rmscut:
				hc.SetBinContent(ibx, 0)
				print int(h.GetBinLowEdge(ibx)),',',
			else:
				hc.SetBinContent(ibx, 1)
	print 
	return hout,hc

def addRMStoTitle(hl):
	retv = []
	for o in hl.l:
		h = o.obj
		newTitle = '{} RMS={:.5f}'.format(h.GetTitle(), h.GetRMS())
		h.SetTitle(newTitle)
		retv.append(h.GetRMS())
	return retv

def main(fname):
	fin = ROOT.TFile.Open(fname)

	hl = dlist.dlist('hl')
	hl.add_from_file('histos/fHcellsN', fname, 'counts', 'hist')
	hl.add_from_file('histos/fHcellsW', fname, 'E-weighted', 'hist')
	hl.normalize_self(False)

	hl200 = dlist.dlist('hl200')
	hl200.add_from_file('histos/fHcellsN200', fname, '200/counts', 'hist')
	hl200.add_from_file('histos/fHcellsW200', fname, '200/E-weighted', 'hist')
	#hl.normalize_self(False, to_max=True)
	hl200.normalize_self(False)

	hls = dlist.ListStorage('bad_channels')

	hlrm = dlist.dlist('vars')
	hvs = get_var(hl[0].obj)
	hlrm.add(hvs[0], 'counts', draw_opt='hist')
	hls.add_to_list('maps', hvs[1], 'map counts', dopt='hist')
	hvs = get_var(hl[1].obj)
	hlrm.add(hvs[0], 'E-weighted', draw_opt='hist')
	hls.add_to_list('maps', hvs[1], 'map E-weighted', dopt='hist')
	hlrm.reset_axis_titles('x_{i} - mean')
	hlrm.normalize_self(False, to_max=True)
	rmss = addRMStoTitle(hlrm)

	hlrm200 = dlist.dlist('vars200')
	hvs = get_var(hl200[0].obj)
	hlrm200.add(hvs[0], '200/E counts', draw_opt='hist')
	hls.add_to_list('maps200', hvs[1], '200/map counts', dopt='hist')
	hvs = get_var(hl200[1].obj)
	hlrm200.add(hvs[0], '200/E-weighted', draw_opt='hist')
	hls.add_to_list('maps200', hvs[1], '200/map E-weighted', dopt='hist')
	hlrm200.reset_axis_titles('x_{i} - mean')
	hlrm200.normalize_self(False, to_max=True)
	rmss200 = addRMStoTitle(hlrm200)

	hls.prepend(hl)
	hls.prepend(hl200)
	hls.prepend(hlrm)
	hls.prepend(hlrm200)
	hls.legend_position(x1=0.3)
	hls.draw_all(logy=True, orient=1)

	hls.tcanvas.cd(2)
	for i, rms in enumerate(rmss):
		rmscut = rms * 3.
		du.draw_line(rmscut, 1., rmscut, 2.5, col=2-i, width=4, alpha=0.8, style=1)
		rmscut = rms * 2.
		du.draw_line(rmscut, 1., rmscut, 2.5, col=2-i, width=4, alpha=0.8, style=2)
		rmscut = rms * 1.
		du.draw_line(rmscut, 1., rmscut, 2.5, col=2-i, width=4, alpha=0.8, style=3)
	hls.tcanvas.cd(1)
	for i,rms in enumerate(rmss200):
		rmscut = rms * 3.
		du.draw_line(rmscut, 1., rmscut, 2.5, col=2-i, width=4, alpha=0.8, style=1)
		rmscut = rms * 2.
		du.draw_line(rmscut, 1., rmscut, 2.5, col=2-i, width=4, alpha=0.8, style=2)
		rmscut = rms * 1.
		du.draw_line(rmscut, 1., rmscut, 2.5, col=2-i, width=4, alpha=0.8, style=3)
	hls.set_grid_x()
	hls.update()

if __name__ == '__main__':
	tu.setup_basic_root()
	fname = ut.get_arg_with('--in')
	if fname==None:
		fname = 'Hist_AnalysisResults.root'
	main(fname)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

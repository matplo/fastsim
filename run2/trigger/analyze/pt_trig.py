#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math

def EMCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 110. / 360. * math.pi * 2.

	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)

	return retval

def DCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 80. / 360. * math.pi * 2. #not 70 deg?

	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)

	return retval

def get_h_pT(fname, ntname, medjcut = None, title=None, var='pT'):
	#draw_h1d_from_ntuple(fname, nntname, var, cuts, bwidth, xlow, xhigh, title=None, modname='')
	#var = 'maxj' 
	#var = 'pT'
	cuts   = "(abs(eta)<1 && nEv==-1)*(xsec)".format(medjcut)
	if medjcut != 'NA':
		cuts   = "(abs(eta)<1 && nEv==-1 && (maxj - medj) > {})*(xsec)".format(medjcut)
	print cuts
	bwidth = 1
	xlow   = 0
	xhigh  = 250

	if title == None:
		title  = '-'.join([fname, ntname, var, cuts])
	hltmp = dlist.dlist(title)

	h 	   = tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)

	hltmp.add(h, title, 'p E1')
	#hltmp.add(h, title, 'hist l E1')

	nEv = tu.get_max_from_ntuple(fname, ntname, 'nEv')
	if nEv<=0 or nEv==None:
		nEv = 10000. - 1.
	print '[i] scaling by nEv: ', nEv+1.
	hltmp.scale(1./(nEv * 1. + 1.))
	hltmp.update()

	tu.gList.append(hltmp)

	return hltmp

def make_hl_name(files = [], ntuples = []):
	fs  = ut.remove_duplicates(files)
	nts = ut.remove_duplicates(ntuples)
	hlname = 'fs-' + '-'.join(f for f in fs) + 'nts-' + '-'.join(nt for nt in nts)
	hlname = hlname.replace("default_emctrig_out", "").replace(".root", "")
	return hlname

def compare_jet_pt(files = [], ntuples=[], titles=[]):

	hlname = 'compare_jet_pt_' + make_hl_name(files, ntuples)

	hl = dlist.dlist(hlname)

	for i,fname in enumerate(files):
		print i, fname, ntuples[i]
		hltmp = get_h_pT(fname, ntuples[i], 'NA', titles[0])
		hl.add_list(hltmp)
		for medjcut in range(0, 40, 5):
			newtitle = '{} max-median > {}'.format(titles[i], medjcut)
			hltmp = get_h_pT(fname, ntuples[i], medjcut, newtitle)
			hl.add_list(hltmp)

	hl.reset_axis_titles('p_{T}', 'd#sigma/dp_{T} (mb/GeV)')
	hl.scale_by_binwidth(True)
	hl.make_canvas()
	ym = ut.get_arg_with('--ymin')
	if ym != None:
		ym = float(ym)
	else:
		ym = 2e-8
	hl.draw(miny=ym, logy=True)
	hl.self_legend(x1=0.6)
	ROOT.gPad.SetLogy()
	hl.update()
	tu.gList.append(hl)

	if ut.is_arg_set('--print'):
		hl.pdf()

	hlr = hl.ratio_to(0)
	hlr.make_canvas()
	hlr.draw(miny=0,maxy=2.0)
	hlr.self_legend(x1=0.3)
	hlr.update()

	tu.gList.append(hlr)

	if ut.is_arg_set('--print'):
		hlr.pdf()

	return hl

if __name__=="__main__":
    tu.setup_basic_root()

    args = []
    for i in range(1,7):
    	sarg = '--{}'.format(i)
    	tmp = ut.get_arg_with(sarg) 
    	if tmp != None:
	    	args.append(tmp)

    if len(args) < 1:
    	exit()

    fnames = []
    ntuples = []
    titles = []
    for s in args:
    	fnames.append(s.split(',')[0])
    	ntuples.append(s.split(',')[1])
    	titles.append(s.split(',')[2])

    hl = compare_jet_pt(fnames, ntuples, titles)
    if not ut.is_arg_set('-b'):
        IPython.embed()


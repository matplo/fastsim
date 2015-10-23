#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math
import sys
import atlas_jets

def get_pT(fname):
	ntuples = ['jets_hard_EMC']
	usercut = 'abs(eta)<0.5'
	var     = 'pT'
	bwidth  = 20
	xlow    = 0
	xhigh   = 500

	title  = '7TeVjets-pythia'
	hltmp = dlist.dlist(title)
	tu.getTempCanvas()
	for ntname in ntuples:
		title  = '7TeVjets-pythia-href'
		cuts    = "(nEv==-1 && {})".format(usercut)
		href 	= tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)
		title  = '7TeVjets-pythia'
		cuts    = "(nEv==-1 && {})*(xsec)".format(usercut)
		h 	   = tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)
		#tu.filter_single_entries(h, href, thr=10)
		#hltmp.add(h, ntname, 'p E1')
		hltmp.add(h, ntname, 'l hist')
		#hltmp.add(h, ntname, 'serror noleg +k1')
		#hltmp.add(h, ntname, 'serror noleg +k2')
		#hltmp.add(h, title, 'hist l E1')


		nEv = tu.get_max_from_ntuple(fname, ntname, 'nEv')
		if nEv<=0 or nEv==None:
			nEv = 10000. - 1.
		#print '[i] scaling by nEv: ', nEv+1.

	hltmp.reset_axis_titles('p_{T}', 'd#sigma/dp_{T} (pb/cGeV)')
	hltmp.scale_by_binwidth(True)
	hltmp.scale(1./(nEv * 1. + 1.) * 1.e9) # to pb

	#hltmp.destroy_canvas()

	return hltmp

if __name__ == '__main__':
	tu.setup_basic_root()
	hl = dlist.dlist('py_to_atlas')
	simhl = get_pT('/Volumes/SAMSUNG/data/run2/trigger/2015-10-23/7TeV/default_emctrig_out_R_0.2_femc_1.0.root')
	hl.add_list(simhl)
	simhl = get_pT('/Volumes/SAMSUNG/data/run2/trigger/2015-10-23/7TeV/default_emctrig_out_R_0.4_femc_1.0.root')
	hl.add_list(simhl)
	hl[0].obj.SetTitle('Pythia R=0.2')
	hl[1].obj.SetTitle('Pythia R=0.4')
	atlas = atlas_jets.AtlasJets()
	hl.add_list(atlas.get())
	hl.make_canvas(w=700,h=700)
	hl.zoom_axis(0, 100, 350)
	hl.draw(logy=True, miny=5., maxy=8e3)
	hl.self_legend()
	ROOT.gPad.SetLogy()
	hl.update()
	tu.gList.append(hl)
	if not tu.is_arg_set('-b'):
		IPython.embed()

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

from plots_23Oct2015 import *

def draw_thresholds(t='JE', draw=True, noxe=False, dopt='p'):
	jethrs = [
		[33, 27, 21, 16, 14, 13],  # EMC 1e-3
		[28, 23, 18, 12,  8,  7],  # EMC 1e-2
		[32, 28, 21, 15, 12, 12],  # DMC 1e-3
		[27, 22, 17, 11,  8,  6] ] # DMC 1e-2

	gathrs = [
		[8, 8, 8, 8, 8, 8],  	# EMC 1e-3
		[7, 6, 6, 5, 5, 5],		# EMC 1e-2
		[8, 8, 7, 7, 7, 7],		# DMC 1e-3
		[7, 6, 6, 5, 4, 4] ]	# DMC 1e-2  

	hl = dlist.dlist('thresholds-{}'.format(t))
	cent = centrality.Centrality()

	names = [
		'JE EMC 1e-3',
		'JE EMC 1e-2',
		'JE DMC 1e-3',
		'JE DMC 1e-2'
		]

	for i in range(len(jethrs)):
		ns = names[i].replace('JE', t)
		print ns
		if t=='JE':
			if noxe==False:
				gr = dlist.make_graph_ae_xy(ns, cent.BinCenters(), jethrs[i], xlow=cent.BinLowsE(), xhigh=cent.BinHighsE())
			else:
				gr = dlist.make_graph_xy(ns, cent.BinCenters(), jethrs[i])
		else:
			if noxe==False:
				gr = dlist.make_graph_ae_xy(ns, cent.BinCenters(), gathrs[i], xlow=cent.BinLowsE(), xhigh=cent.BinHighsE())			
			else:
				gr = dlist.make_graph_xy(ns, cent.BinCenters(), gathrs[i])
		hl.add(gr, ns, dopt)

	hl.reset_axis_titles('centrality', 'threshold (GeV)')

	if draw==True:
		hl.make_canvas(600, 600)
		hl.draw()
		if t=='JE':
			hl.self_legend()
		else:
			hl.self_legend(1 ,'', 0.6170569,0.4013333,0.8177258,0.6513333)
		hl.update()

		if '--print' in sys.argv:
			hl.pdf()

	tu.gList.append(hl)

	return hl

if __name__ == '__main__':
	tu.setup_basic_root()

	bdir = ''
	bdir = tu.get_arg_with('--dir')

	ntfs  	= NTFiles(bdir)
	ntfsph = NTFiles('/Volumes/SAMSUNG/data/run2/trigger/2015-10-23/5TeV/hardQCD')

	photons = False
	femc = 0.3
	#femc = 1.0
	R=0.4
	usercut='(1)'
	cal='all'
	var='pT'

	if '--photons' in sys.argv:
		photons = True
		fname = ntfsph.get_file(femc, photons, R)

	if '--xsec' in sys.argv:
		draw_pT_xsec(fname, photons, femc, R, usercut, cal, var)
		draw_pT_xsec(fname, photons, femc, R, usercut, cal, var='medj')

	if '--yields' in sys.argv:
		intLumi = 220. * 1.e6
		femc = 0.3
		#femc = 1.0
		if '--photons' in sys.argv:
			cal = 'EMC'
			draw_AA_yield(fname, photons, femc, R, cal, var)
			draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)
			cal = 'DMC'
			draw_AA_yield(fname, photons, femc, R, cal, var)
			draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)
		else:
			for r in [0.4, 0.2]:
				R=r
				fname = ntfs.get_file(femc, photons, R)
				cal = 'EMC'
				draw_AA_yield(fname, photons, femc, R, cal, var)
				draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)
				cal = 'DMC'
				draw_AA_yield(fname, photons, femc, R, cal, var)
				draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)

	if '--trigger' in sys.argv:
		R=0.4
		femc = 0.3
		fname = ntfs.get_file(femc, photons, R)

		if '--je' in sys.argv:
			var='maxj-medj'
			draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')
			#var='JEmaxECAL-JEmedDCAL'
			#draw_trigger_rates(fname, photons, femc, R, var, 'triggers', 'EMC')
			var='maxj-medj'
			draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_DMCc', 'DMC')

		if '--ga' in sys.argv:
			var='maxg-medj/16.'
			draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')
			var='maxg-medj/16.'
			draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_DMCc', 'DMC')

	if '--bias' in sys.argv:
		var='pT'
		R=0.4
		R=0.2
		femc = 0.3
		fname = ntfs.get_file(femc, photons, R)

		if '--je' in sys.argv:
			threxp = 'maxj-medj'
			jethr = [33, 27, 21, 16, 14, 13] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp=threxp)
			jethr = [28, 23, 18, 12, 8, 7] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp=threxp)

			jethr = [32, 28, 21, 15, 12, 12] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'DMC', var, thrs=jethr, threxp=threxp)
			jethr = [27, 22, 17, 11, 8, 6] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'DMC', var, thrs=jethr, threxp=threxp)

		if '--ga' in sys.argv:
			threxp = 'maxg-medj/16.'
			jethr = [8, 8, 8, 8, 8, 8] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp=threxp)
			jethr = [7, 6, 6, 5, 5, 5] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp=threxp)

			jethr = [8, 8, 7, 7, 7, 7] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'DMC', var, thrs=jethr, threxp=threxp)
			jethr = [7, 6, 6, 5, 4, 4] #made with femc=0.3
			draw_bias(fname, photons, femc, R, 'DMC', var, thrs=jethr, threxp=threxp)

	if '--thresholds' in sys.argv:
			draw_thresholds('JE', True, noxe=True, dopt='l')
			draw_thresholds('GA', True, noxe=True, dopt='l')

	if not ut.is_arg_set('-b'):
		IPython.embed()

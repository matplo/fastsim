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
		femc = 0.3
		fname = ntfs.get_file(femc, photons, R)
		var='maxj-medj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')
		var='maxj-medj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_DMCc', 'DMC')

		var='maxg-medj/16.'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')
		var='maxg-medj/16.'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_DMCc', 'DMC')

	if not ut.is_arg_set('-b'):
		IPython.embed()

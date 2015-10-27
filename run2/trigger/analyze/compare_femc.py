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
from draw_cent import *

if __name__ == '__main__':
	tu.setup_basic_root()

	bdir = ''
	bdir = tu.get_arg_with('--dir')

	photons=False
	R=0.4
	var='pT'
	threxp = 'maxj-medj'
	jethr = [33, 27, 21, 16, 14, 13] #made with femc=0.3
	gBinSetupPt.bwidth = 15
	gBinSetupPt.xhigh  = 210

	if '--femc' in sys.argv:
		hl = dlist.dlist('compare_femc')
		for femc in [1.0, 0.7, 0.3]:
			fname = '/Users/ploskon/data/run2/2015-10-27/withmb-realbg-femc-x/default_emctrig_out_R_0.4_femc_0.3.root'.replace('femc_0.3', 'femc_{:.1f}'.format(femc))
			print fname
			hlr = draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp=threxp)
			hl.add(hlr[0].obj, 'E/p={:.1f}'.format(femc), 'hist l')
		hl.make_canvas(600, 600)
		hl.draw(maxy=1.2, miny=0)
		hl.self_legend()
		ROOT.gPad.SetGridx()
		ROOT.gPad.SetGridy()
		hl.update()

	for femc in [1.0, 0.7, 0.3]:
		fname = '/Users/ploskon/data/run2/2015-10-27/withmb-realbg-femc-x/default_emctrig_out_R_0.4_femc_0.3.root'.replace('femc_0.3', 'femc_{:.1f}'.format(femc))
		med_correl(fname, 'maxj', maxy=50, centbins=False, modname='compare_femc-{:.1f}'.format(femc))

	for femc in [1.0, 0.7, 0.3]:
		fname = '/Users/ploskon/data/run2/2015-10-27/withmb-realbg-femc-x/default_emctrig_out_R_0.4_femc_0.3.root'.replace('femc_0.3', 'femc_{:.1f}'.format(femc))
		var='medj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')
		var='maxj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')
		var='maxj-medj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc', 'EMC')

	if not ut.is_arg_set('-b'):
		IPython.embed()

#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math
import sys

def main(what=0, nrebin=1):
	hbname = 'ClusterEnergy'
	if what==1:
		hbname = 'EMCJEHOfflinePatchAmp'
	#ClusterEnergy_EMCal_EMCEJ1
	dets = ['EMCal', 'DCal']
	trigs = ['INT7', 'EG1', 'EJ1']
	
	fname = 'histos_000244982.root'

	lname = 'clusters'
	if what==1:
		lname = 'patches'
	hl = dlist.ListStorage(lname)
	for d in dets:
		for t in trigs:
			if what == 0:
				tname = t
				if t != 'INT7':
					tname = '{}MC{}'.format(d[:1], t)
				htitle = '{} {}'.format(d, t)
				hname = '{}_{}_{}'.format(hbname, d, tname)
			if what == 1:
				tname = 'JE'
				if 'EG' in t:
					tname = 'GA'
				else:
					tname = 'JE'
				hname = 'EMC{}HOnlinePatchAmp_{}_{}'.format(tname, d, t)
				if t != 'INT7':
					hname = 'EMC{}HOnlinePatchAmp_{}_{}MC{}'.format(tname, d, d[:1], t)
				print hname
				htitle = '{} {}'.format(d, t)
			hl.add_from_file(d, hname, fname, htitle, 'p')
			hl.get(d).last().obj.Rebin(nrebin)
			hl.get(d).last().obj.Scale(1./nrebin)
			scale = 1.
			if what==1:
				scale = 0.0785
				hl.get(d).last().obj.GetXaxis().SetTitle('patch energy (GeV)')
				xmin = hl.get(d).last().obj.GetXaxis().GetXmin() * scale
				xmax = hl.get(d).last().obj.GetXaxis().GetXmax() * scale
				hl.get(d).last().obj.GetXaxis().SetLimits(xmin, xmax)
	hl.draw_all(logy=True)

	hlr = dlist.ListStorage('ratios')
	for d in dets:
		l = hl.get(d)
		hret = l.ratio_to(0)
		hret.name = d
		hret.title = d + ' ' + fname.split('_')[1].replace('.root', '')
		hret.reset_axis_titles(yt='ratio')
		hlr.append(hret)

	return
	rejs = [
		[1, 4.5e-3, 1.6e-3], 
		[1, 3.0e-3, 5.0e-3]
		]

	#for 82
	rejs = [
		[1, 4.7e-3, 3.3e-3], 
		[1, 3.5e-3, 2.0e-3]
		]

	for idet, d in enumerate(dets):
		for itrig, t in enumerate(trigs):
			rej = rejs[idet][itrig]
			tname = t
			if t != 'INT7':
				tname = '{}MC{}'.format(d[:1], t)
			if rej < 1:
				fc = ROOT.TF1('fc', '{}'.format(rej), 0, 100)
				hlr.add_to_list(d, fc, 'rej.{} {}'.format(tname, rej), 'l +l1 +w3')
	hlr.legend_position(x1=0.4)
	hlr.draw_all(logy=True, maxy=2., miny=1e-3)
	hlr.set_grid_y()
	hlr.set_grid_x()
	hlr.update()

if __name__ == '__main__':
	tu.setup_basic_root()
	main(what=0)
	if '--patches' in sys.argv:
		main(what=1)
	if not ut.is_arg_set('-b'):
		IPython.embed()	

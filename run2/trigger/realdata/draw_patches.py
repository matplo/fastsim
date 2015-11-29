#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math
import sys

def main(nrebin=10):
	hbname = 'EMCJEHOfflinePatchAmp'
	dets = ['EMCal'] #, 'DCal']
	patch = ['GA', 'JE']
	trigs = ['INT7', 'EG1', 'EJ1']
	
	fname = 'histos_000244982.root'

	lname = 'patches'
	hl = dlist.ListStorage(lname)
	for d in dets:
		for t in trigs:
			for p in patch:
				if p=='GA' and t=='EJ1':
					continue
				if p=='JE' and t=='EG1':
					continue
				hname = 'EMC{}HOnlinePatchAmp_{}_{}'.format(p, d, t)
				if t != 'INT7':
					hname = 'EMC{}HOnlinePatchAmp_{}_{}MC{}'.format(p, d, d[:1], t)
				htitle = '{} {} {}'.format(d, t, p)
				print hname
				lname = '{}{}'.format(d, p)
				hl.add_from_file(lname, hname, fname, htitle, 'p')
				hl.get(lname).last().obj.Rebin(nrebin)
				hl.get(lname).last().obj.Scale(1./nrebin)
				scale = 0.0785
				hl.get(lname).last().obj.GetXaxis().SetTitle('patch energy (GeV)')
				xmin = hl.get(lname).last().obj.GetXaxis().GetXmin() * scale
				xmax = hl.get(lname).last().obj.GetXaxis().GetXmax() * scale
				hl.get(lname).last().obj.GetXaxis().SetLimits(xmin, xmax)
	hl.draw_all(logy=True)

	hlr = dlist.ListStorage('ratios')
	for l in hl.lists:
		hret = l.ratio_to(0, '')
		hret.name = l.name
		hret.title = l.name
		hret.reset_axis_titles(yt='ratio')
		hlr.append(hret)

	rejs = [
		[1, 4.5e-3, 1.6e-3], 
		[1, 3.0e-3, 5.0e-3]
		]

	#for 82
	rejs = [
		[1, 4.7e-3, 3.3e-3], 
		[1, 3.5e-3, 2.0e-3]
		]

	hlr.legend_position(x1=0.4)
	hlr.draw_all(logy=True, maxy=50., miny=1e-3)
	hlr.set_grid_y()
	hlr.set_grid_x()
	hlr.update()

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()	

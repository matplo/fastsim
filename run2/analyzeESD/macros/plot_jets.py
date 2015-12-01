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

import draw_ntuple

kOther = 1
kCINT7 = 2
kEJ1   = 4
kEG1   = 8
kDJ1   = 16
kDG1   = 32

def tbit(ttype):
	d = dict([('kOther' , 1),('kCINT7' , 2),('kEJ1' , 4),('kEG1' , 8),('kDJ1' , 16), ('kDG1' , 32)])
	return d[ttype]

def get_jets(indir, var='', cuts='', bwidth=5, xlow= 0, xhigh=300):
	print '[i] get_jets:',var
	tu.getTempCanvas().cd()
	ntname = 't'	
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir(indir, ntname, var, cuts, bwidth, xlow, xhigh, 
								title='h', modname='', nev=-1, fpatt='Tree_*.root')
	return hl.sum()

def get_n_events(indir, ttype, bwidth=100, xlow= 0, xhigh=300):
	cuts = 'trig.type & {}'.format(ttype)
	var =  'trig.type'
	ntname = 't'	
	tu.getTempCanvas().cd()
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir(indir, ntname, var, cuts, bwidth, xlow, xhigh, 
										title='h', modname='', nev=-1, fpatt='Tree_*.root')
	nentries = hl.sum().obj.GetEntries()
	print '[i] get_n_events:',var,cuts,nentries
	return nentries

def main_area_sub(dname):
	ls = dlist.ListStorage('jets')

	area = [ 0.0316*0.0316*ROOT.TMath.Pi(), 0.2*0.2*ROOT.TMath.Pi(), 0.4*0.4*ROOT.TMath.Pi()]
	for fdet in [0, 1]:
		for ij,jets in enumerate([ 'jets00.fE', 'jets02.fE', 'jets04.fE' ]):
			for ttype in ['kCINT7', 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
				bit = tbit(ttype)
				if fdet == 0 and 'kD' in ttype: continue
				if fdet == 1 and 'kE' in ttype: continue
				detcondition = jets.replace('.fE', '.fDet=={}'.format(fdet))
				sdet = 'EMCAL'
				if fdet > 0: sdet = 'DCAL'
				print '    ',sdet,detcondition,ttype,jets
				median = 'trig.medjECAL8x8/0.05'
				if fdet == 0:
					median = 'trig.medjDCAL8x8/0.05'
				var = '{} - {} * {}'.format(jets, median, area[ij])
				h = get_jets(dname, var, '(trig.type & {})&&({})'.format(bit, detcondition), xlow=-200)
				h.obj.Scale(1./get_n_events(dname, bit))
				ls.add_to_list(sdet+' '+jets+'_m', h, '{} {}'.format(ttype, sdet), 'hist')

	ls.draw_all(logy=True)
	ls.pdf()
	ls.write_all(mod='modn:')

def main(dname):
	ls = dlist.ListStorage('jets')

	for fdet in [0, 1]:
		for ij,jets in enumerate([ 'jets00.fE', 'jets02.fE', 'jets04.fE' ]):
			for ttype in ['kCINT7', 'kEJ1', 'kEG1', 'kDJ1', 'kDG1']:
				bit = tbit(ttype)
				if fdet == 0 and 'kD' in ttype: continue
				if fdet == 1 and 'kE' in ttype: continue
				detcondition = jets.replace('.fE', '.fDet=={}'.format(fdet))
				sdet = 'EMCAL'
				if fdet > 0: sdet = 'DCAL'
				print '    ',sdet,detcondition,ttype,jets
				h = get_jets(dname, jets, '(trig.type & {})&&({})'.format(bit, detcondition), xlow=0)
				h.obj.Scale(1./get_n_events(dname, bit))
				ls.add_to_list(sdet+' '+jets, h, '{} {}'.format(ttype, sdet), 'hist')

	ls.draw_all(logy=True)
	ls.pdf()
	ls.write_all(mod='modn:')

def draw():
	rebin = ut.get_arg_with('--rebin')
	if rebin != None:
		rebin = int(rebin)
	files = [
		'EMCAL_jets04.fE.root',
		'EMCAL_jets02.fE.root',
		'EMCAL_jets00.fE.root',
		'DCAL_jets04.fE.root',
		'DCAL_jets02.fE.root',
		'DCAL_jets00.fE.root' ]

	ls = dlist.ListStorage('jets_draw')
	lsr = dlist.ListStorage('jets_draw_ratios')

	for fn in files:
		hl = dlist.dlist(fn)
		hl.add_from_file('o_0', fn, 'kCINT7', 	'hist')
		hl.add_from_file('o_1', fn, 'JE', 		'hist')
		hl.add_from_file('o_2', fn, 'GA', 		'hist')
		if rebin:
			hl.rebin(rebin)
			hl.scale(1./rebin)
		hl.reset_axis_titles('raw e.m. energy (GeV)', '1/N_{ev} dN/dE (c/Gev)')
		hl.scale_by_binwidth()
		ls.append(hl)

		hlr = hl.ratio_to(0, 'hist')
		hlr.title = hl.title.split(' ')[0].replace('.root', '')
		lsr.append(hlr)

	ls.draw_all(logy=True)
	lsr.draw_all(logy=True, maxy=2.e5)
	if '--print' in sys.argv:
		ls.pdf()
		lsr.pdf()

if __name__ == '__main__':
	tu.setup_basic_root()
	envdir = os.getenv('RUN2AESDDIR')
	libs = ['libEMCALTriggerFast', 'libRAnalyzeESD']
	for l in libs:
		lib = os.path.join(envdir, 'lib', l)
		ROOT.gSystem.Load(lib)
	dname = ut.get_arg_with('--in')
	if dname==None:
		dname = './245146'
	if '--make' in sys.argv:
		main(dname)
	if '--draw' in sys.argv:
		draw()
	if not ut.is_arg_set('-b'):
		IPython.embed()	

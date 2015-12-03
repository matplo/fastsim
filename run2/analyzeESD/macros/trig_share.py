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

def get_n_events(indir, cuts, bwidth=100, xlow= 0, xhigh=300):
	var =  'trig.type'
	ntname = 't'	
	tu.getTempCanvas().cd()
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir(indir, ntname, var, cuts, bwidth, xlow, xhigh, 
										title='h', modname='', nev=-1, fpatt='Tree_*.root')
	nentries = hl.sum().obj.GetEntries()
	print '[i] get_n_events:',var,cuts,nentries
	return nentries

def AND_trig_condition(cond, *conds):
	form = '(type & {})'
	sret = form.format(tbit(cond))
	for c in conds:
		sret += ' && ' + form.format(tbit(c))
	sret = '({})'.format(sret)
	return sret 

def main(dname):
	tcond = []
	tcond.append('((type & {}))'.format(tbit('kCINT7')))
	tcond.append('((type & {}))'.format(tbit('kEJ1')))
	tcond.append('((type & {}))'.format(tbit('kEG1')))
	tcond.append('((type & {}) && (type & {}))'.format(tbit('kEJ1'), tbit('kEG1')))
	tcond.append('((type & {}))'.format(tbit('kDJ1')))
	tcond.append('((type & {}))'.format(tbit('kDG1')))
	tcond.append('((type & {}) && (type & {}))'.format(tbit('kDJ1'), tbit('kDG1')))
	tcond.append('((type & {}))'.format(tbit('kCINT7')))
	tcond.append('((type & {}))'.format(tbit('kCINT7')))

	hname = [
		'kCINT7',
		'kEJ1',
		'kEG1',
		'kEJ1kEG1',
		'kDJ1',
		'kDG1',
		'kDJ1kDG1'
	]

	htitle = [
		'kCINT7',
		'kEJ1',
		'kEG1',
		'kEJ1 && kEG1',
		'kDJ1',
		'kDG1',
		'kDJ1 && kDG1'
	]

	hl = dlist.dlist('t_share')

	nevents = []
	for i, tc in enumerate(tcond):
		n = get_n_events(dname, tc)
		nevents.append(n)
		h = ROOT.TH1I(hname[i], hname[i], len(tcond), 0, len(tcond) + 1)
		h.SetBinContent(i+1, n)
		hl.add(h, htitle[i], 'hist')

	for i, tc in enumerate(tcond):
		print tc, nevents[i]

	for i in [0+1, 1+1, 3+1, 4+1]:
		h = hl.l[i].obj
		if i < 2+1:
			isum = 2+1
		else:
			isum = 5+1
		share = nevents[isum] / nevents[i]
		shareMB = nevents[i] / nevents[0]
		newTitle = '{} [AND is {:.1f}%] [frac of MB {:3.1g}%]'.format(h.GetTitle(), share * 100., shareMB * 100.)
		h.SetTitle(newTitle)

	hl.make_canvas()
	hl.draw(logy=True)
	hl.self_legend(miny=1e3, maxy=5e6)
	ROOT.gPad.SetLogy()
	hl.write_to_file(name_mod='modn:')
	hl.pdf()
	tu.gList.append(hl)

if __name__ == '__main__':
	tu.setup_basic_root()
	envdir = os.getenv('RUN2AESDDIR')
	libs = ['libEMCALTriggerFast', 'libRAnalyzeESD']
	for l in libs:
		lib = os.path.join(envdir, 'lib', l)
		ROOT.gSystem.Load(lib)
	dname = ut.get_arg_with('--in')
	if dname==None:
		dname = './output000245146'

	if '--make' in sys.argv:
		main(dname)

	print AND_trig_condition('kCINT7', 'kEG1', 'kEJ1')

	if not ut.is_arg_set('-b'):
		IPython.embed()	


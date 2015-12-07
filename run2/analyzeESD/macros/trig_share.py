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
	tcond.append(AND_trig_condition('kCINT7'))
	tcond.append(AND_trig_condition('kEJ1'))
	tcond.append(AND_trig_condition('kEG1'))
	tcond.append(AND_trig_condition('kEJ1', 'kEG1'))
	tcond.append(AND_trig_condition('kDJ1'))
	tcond.append(AND_trig_condition('kDG1'))
	tcond.append(AND_trig_condition('kDJ1', 'kDG1'))
	#tcond.append(AND_trig_condition('kCINT7', 'kDJ1', 'kDG1'))
	#tcond.append(AND_trig_condition('kCINT7', 'kDJ1', 'kDG1'))

	hname = [
		'kCINT7',
		'kEJ1',
		'kEG1',
		'kEJ1kEG1',
		'kDJ1',
		'kDG1',
		'kDJ1kDG1',
		'kCINT7kDJ1kDG1',
		'kCINT7kDJ1kDG1'
	]

	htitle = [
		'kCINT7',
		'kEJ1',
		'kEG1',
		'kEJ1 && kEG1',
		'kDJ1',
		'kDG1',
		'kDJ1 && kDG1',
		'kCINT7 && kDJ1 && kDG1',
		'kCINT7 && kDJ1 && kDG1'
	]

	hl = dlist.dlist('t_share')

	hlcent = dlist.dlist('t_share_cent')

	cent = []
	for i in range(0, 11):
		cent.append([i*10, (i+1)*10])

	nMB = 0.0
	nevents = []
	for i, tc in enumerate(tcond):
		n = get_n_events(dname, tc)
		nevents.append(n)
		h = ROOT.TH1F(hname[i], hname[i], len(tcond), 0 - 0.5, len(tcond) - 0.5)
		if i == 0:
			nMB = n * 1.
		h.SetBinContent(i+1, n / nMB)
		hl.add(h, '[{}] {}'.format(i, htitle[i]), '+f1001 +a75 +l1 hist')

		hn  = hname[i] + '_cent'
		h  = ROOT.TH1F(hn, hn, 11, 0, 110)
		for ic, c in enumerate(cent):
			tcc = tc + ' && (trig.cent >= {} && trig.cent < {})'.format(c[0],c[1])
			n   = get_n_events(dname, tcc)
			h.SetBinContent(ic+1, n / nMB)
		hlcent.add(h, htitle[i], 'hist')

	hlcent.reset_axis_titles('centrality V0M %', 'ratio to N of kCINT7 triggers')

	hlcent.make_canvas()
	hlcent.draw(logy=True)
	hlcent.self_legend()
	hlcent.update()
	hlcent.write_to_file(name_mod='modn:')
	hlcent.pdf()
	tu.gList.append(hlcent)

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
		newTitle = '{} [AND is {:.1f}%] [ratio to MB {:3.1g}%]'.format(h.GetTitle(), share * 100., shareMB * 100.)
		h.SetTitle(newTitle)

	hl.make_canvas()
	hl.reset_axis_titles('trigger number', 'normalized to kCINT7 N={:.3g}'.format(nevents[0]))
	#hl.draw(logy=True, miny=1e3, maxy=5e6)
	hl.draw(logy=True, miny=5e-4, maxy=2)
	hl.self_legend(1, '', 0.38,0.6,0.8,0.87)
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hl.update()
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

	if not ut.is_arg_set('-b'):
		IPython.embed()	


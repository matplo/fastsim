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
import tutils as tu
import hnutil
import draw_ntuple
import draw_utils as du

from trigutils import *

class GetHL(object):
	def __init__(self):
		self.reset()

	def reset(self):
		self.bwidth   = 5
		self.xlow     = 0
		self.xhigh    = 200
		self.nev      = -1
		
		self.ntname   = 't'
		self.var      = ''
		self.cuts     = ''
		self.refcuts  = ''
		
		self.ybwidth  = 2.
		self.ylow     = 0.
		self.yhigh    = 100.
		
		self.title    = 'h'
		self.modname  = ''
		self.fpatt    = 'tree-*.root'
		self.outfname = 'hl_out.root'
		self.name_mod = 'modn:'
		self.data_dir = './'
		
		self.thr      = 10
		self.R        = 0.4
		
		self.cuts     = '(abs({bname}.Eta()) < 0.9 - {radius}) * (xsec)	'
		self.refcuts  = '(abs({bname}.Eta()) < 0.9 - {radius})			'

	def reset_jet_cuts(self, bname, radius = None):
		r = 0.4
		if radius == None:
			if 'r' in bname:
				r = 0.2
		else:
			r = radius
		self.cuts     = '(abs({bname}.Eta()) < (0.9 - {radius})) * (xsec)'.format(bname=bname, radius=r)
		self.refcuts  = '(abs({bname}.Eta()) < (0.9 - {radius}))'.format(bname=bname, radius=r)

	def make_hl_1d(self, outfname = None):
		print '[i] drawing dir:		', 	self.data_dir
		print '    var:				', 	self.var
		print '    cuts:			',	self.cuts
		print '    refcuts:			',	self.refcuts

		tu.getTempCanvas().cd()
		hl = draw_ntuple.h1d_from_ntuple_dir_filter(cdir = self.data_dir, ntname = self.ntname, 
													title = '{}-{}-{}-{}'.format(self.data_dir, self.ntname, self.var, self.cuts),
													var = self.var, cuts = self.cuts, 
													bwidth = self.bwidth, xlow = self.xlow, xhigh = self.xhigh, 
													refcuts = self.refcuts, 
													nev=self.nev, thr=self.thr, fpatt=self.fpatt)
		hl.make_canvas()
		hl.draw(logy=True)
		hl.self_legend()

		if '--write' in sys.argv:
			if outfname != None:
				hl.write_to_file(outfname, name_mod='modn:')
			else:
				outfname = tu.make_unique_name('jetpt', bname, cuts)
				hl.write_to_file(fname=outfname, name_mod='modn:')

		tu.gList.append(hl)

		return hl

	def make_hl_2d(self, outfname = None, refcuts = False):
		print self.var, self.cuts, self.bwidth, self.xlow, self.xhigh, self.ybwidth, self.ylow, self.yhigh
		tu.getTempCanvas().cd()
		hl = draw_ntuple.h2d_from_ntuple_dir(self.data_dir, self.ntname, 
												self.var, self.cuts, 
												self.bwidth, self.xlow, self.xhigh, self.ybwidth, self.ylow, self.yhigh, 
												self.title, self.modname, self.nev, self.fpatt)
		hlref = draw_ntuple.h2d_from_ntuple_dir(self.data_dir, self.ntname, 
													self.var, self.refcuts, 
													self.bwidth, self.xlow, self.xhigh, self.ybwidth, self.ylow, self.yhigh, 
													self.title, self.modname, self.nev, self.fpatt)
		dlist.filter_single_entries(hl, hlref, self.thr)
		hs = hl.sum()
		hs.obj.Draw("colz")
		tu.gList.append(hs)

		hl.add(hs, 'sum', 'hist', prep=True)

		if '--write' in sys.argv:
			if outfname != None:
				hl.write_to_file(outfname, name_mod='modn:')
			else:
				outfname = tu.make_unique_name('jetpt2D', bname, cuts)
				hl.write_to_file(fname=outfname, name_mod='modn:')

		tu.gList.append(hl)

		return hl

def fname_to_title(fname):
	repc = [['_', ' ',],
			['.root', ''],
			['./', ''],
			['/', ' ']]
	retval = fname
	for r in repc:
		retval = retval.replace(r[0], r[1])
	return retval

def draw_pt(nev):
	files = ['jetpt_0.4.root',
			 'jetpt_EMCal_0.4.root',
			 #'jetpt_DCal_0.4.root',
			 'jetpt_0.2.root',
			 'jetpt_EMCal_0.2.root',
			 'jetpt_DCal_0.2.root']

	hl = dlist.ListStorage('draw_jetpt')
	for f in files:
		#hl.add_from_file('pt', 'o_0', f, fname_to_title(f).replace('jetpt', 'jet p_{T}'), 'hist +f1001 +a20')
		hl.add_from_file('pt', 'o_0', f, fname_to_title(f).replace('jetpt', 'jet p_{T}'), 'hist')

	hl.get('pt').scale(1./nev)
	hl.get('pt').reset_axis_titles('jet p_{T}', 'xsection (mb)')
	hl.draw_all(orient=1, logy=True)

	tu.gList.append(hl)

def draw_fidu():
	feta = ['jeteta_0.2.root',
			'jeteta_0.4.root',
			'jeteta_EMCal_0.2.root',
			'jeteta_EMCal_0.4.root',
			'jeteta_DCal_0.2.root',
			'jeteta_DCal_0.4.root']
	fphi = ['jetphi_0.2.root',
			'jetphi_0.4.root',
			'jetphi_EMCal_0.2.root',
			'jetphi_EMCal_0.4.root',
			'jetphi_DCal_0.2.root',
			'jetphi_DCal_0.4.root']

	hl = dlist.ListStorage('draw_acceptance')
	for f in feta:
		hl.add_from_file('#eta', 'o_0', f, fname_to_title(f).replace('jeteta', '#eta'), 'hist +f1001 +a20')
	for f in fphi:
		hl.add_from_file('#varphi', 'o_0', f, fname_to_title(f).replace('jetphi', '#varphi'), 'hist +f1001 +a20')

	hl.get('#eta').reset_axis_titles('jet #eta', 'counts x xsection (arb. units)')
	hl.get('#varphi').reset_axis_titles('jet #varphi', 'counts x xsection (arb. units)')

	hl.get('#eta').zoom_axis(0, -1, 1)
	hl.get('#varphi').zoom_axis(0, -2, 3.2)
	#for l in hl.lists:
	#	l.normalize_self(scale_by_binwidth=False)

	hl.draw_all(orient=1)

	tu.gList.append(hl)


def draw_tcut():
	hname = 'o_16'

	pTmin = 0
	pTmax = 20
	step  = 4

	files = [ 	'eje_j.root',
				#'eje_j_lead.root',
				'eje_jE.root',
				#'eje_jE_lead.root',
				'dje_jDr.root',
				#'dje_jDr_lead.root' 
				]

	for fname in files:
		pTs = []
		htitle = fname
		#hl = dlist.get_projectionsX(hname, fname, htitle, pTmin, pTmax, step, 'P L HIST', pTs)
		hl = dlist.get_projections_axis_lowcut(hname, fname, htitle, pTmin, pTmax, step, opt='p', axis = 0, pTs=pTs)
		hl.make_canvas()
		hl.draw(logy=True)
		hl.self_legend()
		ROOT.gPad.SetLogy()
		hl.update()
		tu.gList.append(hl)

		hlr = hl.ratio_to(0, 'p l')
		hlr.make_canvas()
		hlr.draw(miny=0, maxy=2)
		hlr.self_legend()
		hlr.update()
		tu.gList.append(hlr)

if __name__=="__main__":
	tu.setup_basic_root()

	data_dir = '/Volumes/one/data/run2/trigger/2016-02-08/hardQCD/vacf/'
	if ut.get_arg_with('--dir') != None:
		data_dir = ut.get_arg_with('--dir')

	nev = 1000
	if '--jetpt' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = nev

		hl.var  = 'j.Pt()'
		hl.reset_jet_cuts(bname='j', radius=0.4)
		hl.make_hl_1d(outfname = 'jetpt_0.4.root')

		hl.var  = 'jE.Pt()'
		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.make_hl_1d(outfname = 'jetpt_EMCal_0.4.root')

		hl.var  = 'jr.Pt()'
		hl.reset_jet_cuts(bname='jr', radius=0.2)
		hl.make_hl_1d(outfname = 'jetpt_0.2.root')

		hl.var  = 'jEr.Pt()'
		hl.reset_jet_cuts(bname='jEr', radius=0.2)
		hl.make_hl_1d(outfname = 'jetpt_EMCal_0.2.root')

		hl.var  = 'jDr.Pt()'
		hl.reset_jet_cuts(bname='jDr', radius=0.2)
		hl.make_hl_1d(outfname = 'jetpt_DCal_0.2.root')

	if '--drawpt' in sys.argv:
		draw_pt(nev)

	if '--tcut' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = 100
		#hl.var      = 'tgEJE.fE:j.Pt()' # for whatever reason this doesn't work
		hl.reset_jet_cuts(bname='j', radius=0.4)

		hl.var      = 'tg.maxEJE.fE:j.Pt()'
		hl.make_hl_2d('eje_j.root')		
		#hl.var      = 'tg.maxEJE.fE:j.Pt()[0]'
		#hl.make_hl_2d('eje_j_lead.root')

		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.var      = 'tg.maxEJE.fE:jE.Pt()'
		hl.make_hl_2d('eje_jE.root')
		#hl.var      = 'tg.maxEJE.fE:jE.Pt()[0]'
		#hl.make_hl_2d('eje_jE_lead.root')

		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.var      = 'tg.maxEJE8x8.fE:jE.Pt()'
		hl.make_hl_2d('eje_jE.root')

		hl.reset_jet_cuts(bname='jDr', radius=0.2)
		hl.var      = 'tg.maxDJE8x8.fE:jDr.Pt()'
		hl.make_hl_2d('dje_jDr.root')
		#hl.var      = 'tg.maxDJE8x8.fE:jDr.Pt()[0]'
		#hl.make_hl_2d('dje_jDr_lead.root')

	if '--drawtcut' in sys.argv:
		draw_tcut()

	if '--jetfidu' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = 1000
		hl.xhigh    =  4
		hl.xlow     = -4
		hl.bwidth   = 0.1

		hl.reset_jet_cuts(bname='j', radius=0.4)
		hl.var = 'j.Phi()'
		hl.make_hl_1d(outfname = 'jetphi_0.4.root')

		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.var = 'jE.Phi()'
		hl.make_hl_1d(outfname = 'jetphi_EMCal_0.4.root')

		hl.reset_jet_cuts(bname='jD', radius=0.4)
		hl.var = 'jD.Phi()'
		hl.make_hl_1d(outfname = 'jetphi_DCal_0.4.root')

		hl.reset_jet_cuts(bname='j', radius=0.4)
		hl.var = 'j.Eta()'
		hl.make_hl_1d(outfname = 'jeteta_0.4.root')

		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.var = 'jE.Eta()'
		hl.make_hl_1d(outfname = 'jeteta_EMCal_0.4.root')

		hl.reset_jet_cuts(bname='jD', radius=0.4)
		hl.var = 'jD.Eta()'
		hl.make_hl_1d(outfname = 'jeteta_DCal_0.4.root')

		# R=0.2

		hl.reset_jet_cuts(bname='j', radius=0.2)
		hl.var = 'j.Phi()'
		hl.make_hl_1d(outfname = 'jetphi_0.2.root')

		hl.reset_jet_cuts(bname='jE', radius=0.2)
		hl.var = 'jE.Phi()'
		hl.make_hl_1d(outfname = 'jetphi_EMCal_0.2.root')

		hl.reset_jet_cuts(bname='jD', radius=0.2)
		hl.var = 'jD.Phi()'
		hl.make_hl_1d(outfname = 'jetphi_DCal_0.2.root')

		hl.reset_jet_cuts(bname='j', radius=0.2)
		hl.var = 'j.Eta()'
		hl.make_hl_1d(outfname = 'jeteta_0.2.root')

		hl.reset_jet_cuts(bname='jE', radius=0.2)
		hl.var = 'jE.Eta()'
		hl.make_hl_1d(outfname = 'jeteta_EMCal_0.2.root')

		hl.reset_jet_cuts(bname='jD', radius=0.2)
		hl.var = 'jD.Eta()'
		hl.make_hl_1d(outfname = 'jeteta_DCal_0.2.root')

	if '--drawfidu' in sys.argv:
		draw_fidu()

	if not ut.is_arg_set('-b'):
		IPython.embed()


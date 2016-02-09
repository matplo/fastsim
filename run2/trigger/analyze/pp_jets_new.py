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
		
		self.cuts     = '(abs({bname}.Eta()) < 0.9 - {radius}) * (hd.xsec)	'
		self.refcuts  = '(abs({bname}.Eta()) < 0.9 - {radius})			'

	def reset_jet_cuts(self, bname, radius = None):
		r = 0.4
		if radius == None:
			if 'r' in bname:
				r = 0.2
		else:
			r = radius
		self.cuts     = '(abs({bname}.Eta()) < (0.9 - {radius})) * (hd.xsec)'.format(bname=bname, radius=r)
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

		dlist.filter_single_entries_2d(hl, hlref, self.thr)

		hs = hl.sum()
		hs.obj.Draw("colz")
		tu.gList.append(hs)
		hl.add(hs, 'sum', 'hist', prep=True)

		hsref = hlref.sum()
		hs.obj.Draw("colz")
		tu.gList.append(hsref)
		hlref.add(hsref, 'sum', 'hist', prep=True)

		if '--write' in sys.argv:
			if outfname != None:
				hl.write_to_file(outfname, name_mod='modn:')
				hlref.write_to_file(outfname.replace('.root', '_ref.root'), name_mod='modn:')
			else:
				outfname = tu.make_unique_name('jetpt2D', bname, cuts)
				hl.write_to_file(fname=outfname+'.root', name_mod='modn:')
				hl.write_to_file(fname=outfname+'_ref.root', name_mod='modn:')

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

def draw_pt(nev=-1):
	files = [#'jetpt_0.4.root',
			 'jetpt_EMCal_0.4.root',
			 #'jetpt_DCal_0.4.root',
			 #'jetpt_0.2.root',
			 'jetpt_EMCal_0.2.root',
			 'jetpt_DCal_0.2.root']

	subdir = './'
	subdir = './jetpt'

	hl = dlist.ListStorage('draw_jetpt')
	for f in files:
		#hl.add_from_file('pt', 'o_0', f, fname_to_title(f).replace('jetpt', 'jet p_{T}'), 'hist +f1001 +a20')
		fn = os.path.join(subdir, f)
		print fn
		hl.add_from_file('pt', 'o_0', fn, fname_to_title(f).replace('jetpt', ''), 'p')

	if nev < 0:
		nev = 10000.
	topb = 1.e9
	#dphiscaleup=1./((ROOT.TMath.DegToRad() * 110. - 0.4 - 0.4)/(ROOT.TMath.Pi()*2.))
	#hl.get('pt').scale(1./nev * topb / 0.6 / 10. * dphiscaleup) # deta is (0.7-0.4) x 2
	#hl.get('pt').reset_axis_titles('jet p_{T}', 'd#sigma/dp_{T}/d#eta (pb)')

	hl.get('pt').scale(1./nev * topb)
	hl.get('pt').reset_axis_titles('jet p_{T}', '#sigma (pb)')

	hl.draw_all(orient=0, logy=True, legtitle='anti-k_{T}; pp@13TeV')
	hl.zoom_axis(0, 0, 200)
	hl.set_grid_x()
	hl.set_grid_y()
	hl.resize_window(800,800)
	tu.gList.append(hl)
	hl.pdf()
	hl.png()

def draw_pt_bias(nev, files = None, title = ''):

	if files == None:
		files = [ 'jetpt_EMCal_0.4_0.root', 'jetpt_EMCal_0.4_5.root', 'jetpt_EMCal_0.4_10.root', 'jetpt_EMCal_0.4_15.root', 'jetpt_EMCal_0.4_20.root', 'jetpt_EMCal_0.4_25.root', 'jetpt_EMCal_0.4_30.root' ]
	titles = [ 'minbias', '5 GeV', '10 GeV', '15 GeV', '20 GeV', '25 GeV', '30 GeV' ]

	subdir = './'
	subdir = './jetpt'

	hl = dlist.ListStorage('trigger bias {}'.format(title))
	for i,f in enumerate(files):
		fn = os.path.join(subdir, f)
		print fn
		hl.add_from_file('pt', 'o_0', fn, titles[i], 'hist')

	lnev = -1
	if nev == -1:
		lnev = 10000

	for lx in hl.lists:
		print lx.name
		lx.scale(1./lnev)
		lx.reset_axis_titles('jet p_{T}', 'xsection (mb)')

	hlb = dlist.ListStorage('draw_pt_bias_b {}'.format(title))
	for lx in hl.lists:
		print lx.name
		hlbias = lx.ratio_to(0, 'l')
		hlbias.title = title
		hlbias.reset_axis_titles('p_{T}', 'ratio')
		hlb.append(hlbias)

		#hlbias = hl.get('pt').ratio_to(0, 'l')
		#hlbias.make_canvas()
		#hlbias.draw(miny=0, maxy=2)
		#hlbias.self_legend()
		#hl.append(hlbias)
		#tu.gList.append(hlbias)

	hl.draw_all(orient=0, logy=True)
	tu.gList.append(hl)

	hlb.draw_all(orient=0, logy=False, maxy=1.6)
	tu.gList.append(hlb)

	hlb.pdf()
	hlb.png()


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

	subdir = './'
	subdir = './phieta'

	hl = dlist.ListStorage('draw_acceptance')
	for f in feta:
		fn = os.path.join(subdir, f)
		hl.add_from_file('#eta', 'o_0', fn, fname_to_title(f).replace('jeteta', '#eta'), 'hist +f1001 +a20')
	for f in fphi:
		fn = os.path.join(subdir, f)
		hl.add_from_file('#varphi', 'o_0', fn, fname_to_title(f).replace('jetphi', '#varphi'), 'hist +f1001 +a20')

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
	pTmax = 30
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

def draw_trejections():
	hname = 'o_0'
	files = ['tEJE.root',
			'tEJE8x8.root',
			'tEJEmax.root',
			'tEJEmax8x8.root',
			'tDJEmax8x8.root']

	subdir = './'
	subdir = './trej'

	hl = dlist.ListStorage('trejections')
	for f in files:
		fn = os.path.join(subdir, f)
		lname = fn.replace('.root', '')
		hl.add_from_file('tspectra', hname, fn, lname, 'l')
	hl.get('tspectra').scale(1./10000.)

	hl.append(dlist.fractional_yats(hl.get('tspectra')))
	hl.zoom_axis(0, 0, 30)
	hl.draw_all(logy=True, miny=1e-6)
	hl.set_grid_x()	
	hl.set_grid_y()
	tu.gList.append(hl)
	hl.pdf()
	hl.png()
	
if __name__=="__main__":
	tu.setup_basic_root()

	data_dir = '/Volumes/one/data/run2/trigger/2016-02-08/hardQCD/vacf/'
	if ut.get_arg_with('--dir') != None:
		data_dir = ut.get_arg_with('--dir')

	nev = -1
	if ut.is_arg_set('--nev'):
		nev = int(ut.get_arg_with('--nev'))
	print '[i] nev setup:',nev

	if '--jetpt' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = nev
		hl.bwidth   = 10. # 20 GeV bins

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

		for th in [0, 5, 10, 15, 20, 25, 30]:
			hl.bwidth   = 5. # 20 GeV bins
			hl.var = 'jE.Pt()'
			bname  = 'jE'
			r      = 0.4
			hl.cuts     = '(abs({bname}.Eta()) < (0.9 - {radius})) && (tg.maxjECAL > {th}) * (hd.xsec)'.format(bname=bname, radius=r, th=th)
			hl.refcuts  = '(abs({bname}.Eta()) < (0.9 - {radius})) && (tg.maxjECAL > {th})'.format(bname=bname, radius=r, th=th)
			hl.make_hl_1d(outfname = 'jetpt_EMCal_0.4_{th}.root'.format(th=th))

			hl.var = 'jE.Pt()'
			bname  = 'jE'
			r      = 0.4
			hl.cuts     = '(abs({bname}.Eta()) < (0.9 - {radius})) && (tg.maxjECAL8x8 > {th}) * (hd.xsec)'.format(bname=bname, radius=r, th=th)
			hl.refcuts  = '(abs({bname}.Eta()) < (0.9 - {radius})) && (tg.maxjECAL8x8 > {th})'.format(bname=bname, radius=r, th=th)
			hl.make_hl_1d(outfname = 'jetpt_EMCal_0.4_{th}_8x8.root'.format(th=th))

			hl.var = 'jEr.Pt()'
			bname  = 'jEr'
			r      = 0.2
			hl.cuts     = '(abs({bname}.Eta()) < (0.9 - {radius})) && (tg.maxjDCAL8x8 > {th}) * (hd.xsec)'.format(bname=bname, radius=r, th=th)
			hl.refcuts  = '(abs({bname}.Eta()) < (0.9 - {radius})) && (tg.maxjDCAL8x8 > {th})'.format(bname=bname, radius=r, th=th)
			hl.make_hl_1d(outfname = 'jetpt_DCal_0.2_{th}_8x8.root'.format(th=th))

	if '--drawpt' in sys.argv:
		draw_pt(nev)

	if '--drawbias' in sys.argv:
		files = [ 'jetpt_EMCal_0.4_0.root', 'jetpt_EMCal_0.4_5.root', 'jetpt_EMCal_0.4_10.root', 'jetpt_EMCal_0.4_15.root', 'jetpt_EMCal_0.4_20.root', 'jetpt_EMCal_0.4_25.root', 'jetpt_EMCal_0.4_30.root' ]
		draw_pt_bias(nev, files, 'EMC R=0.4 [16x16]')

		files = [ 'jetpt_EMCal_0.4_0_8x8.root', 'jetpt_EMCal_0.4_5_8x8.root', 'jetpt_EMCal_0.4_10_8x8.root', 'jetpt_EMCal_0.4_15_8x8.root', 'jetpt_EMCal_0.4_20_8x8.root', 'jetpt_EMCal_0.4_25_8x8.root', 'jetpt_EMCal_0.4_30_8x8.root' ]
		draw_pt_bias(nev, files, 'EMC R=0.4 [8x8]')

		files = [ 'jetpt_DCal_0.2_0_8x8.root', 'jetpt_DCal_0.2_5_8x8.root', 'jetpt_DCal_0.2_10_8x8.root', 'jetpt_DCal_0.2_15_8x8.root', 'jetpt_DCal_0.2_20_8x8.root', 'jetpt_DCal_0.2_25_8x8.root', 'jetpt_DCal_0.2_30_8x8.root' ]
		draw_pt_bias(nev, files, 'DMC R=0.2 [8x8]')

	if '--tspectrum' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = nev
		hl.bwidth   = 2. # 2 GeV bins

		hl.reset_jet_cuts(bname='j', radius=0.4)
		hl.cuts    = '(1)*(hd.xsec)'
		hl.refcuts = '(1)'

		hl.var  = 'tgEJE.fE'
		hl.make_hl_1d(outfname = 'tEJE.root')
		hl.var  = 'tgEJE8x8.fE'
		hl.make_hl_1d(outfname = 'tEJE8x8.root')

		hl.var  = 'tg.maxjECAL'
		hl.make_hl_1d(outfname = 'tEJEmax.root')
		hl.var  = 'tg.maxjECAL8x8'
		hl.make_hl_1d(outfname = 'tEJEmax8x8.root')

		hl.var  = 'tg.maxjDCAL8x8'
		hl.make_hl_1d(outfname = 'tDJEmax8x8.root')

	if '--drawrej' in sys.argv:
		draw_trejections()

	if '--tcut' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = nev
		hl.bwidth   = 5. # 4 GeV bins
		hl.thr      = 10
		#hl.var      = 'tgEJE.fE:j.Pt()' # for whatever reason this doesn't work
		hl.reset_jet_cuts(bname='j', radius=0.4)

		hl.var      = 'tg.maxjECAL:j.Pt()'
		hl.make_hl_2d('eje_j.root')		
		#hl.var      = 'tg.maxjECAL:j.Pt()[0]'
		#hl.make_hl_2d('eje_j_lead.root')

		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.var      = 'tg.maxjECAL:jE.Pt()'
		hl.make_hl_2d('eje_jE.root')
		#hl.var      = 'tg.maxjECAL:jE.Pt()[0]'
		#hl.make_hl_2d('eje_jE_lead.root')

		hl.reset_jet_cuts(bname='jE', radius=0.4)
		hl.var      = 'tg.maxjECAL8x8:jE.Pt()'
		hl.make_hl_2d('eje_jE.root')

		hl.reset_jet_cuts(bname='jDr', radius=0.2)
		hl.var      = 'tg.maxjDCAL8x8:jDr.Pt()'
		hl.make_hl_2d('dje_jDr.root')
		#hl.var      = 'tg.maxjDCAL8x8:jDr.Pt()[0]'
		#hl.make_hl_2d('dje_jDr_lead.root')

	if '--drawtcut' in sys.argv:
		draw_tcut()

	if '--jetfidu' in sys.argv:
		hl          = GetHL()
		hl.data_dir = data_dir
		hl.nev      = nev
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


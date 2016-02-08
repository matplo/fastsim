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
		self.bwidth   = 10
		self.xlow     = 0
		self.xhigh    = 200
		self.nev      = -1
		
		self.ntname   = 't'
		self.var      = ''
		self.cuts     = ''
		
		self.ybwidth  = 1
		self.ylow     = 0
		self.yhigh    = 200
		
		self.title    = 'h'
		self.modname  = ''
		self.fpatt    = '*.root'
		
		self.outfname = 'hl_out.root'
		self.name_mod = 'modn:'

	def get_hl(self, data_dir, ntname, var, cuts, refcuts):
		print '[i] drawing dir:', data_dir
		print '    var:',var
		print '    cuts:',cuts

		tu.getTempCanvas().cd()
		hl = draw_ntuple.h1d_from_ntuple_dir_filter(cdir = data_dir, ntname = ntname, 
													title = '{}-{}-{}-{}'.format(data_dir, ntname, var, cuts),
													var = var, cuts = cuts, 
													bwidth = self.bwidth, xlow = self.xlow, xhigh = self.xhigh, 
													refcuts = refcuts, 
													nev=self.nev, thr=10, fpatt='tree-*.root')
		return hl

	def make_jet(self, data_dir, R=0.4, usrcuts=None, outfname = None, func='Pt()'):
		ntname = 't'
		bname = 'j'

		if R == 0.2:
			bname = 'jr'

		var = '{}.{}'.format(bname, func)

		if usrcuts == None:
			usrcuts = 'abs({}.Eta()) < (0.9 - {})'.format(bname, R)
		else:
			usrcuts = usrcuts.format(bname=bname)  

		cuts = '({})*(hd.xsec)'.format(usrcuts)
		refcuts = '{}'.format(usrcuts)

		hl = self.get_hl(data_dir, ntname, var, cuts, refcuts)

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

	def make_jet_tcut(self, data_dir):
		hl = draw_ntuple.h2d_from_ntuple_dir(data_dir, self.ntname, 
											self.var, self.cuts, 
											self.bwidth, self.xlow, self.xhigh, self.ybwidth, self.ylow, self.yhigh, 
											self.title, self.modname, self.nev, self.fpatt)
		if '--write' in sys.argv:
			outfname = tu.make_unique_name(self.outfname)
			hl.write_to_file(outfname, name_mod=self.name_mod)

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
	feta = ['jeteta_EMCal.root',
			'jeteta_EMCal_0.2.root',
			'jeteta_EMCal_0.4.root',
			'jeteta_DCal.root',
			'jeteta_DCal_0.2.root',
			'jeteta_DCal_0.4.root']
	fphi = ['jetphi_EMCal.root',
			'jetphi_EMCal_0.2.root',
			'jetphi_EMCal_0.4.root',
			'jetphi_DCal.root',
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

if __name__=="__main__":
	tu.setup_basic_root()

	data_dir = '/Volumes/one/data/run2/trigger/2016-02-08/hardQCD/vacf/'
	if ut.get_arg_with('--dir') != None:
		data_dir = ut.get_arg_with('--dir')

	nev = 1000
	if '--jetpt' in sys.argv:
		hl = GetHL()
		hl.nev    = nev
		hl.make_jet(data_dir, R=0.4, outfname = 'jetpt_0.4.root')
		hl.make_jet(data_dir, R=0.2, outfname = 'jetpt_0.2.root')

		usrcuts_list = [['{}'.format(emcal_eta_phi_cut(R=0.4)), 'jetpt_EMCal.root']]
		for c in usrcuts_list:
			hl.make_jet(data_dir, R=0.4, usrcuts=c[0], outfname=c[1].replace('.root', '_0.4.root'))

		usrcuts_list = [['{}'.format(emcal_eta_phi_cut(R=0.2)), 'jetpt_EMCal.root'],
						['{}'.format(dcal_eta_phi_cut(R=0.2)), 'jetpt_DCal.root'] ]
		for c in usrcuts_list:
			hl.make_jet(data_dir, R=0.2, usrcuts=c[0], outfname=c[1].replace('.root', '_0.2.root'))

	if '--drawpt' in sys.argv:
		draw_pt(nev)

	if '--tcut' in sys.argv:
		hl = GetHL()
		hl.nev    = nev
		hl.var = 'tgEJE.fE:j.Pt()'
		hl.cuts = emcal_eta_phi_cut(R=0.4)

		hl.make_jet_tcut(data_dir)

	if '--jetfidu' in sys.argv:
		hl = GetHL()
		hl.nev    = 10000
		hl.xhigh  =  4
		hl.xlow   = -4
		hl.bwidth = 0.1
		#debug phi and eta cuts
		usrcuts_list = [[emcal_eta_phi_cut(R=0.4), 'jetpt_EMCal.root'],
						[dcal_eta_phi_cut(R=0.4), 'jetpt_DCal.root'] ]
		for c in usrcuts_list:
			hl.make_jet(data_dir, R=0.4, usrcuts=c[0], outfname=c[1].replace('.root', '_0.4.root').replace('jetpt','jeteta'), func='Eta()')
			hl.make_jet(data_dir, R=0.4, usrcuts=c[0], outfname=c[1].replace('.root', '_0.4.root').replace('jetpt','jetphi'), func='Phi()')

		usrcuts_list = [[emcal_eta_phi_cut(R=0.2), 'jetpt_EMCal.root'],
						[dcal_eta_phi_cut(R=0.2), 'jetpt_DCal.root'] ]
		for c in usrcuts_list:
			hl.make_jet(data_dir, R=0.2, usrcuts=c[0], outfname=c[1].replace('.root', '_0.2.root').replace('jetpt','jeteta'), func='Eta()')
			hl.make_jet(data_dir, R=0.2, usrcuts=c[0], outfname=c[1].replace('.root', '_0.2.root').replace('jetpt','jetphi'), func='Phi()')

		usrcuts_list = [[emcal_eta_phi_cut(R=0.0), 'jetpt_EMCal.root'],
						[dcal_eta_phi_cut(R=0.0), 'jetpt_DCal.root'] ]
		for c in usrcuts_list:
			hl.make_jet(data_dir, R=0.4, usrcuts=c[0], outfname=c[1].replace('.root', '.root').replace('jetpt','jeteta'), func='Eta()')
			hl.make_jet(data_dir, R=0.4, usrcuts=c[0], outfname=c[1].replace('.root', '.root').replace('jetpt','jetphi'), func='Phi()')

	if '--drawfidu' in sys.argv:
		draw_fidu()

	if not ut.is_arg_set('-b'):
		IPython.embed()


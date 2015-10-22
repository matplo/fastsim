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

def EMCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 110. / 360. * math.pi * 2.

	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)

	return retval

def DCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 80. / 360. * math.pi * 2. #not 70 deg?

	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)

	return retval

class NTFiles(object):
	def __init__(self):
		self.basedir=self._guess_dir()
		self.files= [
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-0_default_emctrig_out_femc_1.0.root',
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-200_default_emctrig_out_femc_1.0.root',
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-500_default_emctrig_out_femc_1.0.root',
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-800_default_emctrig_out_femc_1.0.root',	
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-1200_default_emctrig_out_femc_1.0.root',
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-2000_default_emctrig_out_femc_1.0.root',
			'_data1_run2_trigger_2015-10-20_hardQCD_mult-4000_default_emctrig_out_femc_1.0.root',	
		]

	def _guess_dir(self):
		sdirs = [ 
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-20',
			'/Volumes/MP/data/run2/trigger/2015-10-20'
			]
		for s in sdirs:
			if os.path.isdir(s):
				print '[i] NTFiles: basedir guessed:',s
				return s
		print >> std.err, '[w] NTFiles: basedir not guessed. set :basedir manually. using os.getcwd()'
		return os.getcwd()

	def nfiles(self):
		return len(self.files)

	def get_file(self, im = 0, femc=1.0, photons=False):
		retval = self.files[im]
		if femc < 1.0:
			retval = retval.replace("femc_1.0", "femc_{}".format(femc))
		if photons == True:
			retval = retval.replace("_hardQCD_", "_photons_")
		return os.path.join(self.basedir, retval)

	def get_files(self, femc=1.0, photons=False):
		retval = []
		for i in range(self.nfiles()):
			retval.append(self.get_file(i, femc, photons))
		return retval

	def get_mult_from_fname(self, im=0):
		fn = self.files[im]
		return float(fn.split('_mult-')[1].split('_default')[0])


#def get_pT(photons=False, femc=0.1, var='pT'):
def get_pT(photons=False, femc=0.1, var='pT'):
	ntfs  = NTFiles()
	nfile = 4 #0
	fname = ntfs.get_file(nfile, femc, photons)

	ntuples = ['jets_hard_EMC', 'jets_hard_EMCc', 'jets_hard_DMCc']
	if photons:
		ntuples = ['tnj_photon_ALL', 'tnj_photon_EMC', 'tnj_photon_DMC']

	#cuts   = "(abs(eta)<1 && nEv==-1)*(xsec)"
	cuts   = "(nEv==-1)*(xsec)"
	#if medjcut != 'NA':
	#	cuts   = "(abs(eta)<1 && nEv==-1 && (maxj - medj) > {})*(xsec)".format(medjcut)
	#var    = 'pT'
	bwidth = 10
	xlow   = 0
	xhigh  = 250

	title  = '-'.join(['pT', 'f', '{}'.format(nfile), '{}'.format(photons), var, cuts])
	hltmp = dlist.dlist(title)
	hltmp.make_canvas()
	for ntname in ntuples:
		h 	   = tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)
		hltmp.add(h, ntname, 'p E1')
		#hltmp.add(h, title, 'hist l E1')
		nEv = tu.get_max_from_ntuple(fname, ntname, 'nEv')
		if nEv<=0 or nEv==None:
			nEv = 10000. - 1.
		#print '[i] scaling by nEv: ', nEv+1.

	hltmp.reset_axis_titles('p_{T}', 'd#sigma/dp_{T} (mb/cGeV)')
	hltmp.scale_by_binwidth(True)
	hltmp.scale(1./(nEv * 1. + 1.))

	#hltmp.destroy_canvas()

	tu.gList.append(hltmp)

	return hltmp

def draw_pT_xsec(photons=False, var='pT'):
	hlj = get_pT(photons=photons, var=var)
	hlj.make_canvas()
	hlj.draw()
	hlj.self_legend()
	ROOT.gPad.SetLogy()
	hlj.update()

	if '--print' in sys.argv:
		hlj.pdf()

def draw_pT_yields(photons=False, var='pT'):
	hlj = get_pT(photons=photons, var=var)
	hlj.name = hlj.name + '_yats'
	hlj.make_canvas()
	hlj.draw()
	hlj.self_legend()
	ROOT.gPad.SetLogy()
	hlj.update()

	dopt = 'p'
	dopt = 'l hist'

	sigmaPbPb = 7.7

	cent = centrality.Centrality()
	lname = 'pT_yields_{}_{}'.format(photons, var)
	lstore = dlist.ListStorage(lname)
	for ib,taa in enumerate(cent.TAAs()):
		nEv   = 220. * 1.e6 * sigmaPbPb * cent.BinWidth(ib)
		#print ib, taa
		scale = taa * nEv

		hljtmp = dlist.dlist('hljtmp')
		hljtmp.copy(hlj)
		hljtmp.scale(scale)

		htitle = 'EMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields EMC', hljtmp[1].obj, htitle, dopt)
		htitle = 'DMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields DMC', hljtmp[2].obj, htitle, dopt)

		yats = dlist.yats(hljtmp)
		htitle = 'yat EMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yats EMC', yats[1].obj, htitle, dopt)
		htitle = 'yat DMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yats DMC', yats[2].obj, htitle, dopt)

		#yats.destroy_canvas()

	lstore.get('yields EMC').reset_axis_titles('p_{T}', 'dN/dp_{T} (c/GeV)')
	lstore.get('yields DMC').reset_axis_titles('p_{T}', 'dN/dp_{T} (c/GeV)')

	lstore.get('yats EMC').reset_axis_titles('p_{T}', 'yield above p_{T}')
	lstore.get('yats DMC').reset_axis_titles('p_{T}', 'yield above p_{T}')

	lstore.legend_position(0.5, 0.5, 0.7, 0.85)
	lstore.zoom_axis(0, 0, 150)
	if photons==False:
		lstore.draw_all(logy=True, miny=10);
	else:
		lstore.draw_all(logy=True, miny=0.1);		
	for ip in range(1, len(lstore.lists) + 1):
		lstore.tcanvas.cd(ip)
		ROOT.gPad.SetGridy()
		ROOT.gPad.SetGridx()

	if '--print' in sys.argv:
		lstore.pdf()

def draw_patch_yields(photons=False, var='pT'):
	hlj = get_pT(photons=photons, var=var)
	hlj.name = hlj.name + '_yats'
	hlj.make_canvas()
	hlj.draw()
	hlj.self_legend()
	ROOT.gPad.SetLogy()
	hlj.update()

	dopt = 'p'
	dopt = 'l hist'

	sigmaPbPb = 7.7

	cent = centrality.Centrality()
	lname = 'patch_yields_{}_{}'.format(photons, var)
	lstore = dlist.ListStorage(lname)
	for ib,taa in enumerate(cent.TAAs()):
		nEv   = 220. * 1.e6 * sigmaPbPb * cent.BinWidth(ib)
		#print ib, taa
		scale = taa #* nEv

		hljtmp = dlist.dlist('hljtmp')
		hljtmp.copy(hlj)
		hljtmp.scale(scale)

		htitle = 'EMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields EMC', hljtmp[1].obj, htitle, dopt)
		htitle = 'DMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields DMC', hljtmp[2].obj, htitle, dopt)

	lstore.get('yields EMC').reset_axis_titles('patch Energy', 'dN/dp_{T} (c/GeV)')
	lstore.get('yields DMC').reset_axis_titles('patch Energy', 'dN/dp_{T} (c/GeV)')

	lstore.legend_position(0.3, 0.5, 0.7, 0.85)
	lstore.zoom_axis(0, 0, 150)
	if photons==False:
		lstore.draw_all(logy=True, miny=1e-6);
	else:
		lstore.draw_all(logy=True, miny=1e-6);
	for ip in range(1, len(lstore.lists) + 1):
		lstore.tcanvas.cd(ip)
		ROOT.gPad.SetGridy()
		ROOT.gPad.SetGridx()

	if '--print' in sys.argv:
		lstore.pdf()

if __name__ == '__main__':
	tu.setup_basic_root()
	#draw_pT_xsec()
	#draw_pT_xsec(photons=True)

	#draw_pT_yields(False, 'pT')
	#draw_pT_yields(True, 'pT')

	draw_patch_yields(False, 'maxj')
	draw_patch_yields(False, 'maxj-medj')
	draw_patch_yields(False, 'maxg')

	if not ut.is_arg_set('-b'):
		IPython.embed()


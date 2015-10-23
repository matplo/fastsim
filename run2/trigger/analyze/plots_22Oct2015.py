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

	print '[i] using EMCalKeepOutFactor with R=', R, retval

	return retval

def DCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 80. / 360. * math.pi * 2. #not 70 deg?

	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)

	print '[i] using DCalKeepOutFactor with R=', R, retval

	return retval

class NTFiles(object):
	def __init__(self):
		self.basedir=self._guess_dir()
		self.files= [
		'default_emctrig_out_femc_1.0.root',
		'_data1_run2_trigger_2015-10-22_5TeV_default_emctrig_out_femc_1.0.root'
		]

	def _guess_dir(self):
		sdirs = [
			'/Users/ploskon/devel/sandbox/run2/trigger/generate/5TeV/hardQCD/mult-0',
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-22/5TeV',
			'/Volumes/MP/data/run2/trigger/2015-10-22/5TeV' 
			]
		for s in sdirs:
			if os.path.isdir(s):
				print '[i] NTFiles: basedir guessed:',s
				return s
		print >> sys.stderr, '[w] NTFiles: basedir not guessed. set :basedir manually. using os.getcwd()'
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
def get_pT(photons=False, femc=0.1, var='pT', usercut='(1)', cal='all'):
	ntfs  = NTFiles()
	nfile = 0
	fname = ntfs.get_file(nfile, femc, photons)

	ntuples = ['jets_hard_EMC', 'jets_hard_EMCc', 'jets_hard_DMCc']
	if photons:
		ntuples = ['tnj_photon_ALL', 'tnj_photon_EMC', 'tnj_photon_DMC']

	#cuts   = "(abs(eta)<1 && nEv==-1)*(xsec)"
	cuts   = "(nEv==-1 && {})*(xsec)".format(usercut)
	#if medjcut != 'NA':
	#	cuts   = "(abs(eta)<1 && nEv==-1 && (maxj - medj) > {})*(xsec)".format(medjcut)
	#var    = 'pT'
	bwidth = 5
	xlow   = 0
	xhigh  = 300

	title  = '-'.join(['pT', 'f', '{}'.format(nfile), '{}'.format(photons), var, cuts])
	hltmp = dlist.dlist(title)
	tu.getTempCanvas().cd()
	for i,ntname in enumerate(ntuples):
		if cal=='EMC' and i!=1:
			continue
		if cal=='DMC' and i!=2:
			continue
		h 	   = tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)
		if i==1:
			h.Scale(EMCalKeepOutFactor(0.2))
		if i==2:
			h.Scale(DCalKeepOutFactor(0.2))			
		hltmp.add(h, ntname, 'p E1')
		#hltmp.add(h, title, 'hist l E1')
		nEv = tu.get_max_from_ntuple(fname, ntname, 'nEv')
		if nEv<=0 or nEv==None:
			nEv = 10000. - 1.
		#print '[i] scaling by nEv: ', nEv+1.

	hltmp.reset_axis_titles('p_{T}', 'd#sigma/dp_{T} (mb/cGeV)')
	hltmp.scale_by_binwidth(True)
	hltmp.scale(1./(nEv * 1. + 1.))

	return hltmp

def draw_pT_xsec(photons=False, var='pT', usercut='(1)'):
	hlj = get_pT(photons=photons, var=var, usercut='(1)')
	if usercut != '(1)':
		hljc = get_pT(photons=photons, var=var, usercut=usercut)
		hlj.add_list(hljc)
	hlj.make_canvas()
	hlj.draw()
	hlj.self_legend()
	ROOT.gPad.SetLogy()
	hlj.update()

	tu.gList.append(hlj)

	if '--print' in sys.argv:
		hlj.pdf()

def draw_pT_yields(photons=False, var='pT'):

	dopt = 'p'
	dopt = 'l hist'

	intLumi = 220. * 1.e6

	cent = centrality.Centrality()
	lname = 'pT_yields_{}_{}'.format(photons, var)
	lstore = dlist.ListStorage(lname)
	for ib,taa in enumerate(cent.TAAs()):
		centBins = cent.BinRange(ib)
		centcut = "(npart >= {} && npart < {})".format(centBins[0], centBins[1])
		nEv = cent.BinPbPbNEvents(ib, intLumi)
		print ib, cent.Label(ib), centcut, nEv

		hlj = get_pT(photons=photons, var=var, usercut=centcut, cal='all')
		#hlj.scale(taa * nEv)
		hlj.scale(taa * nEv / cent.BinWidth(ib))
		print '[w] weighting depends how events were generated - xsection per cent bin...!'

		htitle = 'EMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields EMC', hlj[1].obj, htitle, dopt)
		htitle = 'DMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields DMC', hlj[2].obj, htitle, dopt)

		yats = dlist.yats(hlj)
		htitle = 'yat EMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yats EMC', yats[1].obj, htitle, dopt)
		htitle = 'yat DMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yats DMC', yats[2].obj, htitle, dopt)

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

#triggers->Draw("JEmaxECAL:npart>>h(100,0,100,200,0,100)", "(1)*(xsec)", "colz")
def draw_patch_yields(photons=False, var='pT'):

	dopt = 'p'
	dopt = 'l hist'

	intLumi = 220. * 1.e6

	cent = centrality.Centrality()
	lname = 'patch_yields_{}_{}'.format(photons, var)
	lstore = dlist.ListStorage(lname)
	for ib,taa in enumerate(cent.TAAs()):
		centBins = cent.BinRange(ib)
		centcut = "(npart >= {} && npart < {})".format(centBins[0], centBins[1])
		nEv = cent.BinPbPbNEvents(ib, intLumi)
		print ib, cent.Label(ib), centcut, nEv

		hlj = get_pT(photons=photons, var=var, usercut=centcut)
		hlj.name = hlj.name + '_cent_{}'.format(ib)
		#hlj.make_canvas()
		#hlj.draw()
		#hlj.self_legend()
		#ROOT.gPad.SetLogy()
		#hlj.update()
	
		hljtmp = dlist.dlist('hljtmp')
		hljtmp.copy(hlj)
		hljtmp.scale(taa / cent.BinWidth(ib))
		print '[w] weighting depends how events were generated - xsection per cent bin...!'

		htitle = 'EMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields EMC', hljtmp[1].obj, htitle, dopt)
		htitle = 'DMC {} (nEv={:.1f} M)'.format(cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('yields DMC', hljtmp[2].obj, htitle, dopt)

	lstore.get('yields EMC').reset_axis_titles(var, 'dN/dp_{T} (c/GeV)')
	lstore.get('yields DMC').reset_axis_titles(var, 'dN/dp_{T} (c/GeV)')

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
		lstore.update()

	if '--print' in sys.argv:
		lstore.pdf()

def draw_pT_bias(photons=False, cal='EMC', varcut='maxj', thrs = [60, 50, 40, 30, 20, 10, 5]):
	var     ='pT'
	dopt    ='p'
	doptr   ='l hist'
	cent    = centrality.Centrality()
	lname   = 'yields_bias_{}_{}_{}_{}'.format(cal, photons, var, varcut)	
	lstore  = dlist.ListStorage(lname)
	
	lname   = 'ratio_bias_{}_{}_{}_{}'.format(cal, photons, var, varcut)	
	lstorer = dlist.ListStorage(lname)

	if cal!='EMC' and cal!='DMC':
		print '[i]', draw_pT_bias, 'cal arg can be only EMC or DMC - stop here'
		return None

	intLumi = 220. * 1.e6
	for ib,taa in enumerate(cent.TAAs()):
		centBins = cent.BinRange(ib)
		centcut = "(npart >= {} && npart < {})".format(centBins[0], centBins[1])
		nEv = cent.BinPbPbNEvents(ib, intLumi)
		print ib, cent.Label(ib), centcut, nEv

		hlj = get_pT(photons=photons, var=var, usercut=centcut, cal=cal)
		hlj.scale(taa * nEv)
		#hlj.make_canvas()
		#hlj.draw()
		#hlj.self_legend()
		#ROOT.gPad.SetLogy()
		#hlj.update()

		thrcut = '({} > {})'.format(varcut, thrs[ib])
		sumcut = '{} && {}'.format(centcut, thrcut)

		hljc = get_pT(photons=photons, var=var, usercut=sumcut, cal=cal)
		hljc.scale(taa * nEv)
		#hljc.make_canvas()
		#hljc.draw()
		#hljc.self_legend()
		#ROOT.gPad.SetLogy()
		#hljc.update()

		htitle = '{} {} (nEv={:.1f} M)'.format(cal, cent.Label(ib), nEv/1.e6)
		lstore.add_to_list('{} yields {}'.format(cal, cent.Label(ib)), hlj[0].obj, htitle, dopt)
		htitle = '{} {} trig'.format(cal, cent.Label(ib))
		lstore.add_to_list('{} yields {}'.format(cal, cent.Label(ib)), hljc[0].obj, htitle, dopt)

		hlrtmp = dlist.make_ratio(hljc[0].obj, hlj[0].obj)
		htitle = '{} {}'.format(cent.Label(ib), thrcut)
		lstorer.add_to_list('{} bias'.format(cal), hlrtmp[0].obj, htitle, doptr)

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
		lstore.update()

	lstorer.legend_position(0.3, 0.6, 0.7, 0.85)
	lstorer.zoom_axis(0, 0, 150)
	lstorer.draw_all(logy=False, miny=0., maxy=2.);

	if '--print' in sys.argv:
		lstore.pdf()
		lstorer.pdf()

if __name__ == '__main__':
	tu.setup_basic_root()
	draw_pT_xsec()
	#draw_pT_xsec(photons=True)

	draw_pT_yields(False, 'pT')
	#draw_pT_yields(True, 'pT')

	#draw_patch_yields(False, 'maxj')
	#draw_patch_yields(False, 'maxj-medj')
	#draw_patch_yields(False, 'maxg')

	#draw_pT_xsec(photons=False, var='pT', usercut='((maxj-medj)>20)')

	#draw_pT_bias(photons=False, cal='EMC', varcut='maxj', thrs = [60, 50, 40, 30, 20, 10, 5])
	#draw_pT_bias(photons=False, cal='EMC', varcut='maxj-medj', thrs = [43.5, 43, 42.5, 40, 30, 25, 20])

	if not ut.is_arg_set('-b'):
		IPython.embed()


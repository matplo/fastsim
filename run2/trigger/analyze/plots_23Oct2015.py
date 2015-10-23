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
			'default_emctrig_out_R_0.4_femc_1.0.root'
			]

	def _guess_dir(self):
		sdirs = [
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-23/5TeV/hardQCD',
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

	def get_file(self, femc=1.0, photons=False, R=0.4):
		retval = os.path.join(self.basedir, self.files[0])
		if femc < 1.0:
			retval = retval.replace("femc_1.0", "femc_{}".format(femc))
		if photons == True:
			retval = retval.replace("_hardQCD_", "_photons_")
		if R!=0.4:
			retval = retval.replace("_R_0.4_", "_R_0.2_")
		return retval

def to_file_name(s):
	return "".join([x if x.isalnum() else "_" for x in s])

def get_pT(fname, photons=False, femc=0.1, var='pT', usercut='(1)', cal='all', R=0.4):
	ntuples = ['jets_hard_EMC', 'jets_hard_EMCc', 'jets_hard_DMCc']
	if photons:
		ntuples = ['tnj_photon_ALL', 'tnj_photon_EMC', 'tnj_photon_DMC']

	cuts   = "(nEv==-1 && {})*(xsec)".format(usercut)

	bwidth = 20
	xlow   = 0
	xhigh  = 200

	what = 'jets'
	if photons:
		what = 'photons'
	title = '{}-femc-{}-var-{}-usercut-{}-calo-{}-R-{}'.format(what, femc, var, usercut, cal, R)
	title = to_file_name(title)
	hltmp = dlist.dlist(title)
	tu.getTempCanvas().cd()
	for det in cal.split(' '):
		idet = -1
		if det=='all': idet = 0
		if det=='EMC': idet = 1
		if det=='DMC': idet = 2
		if idet < 0: continue

		ntname = ntuples[idet]
		h 	   = tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)
		if idet==1:
			h.Scale(EMCalKeepOutFactor(R))
		if idet==2:
			h.Scale(DCalKeepOutFactor(R))
		title  = '{}-femc:{}-var:{}-usercut:{}-R:{}'.format(what, femc, var, usercut, R)
		htitle = ntname.replace('_', ' ') + ' ' + title.replace('-', ' ')
		hltmp.add(h, htitle, 'p E1')
		#hltmp.add(h, title, 'hist l E1')
		nEv = tu.get_max_from_ntuple(fname, ntname, 'nEv')
		if nEv<=0 or nEv==None:
			nEv = 10000. - 1.
		#print '[i] scaling by nEv: ', nEv+1.

	if len(hltmp) > 0:
		hltmp.reset_axis_titles('p_{T}', 'd#sigma/dp_{T} (mb/cGeV)')
		hltmp.scale_by_binwidth(True)
		hltmp.scale(1./(nEv * 1. + 1.))

	return hltmp

def draw_pT_xsec(fname, photons=False, femc=0.1, R=0.4, usercut='(1)', cal='all', var='pT'):
	#hlj = get_pT(fname, photons=photons, femc=femc, var=var, usercut='(1)', cal=cal, R=R)
	#if usercut != '(1)':
	#	hljc = get_pT(fname, photons=photons, femc=femc, var=var, usercut=usercut, cal=cal, R=R)
	#	hlj.add_list(hljc)
	hlj = get_pT(fname, photons=photons, femc=femc, var=var, usercut=usercut, cal=cal, R=R)
	hlj.make_canvas(w=600,h=600)
	hlj.draw()
	hlj.self_legend(x1=0.25, x2=0.45)
	ROOT.gPad.SetLogy()
	hlj.update()
	tu.gList.append(hlj)
	if '--print' in sys.argv:
		hlj.pdf()
	if '--write' in sys.argv:
		hlj.write_to_file()

def draw_AA_yield(fname, photons=False, femc=0.1, R=0.4, cal='all', var='pT', useLint=0):

	if cal=='all':
		print '[w] draw_AA_yield works best for EMC or DMC... ;-)'
		return 

	cent = centrality.Centrality()

	what = 'jets'
	if photons:
		what = 'photons'
	title = to_file_name('AAyields-{}-femc-{}-var-{}-calo-{}-R-{}'.format(what, femc, var, cal, R))
	if useLint > 0:
		title = title.replace('AAyields', 'AAyieldsLint')
	hlj = dlist.dlist(title)
	for ib,taa in enumerate(cent.TAAs()):
		usercut='(npart >= {} && npart < {})'.format(cent.BinLow(ib), cent.BinHigh(ib))
		print ib, cent.Label(ib), taa, usercut
		hl = get_pT(fname, photons=photons, femc=femc, var=var, usercut=usercut, cal=cal, R=R)
		hl[0].obj.SetTitle(cal + ' ' + cent.Label(ib))
		hl.scale(taa / cent.BinWidth(ib)) #correct for loss of stats when cutting on cent
		if useLint > 0:
			hl.scale(cent.BinPbPbNEvents(ib, intLumi))
		hl[0].obj.SetTitle(cal + ' ' + cent.Label(ib) + ' ({:.1f}M) '.format(cent.BinPbPbNEvents(ib, intLumi)/1.e6))
		hlj.add_list(hl)

	hlj.make_canvas(w=600,h=600)
	hlj.draw()
	hlj.self_legend(x1=0.35, x2=0.45)
	ROOT.gPad.SetLogy()
	hlj.update()
	tu.gList.append(hlj)
	if '--print' in sys.argv:
		hlj.pdf()
	if '--write' in sys.argv:
		hlj.write_to_file(name_mod='modn:')

if __name__ == '__main__':
	tu.setup_basic_root()

	ntfs  = NTFiles()
	photons = False
	femc = 0.1
	R=0.4
	usercut='(1)'
	cal='all'
	var='pT'
	fname = ntfs.get_file(femc, photons, R)
	#draw_pT_xsec(fname, photons, femc, R, usercut, cal, var)
	usercut='(maxj>20)'
	#draw_pT_xsec(fname, photons, femc, R, usercut, cal, var)

	intLumi = 220. * 1.e6
	cal = 'EMC'
	draw_AA_yield(fname, photons, femc, R, cal, var)
	draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)
	cal = 'DMC'
	draw_AA_yield(fname, photons, femc, R, cal, var)
	draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)

	if not ut.is_arg_set('-b'):
		IPython.embed()


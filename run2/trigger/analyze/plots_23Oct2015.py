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

	#print '[i] using EMCalKeepOutFactor with R=', R, retval

	return retval

def DCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 80. / 360. * math.pi * 2. #not 70 deg?

	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)

	#print '[i] using DCalKeepOutFactor with R=', R, retval

	return retval

class NTFiles(object):
	def __init__(self, adir=''):
		self.basedir = adir
		if adir=='' or adir==None:
			self.basedir=self._guess_dir()
		print '[i] basedir:',self.basedir
		if os.path.isdir(self.basedir)==False:
			print >> sys.stderr, '[w] basedir is not a directory:',self.basedir
		self.files= [
			'default_emctrig_out_R_0.4_femc_1.0.root',
			'default_emctrig_out_R_0.4_femc_1.0.root'
			]

	def _guess_dir(self):
		sdirs = [
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-26',
			'/Volumes/SAMSUNG/data/run2/trigger/2015-10-23/5TeV/hardQCD',
			'/Volumes/MP/data/run2/trigger/2015-10-23/5TeV/hardQCD',
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
		if os.path.isfile(retval)==False:
			print >> sys.stderr,'[e] not a file:',retval
			raise IOError(retval)
			retval = None
		print "[i] using file:",retval
		return retval

def to_file_name(s):
	return "".join([x if x.isalnum() else "_" for x in s])

def get_pT(fname, photons=False, femc=0.1, var='pT', usercut='(1)', cal='all', R=0.4):
	ntuples = ['jets_hard_EMC', 'jets_hard_EMCc', 'jets_hard_DMCc']
	if photons:
		ntuples = ['tnj_photon_ALL', 'tnj_photon_EMC', 'tnj_photon_DMC']

	cuts   = "(nEv==-1 && {})*(xsec)".format(usercut)

	bwidth = 10
	xlow   = 0
	xhigh  = 300

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
		hltmp.reset_axis_titles(var, 'd#sigma/d{}'.format(var))
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

def draw_bias(fname, photons=False, femc=0.1, R=0.4, cal='all', var='pT', thrs=[0], threxp='maxj'):
	if cal=='all':
		print '[w] draw_AA_yield works best for EMC or DMC... ;-)'
		return 

	print '[i] bias for:',var,'for:',cal

	cent = centrality.Centrality()

	what = 'jets'
	if photons:
		what = 'photons'
	title = 'draw-bias-{}-femc-{}-var-{}-calo-{}-R-{}'.format(what, femc, var, cal, R)
	title = title + '{}-'.format(threxp) + '-'.join(str(n) for n in thrs)
	title = to_file_name(title)
	hl = dlist.dlist(title)

	hljnc = get_pT(fname, photons=photons, femc=femc, var=var, usercut='(1)', cal=cal, R=R)
	hljnc[0].obj.SetTitle('unbiased')
	hljnc[0].obj.SetName('unbiased')
	hl.add(hljnc[0].obj, 'unbiased', 'hist l')

	for ib,thr in enumerate(thrs):
		usercut='({} > {})'.format(threxp, thr)
		hljc  = get_pT(fname, photons=photons, femc=femc, var=var, usercut=usercut, cal=cal, R=R)
		hljc[0].obj.SetTitle(usercut)
		hljc[0].obj.SetName(to_file_name(usercut))
		#hljnc.add_list(hljc)
		centcuts='{}-{}%'.format(cent.BinLow(ib), cent.BinHigh(ib))
		newtitle = '{} : {} > {}'.format(centcuts, threxp, thr)
		hl.add(hljc[0].obj, newtitle, 'hist l')

	hlr = hl.ratio_to()
	hlr.reset_axis_titles(var, 'ratio: {} cut / min. bias'.format(threxp))
	hlr.make_canvas(w=600,h=600)
	hlr.draw('hist l')
	#hlj.self_legend(x1=0.25, x2=0.45)
	hlr.self_legend(x1=0.48,y1=0.4,x2=0.72,y2=0.6)
	#ROOT.gPad.SetLogy()
	hlr.update()
	tu.gList.append(hlr)
	if '--print' in sys.argv:
		hlr.pdf()
	if '--write' in sys.argv:
		hlr.write_to_file()

def draw_bias_cent(fname, photons=False, femc=0.1, R=0.4, cal='all', var='pT', thrs=[0], threxp='maxj'):
	if cal=='all':
		print '[w] draw_AA_yield works best for EMC or DMC... ;-)'
		return 

	print '[i] bias for:',var,'for:',cal

	cent = centrality.Centrality()

	what = 'jets'
	if photons:
		what = 'photons'
	title = 'draw-bias-{}-femc-{}-var-{}-calo-{}-R-{}'.format(what, femc, var, cal, R)
	title = title + '{}-'.format(threxp) + '-'.join(str(n) for n in thrs)
	title = to_file_name(title)
	hl = dlist.dlist(title)
	for ib,thr in enumerate(thrs):
		centcut='(npart >= {} && npart < {})'.format(cent.BinLow(ib), cent.BinHigh(ib))
		centcuts='{}-{}%'.format(cent.BinLow(ib), cent.BinHigh(ib))
		hljnc = get_pT(fname, photons=photons, femc=femc, var=var, usercut=centcut, cal=cal, R=R)
		hljnc[0].obj.SetTitle('unbiased {}'.format(centcuts))
		hljnc[0].obj.SetName('unbiased {}'.format(centcuts))
		usercut='({} > {}) && ({})'.format(threxp, thr, centcut)
		hljc  = get_pT(fname, photons=photons, femc=femc, var=var, usercut=usercut, cal=cal, R=R)
		newtitle = '{} : {} > {}'.format(centcuts, threxp, thr)
		hljc[0].obj.SetTitle(newtitle)
		hljc[0].obj.SetName(to_file_name(newtitle))
		hljnc.add_list(hljc)
		hlj = hljnc.ratio_to()
		#hl.add_list(hlj)
		hl.add(hlj[0].obj, newtitle, 'hist l')

	hl.reset_axis_titles(var, 'ratio: {} cut / min. bias'.format(threxp))
	hl.make_canvas(w=600,h=600)
	hl.draw('hist l')
	#hl.self_legend(x1=0.25, x2=0.45)
	hl.self_legend(x1=0.52,y1=0.4,x2=0.72,y2=0.6)
	#ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hl.update()
	tu.gList.append(hl)
	if '--print' in sys.argv:
		hl.pdf()
	if '--write' in sys.argv:
		hl.write_to_file()

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
		#usercut='(npart >= {} && npart < {})'.format(cent.BinLow(ib), cent.BinHigh(ib))
		usercut='(pT>20)'
		#print ib, cent.Label(ib), taa, usercut
		hl = get_pT(fname, photons=photons, femc=femc, var=var, usercut=usercut, cal=cal, R=R)
		hl[0].obj.SetTitle(cal + ' ' + cent.Label(ib))
		hl[0].obj.SetName(cal + '_' + cent.Label(ib))
		#hl.scale(taa / cent.BinWidth(ib)) #correct for loss of stats when cutting on cent
		hl.scale(taa) #do not correct for loss of stats when not cutting on cent
		if useLint > 0:
			hl.scale(cent.BinPbPbNEvents(ib, useLint))
			hl[0].obj.SetTitle(cal + ' ' + cent.Label(ib) + ' ({:.1f}M) '.format(cent.BinPbPbNEvents(ib, useLint)/1.e6))
		hlj.add_list(hl)

	if useLint > 0:
		hlj.reset_axis_titles('p_{T}', 'dN/dp_{T} (c/GeV)')
	else:
		hlj.reset_axis_titles('p_{T}', '1/N_{ev} dN/dp_{T} (c/GeV)')
	hlj.make_canvas(w=600,h=600)
	if useLint > 0:
		hlj.draw(miny=5e-2, maxy=5e7)
	else:
		hlj.draw(miny=5e-11, maxy=9e-1)
	hlj.self_legend(x1=0.55, x2=0.45)
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()

	hlj.update()
	tu.gList.append(hlj)
	if '--print' in sys.argv:
		hlj.pdf()
	if '--write' in sys.argv:
		#hlj.write_to_file(name_mod='modn:')
		hlj.write_to_file()

def get_trigger(fname, photons=False, femc=0.1, var='JEmaxECAL', usercut='(1)', R=0.4, ntname='triggers'):

	#print usercut
	cuts   = "({})*(xsec)".format(usercut)

	bwidth = 1
	xlow   = -100
	xhigh  =  200

	what = 'jets'
	if photons:
		what = 'photons'
	title = '{}-femc-{}-var-{}-usercut-{}-R-{}-ntname-{}'.format(what, femc, var, usercut, R, ntname)
	title = to_file_name(title)
	hltmp = dlist.dlist(title)
	tu.getTempCanvas().cd()
	h 	   = tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title)
	title  = '{}-femc:{}-var:{}-usercut:{}-R:{}'.format(what, femc, var, usercut, R)
	htitle = ntname.replace('_', ' ') + ' ' + title.replace('-', ' ')
	hltmp.add(h, htitle, 'l hist')
	#hltmp.add(h, title, 'hist l E1')
	nEv = tu.get_max_from_ntuple(fname, ntname, 'nEv')
	if nEv<=0 or nEv==None:
		nEv = 10000. - 1.
	#print '[i] scaling by nEv: ', nEv+1.
	if len(hltmp) > 0:
		hltmp.reset_axis_titles(var, 'd#sigma/d{} (mb/cGeV)'.format(var))
		#hltmp.scale_by_binwidth(True)
		hltmp.scale(1./(nEv * 1. + 1.))
	return hltmp

def rejection_table(hl, rej = 1.e-3):
	print '[i] rejections for', hl.name, 'rej:',rej
	retvals = []
	for o in hl.l:
		h = o.obj
		for ib in range(1, h.GetNbinsX()):
			if h.GetBinContent(ib) <= rej:
				print '    ', h.GetTitle(), h.GetBinLowEdge(ib), h.GetBinContent(ib)
				newtitle = '{} [{:.0e}@{:.1f}]'.format(h.GetTitle(), rej, h.GetBinLowEdge(ib))
				h.SetTitle(newtitle)
				retvals.apepnd(h.GetBinLowEdge(ib))
				break
	return retvals

#def get_pT(fname, photons=False, femc=0.1, var='pT', usercut='(1)', cal='all', R=0.4):
def draw_trigger_rates(fname, photons=False, femc=0.1, R=0.4, var='JEmaxECAL', ntname='triggers', cal='EMC'):
	if cal=='all':
		print '[w] draw_AA_yield works best for EMC or DMC... ;-)'
		return 

	print '[i] trigger rates for:',var,'from',ntname

	cent = centrality.Centrality()

	what = 'jets'
	if photons:
		what = 'photons'
	title = to_file_name('trigger-{}-femc-{}-var-{}-R-{}-ntname-{}'.format(what, femc, var, R, ntname))
	hlj = dlist.dlist(title)
	for ib,taa in enumerate(cent.TAAs()):
		usercut='(npart >= {} && npart < {})'.format(cent.BinLow(ib), cent.BinHigh(ib))
		#print ib, cent.Label(ib), taa, usercut
		hl = get_trigger(fname, photons, femc, var, usercut, R, ntname)
		hl[0].obj.SetTitle(cal + ' ' + cent.Label(ib))
		hl[0].obj.SetName(cal + '_' + cent.Label(ib))
		hl.scale(taa / cent.BinWidth(ib)) #correct for loss of stats when cutting on cent
		hlj.add_list(hl)

	hlj.reset_axis_titles(var, '1/N dN/d{} (c/GeV)'.format(var))
	hlj.make_canvas(w=600,h=600)
	hlj.draw()
	hlj.self_legend(x1=0.65, x2=0.95)
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hlj.update()
	tu.gList.append(hlj)

	fyats = dlist.fractional_yats(hlj)
	fyats.reset_axis_titles(yt='rejection factor')
	rjt1 = rejection_table(fyats, 1e-3)
	rjt2 = rejection_table(fyats, 1e-2)
	fyats.make_canvas(w=600,h=600)
	fyats.draw(miny=2.e-4, maxy=70.)
	if 'GAmaxECAL' in var or 'GAmaxDCAL' in var:
		fyats.zoom_axis(0, 0, 30)
	else:		
		fyats.zoom_axis(0, 0, 70)
	if var=='maxg-medj/16.':
		fyats.zoom_axis(0, 0, 20)
	else:		
		fyats.zoom_axis(0, 0, 70)		
	fyats.self_legend(x1=0.2, x2=0.95)
	ROOT.gPad.SetLogy()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	fyats.update()
	tu.gList.append(fyats)

	if '--print' in sys.argv:
		hlj.pdf()
		fyats.pdf()

	if '--write' in sys.argv:
			#hlj.write_to_file(name_mod='modn:')
			hlj.write_to_file()
			fyats.write_to_file()

if __name__ == '__main__':
	tu.setup_basic_root()

	bdir = ''
	bdir = tu.get_arg_with('--dir')

	ntfs  = NTFiles(bdir)
	photons = False
	femc = 0.3
	#femc = 1.0
	R=0.4
	usercut='(1)'
	cal='all'
	var='pT'
	fname = ntfs.get_file(femc, photons, R)

	if '--xsec' in sys.argv:
		draw_pT_xsec(fname, photons, femc, R, usercut, cal, var)
		draw_pT_xsec(fname, photons, femc, R, usercut, cal, var='medj')

	if '--bias' in sys.argv:
		var='pT'

		jethr = [58.5, 43, 31, 19, 15, 14]
		#draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp='maxj')
		#draw_bias(fname, photons, femc, R, usercut, 'DMC', var)

		#jethr = [36, 24.5, 16.5, 8, 4, 4]
		#jethr = [1, 2, 3, 4, 5, 6]
		#draw_bias(fname, photons, femc, R, 'EMC', var='maxj', thrs=jethr, threxp='medj')

		#var = "(pT + rho * 0.5)"
		jethr = [33, 27, 21, 16, 14, 13] #made with femc=0.3
		draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp='maxj-medj')
		#draw_bias_cent(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp='maxj-medj')

		#jethr = [28, 23, 18, 12,  8,  7] #made with femc=0.3
		#draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp='maxj-medj')

	if '--yields' in sys.argv:
		intLumi = 220. * 1.e6
		cal = 'EMC'
		draw_AA_yield(fname, photons, femc, R, cal, var)
		draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)
		cal = 'DMC'
		draw_AA_yield(fname, photons, femc, R, cal, var)
		draw_AA_yield(fname, photons, femc, R, cal, var, intLumi)

	##if '--centrality' in sys.argv:
	##	var='npart'
	##	jethr = [33, 28, 22, 16, 14, 12] #made with femc=0.3
	##	draw_bias(fname, photons, femc, R, 'EMC', var, thrs=jethr, threxp='maxj-medj')

	if '--trigger' in sys.argv:
		cal='EMC'

		#var='JEmaxECAL'
		#draw_trigger_rates(fname, photons, femc, R, var)
		var='JEmedDCAL'
		draw_trigger_rates(fname, photons, femc, R, var)
		var='medj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc')
		var='maxj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc')
		var='maxj-medj'
		draw_trigger_rates(fname, photons, femc, R, var, 'jets_hard_EMCc')
		var='JEmaxECAL - JEmedDCAL'
		draw_trigger_rates(fname, photons, femc, R, var)
		var='JEmaxECAL'
		draw_trigger_rates(fname, photons, femc, R, var)

		#var='GAmaxECAL'
		#draw_trigger_rates(fname, photons, femc, R, var)	
		#var='GAmedDCAL'
		#draw_trigger_rates(fname, photons, femc, R, var)	
		#var='GAmaxECAL - JEmedDCAL / 32.'
		#draw_trigger_rates(fname, photons, femc, R, var)

	if not ut.is_arg_set('-b'):
		IPython.embed()


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

def get_entries(fname):
	fin = ROOT.TFile.Open(fname)
	t = fin.Get("t")
	return t.GetEntries()

def get_Ei_median(indir, var='tgEJE.fE-tg.medjDCAL8x8*4', bwidth=1, xlow=-50, xhigh=300, cent=''):
	print '[i] get_Ei_median:',var
	tu.getTempCanvas().cd()
	tname = 't'
	if len(cent) > 0:
		cuts = '(xsec)*({})'.format(cent)
		refcuts = '(1)*({})'.format(cent)
	else:
		#cuts    = '(1)'
		cuts    = '(xsec)'
		refcuts = '(1)'
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir_filter(indir, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=-1, thr=5, fpatt='tree-*.root') #nev=10000, thr = 1 * bwidth/2.) #thr was 100!
	return hl

def main_patches(X = '', cent=''):
	#fname = './test/tree-default_emctrig_out_R_0.4_femcpar_mtune_1.2.root'
	#nentries = get_entries(fname)
	#print '[i] number of entries:', nentries

	ls = dlist.ListStorage('main')
	indir = './test'
	indir = './hardQCD/mtune1.2'

	dvars = [
		'tgXEJE.fE-tgX.medjDCAL8x8*4',
		'tgXEJE8x8.fE-tgX.medjDCAL8x8',
		'tgXDJE8x8.fE-tgX.medjECAL8x8',
		'tgXEGA.fE-tgX.medgDCAL',
		'tgXDGA.fE-tgX.medgECAL'		
	]

	#dvars = [
	#	'tgX.maxjEJE-tgX.medjDCAL8x8*4',
	#	'tgX.maxjEJE8x8-tgX.medjDCAL8x8',
	#	'tgX.maxjDJE8x8-tgX.medjECAL8x8',
	#	'tgX.maxgEGA.fE-tgX.medgDCAL',
	#	'tgX.maxgDGA-tgX.medgECAL'		
	#]

	print '[i] main_patches'
	for var in [v.replace('X',X) for v in dvars]:
		print '    main_patches:',var,'cent:',cent
		hl = get_Ei_median(indir, var, cent=cent)
		ls.append(hl)

	ls.draw_all(logy=True)
	ls.pdf()
	ls.write_all(mod='modn:')

### JET SPECTRA
def get_Ei_jetpt(indir, var='tgEJE.fE-tg.medjDCAL8x8*4', bwidth=15, xlow=0, xhigh=300, ucuts=''):
	print '[i] get_Ei_jetpt:',var
	tu.getTempCanvas().cd()
	tname = 't'
	if len(ucuts) > 0:
		cuts = '(xsec)*({})'.format(ucuts)
		refcuts = '(1)*({})'.format(ucuts)
	else:
		#cuts    = '(1)'
		cuts    = '(xsec)'
		refcuts = '(1)'
	tu.getTempCanvas().cd()
	hl = draw_ntuple.h1d_from_ntuple_dir_filter(indir, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=-1, thr=1, fpatt='tree-*.root') #nev=10000, thr = 1 * bwidth/2.) #thr was 100!
	return hl

def main_bias(X = '', cent='', thr=[15,8,9,4,4]):

	ls = dlist.ListStorage(tu.make_unique_name('jetpt', X, thr))
	indir = './test'
	indir = './hardQCD/mtune1.2'

	dcuts = [
		'tgXEJE.fE-tgX.medjDCAL8x8*4 > THR',
		'tgXEJE8x8.fE-tgX.medjDCAL8x8 > THR',
		'tgXDJE8x8.fE-tgX.medjECAL8x8 > THR',
		'tgXEGA.fE-tgX.medgDCAL > THR',
		'tgXDGA.fE-tgX.medgECAL > THR'		
	]

	dcuts = [
		'tgX.maxjEJE-tgX.medjDCAL8x8*4 > THR',
		'tgX.maxjEJE8x8-tgX.medjDCAL8x8 > THR',
		'tgX.maxjDJE8x8-tgX.medjECAL8x8 > THR',
		'tgX.maxgEGA.fE-tgX.medgDCAL > THR',
		'tgX.maxgDGA-tgX.medgECAL > THR'		
	]

	dvars = [
		'jE.fE',
		'jDr.fE',
		'jEr.fE',
		#'pi0E.fE',
		#'pi0D.fE',
	]

	print '[i] main_patches'
	for i,var in enumerate(dvars):
		for ic, dcut in enumerate(dcuts):
			if thr[ic] > 0:
				sdcuts = dcut.replace('X', X).replace('THR', '{}'.format(thr[ic]))
			else:
				sdcuts = ''
			print '    main_patches:',var,'cuts:',sdcuts
			hl = get_Ei_jetpt(indir, var, ucuts=sdcuts)
			hl.name = ut.to_file_name('bias_{}_{}_{}'.format(X, var, sdcuts))
			ls.append(hl)

	ls.draw_all(logy=True)
	ls.pdf()
	ls.write_all(mod='modn:')

def show_bias(X = '', cent='', thr=[15,8,9,4,4], det='EMC'):

	ls = dlist.ListStorage(tu.make_unique_name('showbias', X, thr, det))
	indir = './patch_rfiles'

	dcuts = [
		'tgX.maxjEJE-tgX.medjDCAL8x8*4 > THR',
		'tgX.maxjEJE8x8-tgX.medjDCAL8x8 > THR',
		'tgX.maxjDJE8x8-tgX.medjECAL8x8 > THR',
		'tgX.maxgEGA.fE-tgX.medgDCAL > THR',
		'tgX.maxgDGA-tgX.medgECAL > THR'		
	]

	dvars = [
		'jE.fE',
		'jEr.fE',
		'jDr.fE',
		'pi0E.fE',
		'pi0D.fE',
	]

	print '[i] main_patches'
	for i,var in enumerate(dvars):
		if det=='EMC':
			if i in [2,4]:
				continue
		else:
			if i in [0,1,3]:
				continue
		for ic, dcut in enumerate(dcuts):
			if det=='EMC':
				if ic in [2,4]:
					continue
			else:
				if ic in [0,1,3]:
					continue
			sdcuts = dcut.replace('X', X).replace('THR', '{}'.format(thr[ic]))
			mbfile = os.path.join(indir, ut.to_file_name('bias_{}_{}_{}'.format('', var, '')) + '.root' )
			cfile = os.path.join(indir, ut.to_file_name('bias_{}_{}_{}'.format(X, var, sdcuts)) + '.root' )
			hltmp = dlist.dlist('hltmp')
			hltmp.add_from_file('o_0', mbfile, 'l hist')
			if det=='DMC':
				hltmp.l[-1].obj.Rebin(2)
			hltmp.add_from_file('o_0', cfile,  'l hist')
			if det=='DMC':
				hltmp.l[-1].obj.Rebin(2)
			hlr = dlist.make_ratio(hltmp[1].obj, hltmp[0].obj)
			hlr.reset_axis_titles('E (GeV)', 'bias')
			hlrname = 'mask [{}] {}'.format(X, var)
			htitle  = '{}'.format(sdcuts.replace('tg', '').replace(X+'.', ''))
			ls.add_to_list(hlrname, hlr[0].obj, htitle, 'l hist')

	ls.legend_position(x1=0.25, y1=0.25, y2=0.4)
	ls.zoom_axis(0, 0, 150)
	ls.draw_all(logy=False)
	ls.pdf()
	ls.write_all(mod='modn:')

##END JET SPECTRA

def extra_smooth(hl, thr=5):
	for o in hl.l:
		h = o.obj
		for ib in range(2, h.GetNbinsX()):
			icl = h.GetBinContent(ib-1)
			ic0 = h.GetBinContent(ib)
			ich = h.GetBinContent(ib+1)
			if ic0 > thr * (icl + ich)/2.:
				print '    needs smooth bin ',h.GetTitle(),ib,ic0,h.GetBinCenter(ib)
				h.SetBinContent(ib, (icl + ich)/2.)
				err = (h.GetBinError(ib-1) + h.GetBinError(ib+1))/2.
				h.SetBinError(ib, err)

def main_rejections(X = '', cent=''):
	dvars = [
		'tgXEJE.fE-tgX.medjDCAL8x8*4',
		'tgXEJE8x8.fE-tgX.medjDCAL8x8',
		'tgXDJE8x8.fE-tgX.medjECAL8x8',
		'tgXEGA.fE-tgX.medgDCAL',
		'tgXDGA.fE-tgX.medgECAL'		
	]

	#dvars = [
	#	'tgX.maxjEJE-tgX.medjDCAL8x8*4',
	#	'tgX.maxjEJE8x8-tgX.medjDCAL8x8',
	#	'tgX.maxjDJE8x8-tgX.medjECAL8x8',
	#	'tgX.maxgEGA.fE-tgX.medgDCAL',
	#	'tgX.maxgDGA-tgX.medgECAL'		
	#]

	fdir = './patch_rfiles'

	hlname = fdir + ' ' + X
	hlname = ut.to_file_name(hlname)
	hl = dlist.dlist(hlname)

	print '[i] main_rejections'
	for var in [v.replace('X',X) for v in dvars]:
		fname = ut.to_file_name(var)
		print '    main_rejections:',var,fname
		if len(cent) > 0:
			flist = ut.find_files(fdir, '*'+fname+'*xsec*{}__filtered.root'.format(ut.to_file_name(cent)))
		else:
			flist = ut.find_files(fdir, '*'+fname+'*xsec__filtered.root')
		#flist = ut.find_files(fdir, '*'+fname+'*1*.root')
		for fn in flist:
			print '    found file:',fn
			htitle = var.replace('tgX'.replace('X', X), '').replace('.fE', ' ').replace('.',' ')
			hl.add_from_file('o_0', fn, htitle, 'l')

	extra_smooth(hl)

	#hl.make_canvas()
	#hl.draw(logy=True)
	#hl.self_legend()
	#hl.update(logy=True)
	tu.gList.append(hl)

	hlr = dlist.fractional_yats(hl)
	hlr.make_canvas(600,600)
	hlr.draw(logy=True, miny=1e-5, maxy=3e2)
	rejection_table(hlr, 8./8000.)
	rejection_table(hlr, 30./8000.)
	hlr.zoom_axis(0, -5, 45)
	hlr.reset_axis_titles('E_{i}^{A} - median{E_{j}^{B}} (GeV)', 'rejection')
	hlr.self_legend(1, 'dead channel map [{}]'.format(X), x1=0.2,x2=0.9)
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()
	hlr.update(logy=True)
	hlr.pdf()
	tu.gList.append(hlr)

def main_centrality_patch(X = ''):
	dvars = [
		#'tgXEJE.fE-tgX.medjDCAL8x8*4',
		#'tgXEJE8x8.fE-tgX.medjDCAL8x8',
		#'tgXDJE8x8.fE-tgX.medjECAL8x8'

		'tgX.maxjEJE-tgX.medjDCAL8x8*4',
		'tgX.maxjEJE8x8-tgX.medjDCAL8x8',
		'tgX.maxjDJE8x8-tgX.medjECAL8x8'

		#'tgXEGA.fE-tgX.medgDCAL',
		#'tgXDGA.fE-tgX.medgECAL'		
	]

	dvarsy = [
		'tgX.medjDCAL8x8*4',
		'tgX.medjDCAL8x8',
		'tgX.medjECAL8x8'
		#'tgX.medgDCAL',
		#'tgX.medgECAL'		
	]
	vary = [v.replace('X',X) for v in dvarsy]

	lfiles = ut.find_files('./hardQCD/mtune1.2', 'tree-*.root')

	hlt = dlist.dlist('main_centrality_patch_{}'.format(X))
	print '[i] main_centrality_patch'
	for i,var in enumerate([v.replace('X',X) for v in dvars]):
		print '    main_centrality_patch:',var
		hl = dlist.dlist(tu.make_unique_name('hl2d',var))
		for ifile,fn in enumerate(lfiles):
			tu.getTempCanvas().cd()
			print '     ', fn
			htitle = '{};{};{}'.format(ut.to_file_name(var), var, vary[i])
			var2d = '{}:{}'.format(vary[i], var)
			h = tu.draw_h2d_from_ntuple(fname=fn, ntname='t', var=var2d, cuts='(xsec)', 
        			                	 xbwidth=0.5, xlow=-30, xhigh=100, 
    	        		    	         ybwidth=0.5, ylow=  0, yhigh= 50,                          
        	        		    	     title=htitle, modname='f{}'.format(ifile), nev=-1)
			hl.add(h)
		hs = hl.sum()
		htitle = '{};{};{}'.format(ut.to_file_name(var), var, vary[i])
		hlt.add(hs.obj, htitle, 'colz')

	hltc = dlist.dlist('main_centrality_patch_cent_{}'.format(X))
	for i,var in enumerate([v.replace('X',X) for v in dvars]):
		print '    main_centrality_patch cent:',var
		hlc = dlist.dlist(tu.make_unique_name('hl2dc',var))
		for ifile,fn in enumerate(lfiles):
			tu.getTempCanvas().cd()
			print '     ', fn
			# with centrality
			htitle = '{};{};{}'.format(ut.to_file_name(var), var, 'centrality')
			var2d = '{}:{}'.format('hd.cent', var)
			hc = tu.draw_h2d_from_ntuple(fname=fn, ntname='t', var=var2d, cuts='(xsec)', 
        			                	 xbwidth=0.5, xlow=-30, xhigh=100, 
    	        		    	         ybwidth=1.0, ylow=  0, yhigh=100,                          
        	        		    	     title=htitle, modname='fc{}'.format(ifile), nev=-1)
			hlc.add(hc)
		hsc = hlc.sum()
		htitle = '{};{};{}'.format(ut.to_file_name(var), var, 'centrality')
		hltc.add(hsc.obj, htitle, 'colz')

	tu.gList.append(hlt)

	for h in hlt.l:
		tc = du.canvas(h.obj.GetName(), h.obj.GetTitle())
		h.obj.Draw('colz')
		ROOT.gPad.SetLogz()
		tc.resize_window(600,600)
		tu.gList.append(tc)
		tc.pdf()

	tu.gList.append(hltc)

	for h in hltc.l:
		tc = du.canvas(h.obj.GetName(), h.obj.GetTitle())
		h.obj.Draw('colz')
		ROOT.gPad.SetLogz()
		tc.resize_window(600,600)
		tu.gList.append(tc)
		tc.pdf()

	hlt.write_to_file(name_mod='modn:')
	hltc.write_to_file(name_mod='modn:')

def main_overlap(X = ''):
	dvars = [
		'tgXEJE.fE-tgX.medjDCAL8x8*4',
		'tgXEJE8x8.fE-tgX.medjDCAL8x8',
		'tgXDJE8x8.fE-tgX.medjECAL8x8',
		'tgXEGA.fE-tgX.medgDCAL',
		'tgXDGA.fE-tgX.medgECAL'		
	]

	pass

if __name__ == '__main__':
	tu.setup_basic_root()
	variants = ['', '1', '2', '3']
	cent=''
	if '--cent' in sys.argv:
		cent = 'hd.cent>0 && hd.cent<10'
	if '--periph' in sys.argv:
		cent = 'hd.cent>60 && hd.cent<80'
	if '--semi-cent' in sys.argv:
		cent = 'hd.cent>20 && hd.cent<40'
	for v in variants:
		if '--patches' in sys.argv:
			main_patches(v, cent=cent)
		if '--rejections' in sys.argv:
			main_rejections(v, cent=cent)
		if '--2d' in sys.argv:
			main_centrality_patch(v)

	if '--bias-make' in sys.argv:
		zerothr=[0,0,0,0,0]
		main_bias(X='', 	cent='', 	thr=zerothr )
		#main_bias(X='1', 	cent='', 	thr=zerothr )
		#main_bias(X='2', 	cent='', 	thr=zerothr )
		#main_bias(X='3', 	cent='', 	thr=zerothr )

		main_bias(X='', 	cent='', 	thr=[15,  8, 9, 4, 4] )
		main_bias(X='1', 	cent='', 	thr=[18,  9, 8, 4, 4] )
		main_bias(X='2', 	cent='', 	thr=[20, 10, 7, 4, 4] )
		main_bias(X='3', 	cent='', 	thr=[25, 11, 6, 4, 4] )

	if '--bias' in sys.argv:
		show_bias(X='', 	cent='', 	thr=[15,  8, 9, 4, 4], det='EMC')
		show_bias(X='1', 	cent='', 	thr=[18,  9, 8, 4, 4], det='EMC')
		show_bias(X='2', 	cent='', 	thr=[20, 10, 7, 4, 4], det='EMC')
		show_bias(X='3', 	cent='', 	thr=[25, 11, 6, 4, 4], det='EMC')

		show_bias(X='', 	cent='', 	thr=[15,  8, 9, 4, 4], det='DMC')
		show_bias(X='1', 	cent='', 	thr=[18,  9, 8, 4, 4], det='DMC')
		show_bias(X='2', 	cent='', 	thr=[20, 10, 7, 4, 4], det='DMC')
		show_bias(X='3', 	cent='', 	thr=[25, 11, 6, 4, 4], det='DMC')

	if not ut.is_arg_set('-b'):
		IPython.embed()	

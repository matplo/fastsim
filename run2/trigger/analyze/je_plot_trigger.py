import dlist
from trigutils import *
import ROOT
import draw_ntuple

def plot_patches_je(fname, usercut='(1)'):
	var = 'JE'
	bwidth = 1
	xlow   = -30
	xhigh  = 100	
	cuts = '(xsec)*({})'.format(usercut)	
	refcuts = '({})'.format(usercut)	
	hlname = 'plot patches JE {}'.format(var)
	hl = dlist.dlist(to_file_name(hlname))
	for tn in ['tnEJE', 'tnDJE', 'tnEJE8x8', 'tnDJE8x8' ]:
		tu.getTempCanvas().cd()
		print '[i] plot_patches_je',tn,var,cuts
		#h = tu.draw_h1d_from_ntuple(fname, tn, var, cuts, bwidth, xlow, xhigh)
		hls = draw_ntuple.h1d_from_ntuple_dir_filter(fname, tn, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=10000, thr = 10)
		hl.add(hls[0].obj, tn, 'p')
	for var in ['maxEJE', 'maxDJE', 'maxEJE8x8', 'maxDJE8x8']:
		tu.getTempCanvas().cd()
		print '[i] plot_patches_je:',tn,var,cuts
		#h = draw_ntuple.draw_h1d_from_ntuple(fname, 'tn', var, cuts, bwidth, xlow, xhigh)
		hls = draw_ntuple.h1d_from_ntuple_dir_filter(fname, 'tn', var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=10000, thr = 10)
		hl.add(hls[0].obj, var, 'hist l')		
	hl.make_canvas(600,600)
	hl.draw(logy=True)
	hl.self_legend()
	hl.update(logy=True)
	tu.gList.append(hl)
	return hl

#tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title=None, modname=''):
def plot_trigger_je(fname, which='EJE', opt='16x16', usercut='(1)'):
	tname = 'tnEJE'
	if which=='DJE':
		tname = 'tnDJE'
	var = 'JE - medXJE8x8 * 4.'
	if opt=='8x8':
		tname = tname + '8x8'
		var   = 'JE - medXJE8x8'
	cuts = '(xsec)*({})'.format(usercut)
	refcuts = '({})'.format(usercut)
	bwidth = 1
	xlow   = -50
	xhigh  = 200
	tu.getTempCanvas().cd()
	#h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	# nev should be -1
	hls = draw_ntuple.h1d_from_ntuple_dir_filter(fname, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=200000, thr=10)
	h = hls[0].obj
	hlname = 'plot trigger {} {} {}'.format(tname, var, opt)
	if usercut!='(1)':
		hlname = 'plot trigger {} {} {} | {}'.format(tname, var, opt, usercut)		
	print '[i] ', hlname
	hl = dlist.dlist(to_file_name(hlname))
	if usercut != '(1)':
		hl.add(h, '{} {} | {}'.format(which, opt, usercut), 'p')
	else:
		hl.add(h, '{} {}'.format(which, opt), 'p')		
	hl.make_canvas(600,600)
	hl.draw(logy=True)
	hl.self_legend()
	hl.update(logy=True)
	tu.gList.append(hl)
	return hl

def plot_trigger_max_je(fname, which='EJE', opt='16x16', usercut='(1)'):
	tname = 'tn'
	if which=='EJE':
		var = 'maxEJENxN - medDJE8x8 * AreaF'
	else:
		var = 'maxDJENxN - medEJE8x8 * AreaF'
	if opt=='16x16':
		var = var.replace('NxN', '').replace(' * AreaF', ' * {:1.1f}'.format(4.))
	else:
		var = var.replace('NxN', '8x8').replace(' * AreaF', '')

	cuts = '(xsec)*({})'.format(usercut)
	refcuts = '({})'.format(usercut)
	bwidth = 1
	xlow   = -50
	xhigh  = 200
	tu.getTempCanvas().cd()
	#h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	hls = draw_ntuple.h1d_from_ntuple_dir_filter(fname, tname, var, cuts, bwidth, xlow, xhigh, refcuts=refcuts, nev=-1, thr=10)
	h = hls[0].obj
	hlname = 'plot trigger max {} {} [{}]'.format(tname, var, opt)
	if usercut!='(1)':
		hlname = 'plot trigger {} {} {} | {}'.format(tname, var, opt, usercut)		
	print '[i] ', hlname
	hl = dlist.dlist(to_file_name(hlname))
	if usercut!='(1)':
		hl.add(h, 'max {} {} | {}'.format(which, opt, usercut), 'p')
	else:
		hl.add(h, 'max {} {}'.format(which, opt), 'p')		
	hl.make_canvas(600,600)
	hl.draw(logy=True)
	hl.self_legend()
	hl.update(logy=True)
	tu.gList.append(hl)
	return hl

def plot_rejections_je(fname, usercut='(1)', withmax=True):

	hlname = 'JEtriggers'
	if usercut!='(1)':
		hlname = '{} | {}'.format(hlname, usercut)

	hlall = dlist.dlist(to_file_name(hlname))

	hl1 = plot_trigger_je(fname, which='EJE', opt='16x16', usercut=usercut)
	hl2 = plot_trigger_je(fname, which='EJE', opt='8x8', 	usercut=usercut)
	hl3 = plot_trigger_je(fname, which='DJE', opt='16x16', usercut=usercut)
	hl4 = plot_trigger_je(fname, which='DJE', opt='8x8', 	usercut=usercut)
	hlall.add_list(hl1)
	hlall.add_list(hl2)
	hlall.add_list(hl3)
	hlall.add_list(hl4)

	if withmax:
		hl1 = plot_trigger_max_je(fname, which='EJE', opt='16x16',	usercut=usercut)
		hl2 = plot_trigger_max_je(fname, which='EJE', opt='8x8',	usercut=usercut)
		hl3 = plot_trigger_max_je(fname, which='DJE', opt='16x16',	usercut=usercut)
		hl4 = plot_trigger_max_je(fname, which='DJE', opt='8x8',	usercut=usercut)
		hlall.add_list(hl1)
		hlall.add_list(hl2)
		hlall.add_list(hl3)
		hlall.add_list(hl4)

	hlall.make_canvas(600,600)
	hlall.draw(logy=True)
	hlall.self_legend()
	hlall.update(logy=True)
	tu.gList.append(hlall)

	hly = dlist.fractional_yats(hlall)
	rejection_table(hly, 1.0e-3)
	rejection_table(hly, 2.5e-3)
	hly.make_canvas(600,600)
	hly.draw(logy=True, miny=1e-9, maxy=1e1)
	hly.self_legend()
	ROOT.gPad.SetGridx()
	ROOT.gPad.SetGridy()	
	hly.update(logy=True)

	tu.gList.append(hly)

import dlist
from trigutils import *
import ROOT

def plot_patches_ga(fname, usercut='(1)'):
	var = 'GA'
	bwidth = 1
	xlow   = -30
	xhigh  = 100	
	cuts = '(xsec)*({})'.format(usercut)
	hlname = 'plot patches GA {}'.format(var)
	hl = dlist.dlist(to_file_name(hlname))
	for tn in ['tnEGA', 'tnDGA', 'tnEGA8x8', 'tnDGA8x8' ]:
		tu.getTempCanvas().cd()
		h = tu.draw_h1d_from_ntuple(fname, tn, var, cuts, bwidth, xlow, xhigh)
		hl.add(h, tn, 'p')
	for var in ['maxEGA', 'maxDGA', 'maxEGA8x8', 'maxDGA8x8']:
		tu.getTempCanvas().cd()
		h = tu.draw_h1d_from_ntuple(fname, 'tn', var, cuts, bwidth, xlow, xhigh)
		hl.add(h, var, 'hist l')		
	hl.make_canvas(600,600)
	hl.draw(logy=True)
	hl.self_legend()
	hl.update(logy=True)
	tu.gList.append(hl)
	return hl

#tu.draw_h1d_from_ntuple(fname, ntname, var, cuts, bwidth, xlow, xhigh, title=None, modname=''):
def plot_trigger_ga(fname, which='EGA', usercut='(1)'):
	tname = 'tnEGA'
	if which=='DGA':
		tname = 'tnDGA'
	var = 'GA - medXGA8x8 / 16.'
	cuts = '(xsec)*({})'.format(usercut)
	bwidth = 1
	xlow   = -50
	xhigh  = 200
	tu.getTempCanvas().cd()
	h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	hlname = 'plot trigger GA {} {}'.format(tname, var)
	if usercut!='(1)':
		hlname = 'plot trigger {} {} | {}'.format(tname, var, usercut)		
	print '[i] ', hlname
	hl = dlist.dlist(to_file_name(hlname))
	if usercut!='(1)':
		hl.add(h, '{} {} | {}'.format(which, usercut), 'p')
	else:
		hl.add(h, '{}'.format(which), 'p')		
	hl.make_canvas(600,600)
	hl.draw(logy=True)
	hl.self_legend()
	hl.update(logy=True)
	tu.gList.append(hl)
	return hl

def plot_trigger_max_ga(fname, which='EGA', usercut='(1)'):
	tname = 'tn'
	if which=='EGA':
		var = 'maxEGA - medDJE8x8 / 16'
	else:
		var = 'maxDGA - medEJE8x8 / 16'
	cuts = '(xsec)*({})'.format(usercut)
	bwidth = 1
	xlow   = -50
	xhigh  = 200
	tu.getTempCanvas().cd()
	h = tu.draw_h1d_from_ntuple(fname, tname, var, cuts, bwidth, xlow, xhigh)
	hlname = 'plot trigger max GA {} {}'.format(tname, var)
	if usercut!='(1)':
		hlname = 'plot trigger max GA {} {} | {}'.format(tname, var, usercut)		
	print '[i] ', hlname
	hl = dlist.dlist(to_file_name(hlname))
	if usercut!='(1)':
		hl.add(h, 'max {} | {}'.format(which, usercut), 'p')
	else:
		hl.add(h, 'max {}'.format(which), 'p')		
	hl.make_canvas(600,600)
	hl.reset_axis_titles(var)
	hl.draw(logy=True)
	hl.self_legend()
	hl.update(logy=True)
	tu.gList.append(hl)
	return hl

def plot_rejections_ga(fname, usercut='(1)', withmax=True):

	hlname = 'GAtriggers'
	if usercut!='(1)':
		hlname = '{} | {}'.format(hlname, usercut)

	hlall = dlist.dlist(to_file_name(hlname))

	#hl1 = plot_trigger_ga(fname, which='EGA', opt='16x16', usercut=usercut)
	#hl2 = plot_trigger_ga(fname, which='EGA', opt='8x8', 	usercut=usercut)
	#hl3 = plot_trigger_ga(fname, which='DGA', opt='16x16', usercut=usercut)
	#hl4 = plot_trigger_ga(fname, which='DGA', opt='8x8', 	usercut=usercut)
	#hlall.add_list(hl1)
	#hlall.add_list(hl2)
	#hlall.add_list(hl3)
	#hlall.add_list(hl4)

	if withmax:
		hl1 = plot_trigger_max_ga(fname, which='EGA',	usercut=usercut)
		#hl2 = plot_trigger_max_ga(fname, which='DGA',	usercut=usercut)
		hlall.add_list(hl1)
		#hlall.add_list(hl2)

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
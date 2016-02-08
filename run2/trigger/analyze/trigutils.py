import tutils as tu
import math
import dlist 

def EMCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 110. / 360. * math.pi * 2.
	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)
	print '[i] using EMCalKeepOutFactor with R=', R, retval
	return retval

def EMCalUpScaleAtlas(R=0.4):
	dphi  = 360. / 110.
	dyrap = 2./1.4 
	return 1./EMCalKeepOutFactor(R) * dphi

def DCalKeepOutFactor(R=0.4):
	deta = 0.7 * 2.
	dphi = 80. / 360. * math.pi * 2. #not 70 deg?
	deta_r = deta - 2. * R 
	dphi_r = dphi - 2. * R
	retval =  deta_r * dphi_r / (deta * dphi)
	print '[i] using DCalKeepOutFactor with R=', R, retval
	return retval

def EDscaleA():
	emc = 0.7 * 2. * 110. / 360. * math.pi * 2.
	dmc = 0.7 * 2. * 80. / 360. * math.pi * 2. * 0.66
	print dmc/emc

def to_file_name(s):
	return "".join([x if x.isalnum() else "_" for x in s])

def rejection_table(hl, rej = 1.e-3):
	print '[i] rejections for', hl.name, 'rej:',rej
	retvals = []
	for o in hl.l:
		h = o.obj
		for ib in range(1, h.GetNbinsX()):
			if h.GetBinContent(ib) <= rej:
				print '    ', h.GetTitle(), h.GetBinLowEdge(ib), h.GetBinContent(ib)
				newtitle = '{} [{:.1e}@{:.1f}]'.format(h.GetTitle(), rej, h.GetBinLowEdge(ib))
				h.SetTitle(newtitle)
				retvals.append(h.GetBinLowEdge(ib))
				break
	return retvals

def get_nev(fname):
	h = tu.get_object_from_file('hNev', fname)
	return h.GetBinContent(1)

def divide_lists(hl0, hl1):
	hlr = dlist.dlist('ratio')
	for i in range(len(hl0.l)):
		o0 = hl0[i]
		o1 = hl1[i]		
		hlrtmp = dlist.make_ratio(o0.obj, o1.obj)
		hlr.add_list(hlrtmp)
	return hlr

def emcal_eta_phi_cut(R=0):
	return '(({bname}.Eta() > -0.668305 + {R}) && ({bname}.Eta() < 0.668305 - {R}) && ({bname}.Phi() > 1.40413 - {pi} + {R}) && ({bname}.Phi() < 3.26149 - {pi} - {R}))'.format(bname='{bname}', pi=math.pi, R=R)

def dcal_eta_phi_cut(R=0):
	return '(({bname}.Eta() > -0.668305 + {R}) && ({bname}.Eta() < 0.668305 - {R}) && ({bname}.Phi() > 4.54573 - {pi} + {R}) && ({bname}.Phi() < 5.70495 - {pi} - {R} ))'.format(bname='{bname}', pi=math.pi, R=R)

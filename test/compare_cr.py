#!/usr/bin/env python

import sys
import tutils
import ROOT as r
import IPython
import draw_ntuple as dn
import dlist

def compare_cr(fname1, fname2, var='jcut.Pt()', bwidth = 5.):

	ntname = 't'
	cuts   = '(1.) * (header.xsec)'

	print '[i]',var

	tutils.getTempCanvas().cd()
	h1 = dn.h1d_from_ntuple(fname1, ntname, var, cuts, bwidth=bwidth, xlow=0, xhigh=bwidth * 50.)
	tutils.getTempCanvas().cd()
	h2 = dn.h1d_from_ntuple(fname2, ntname, var, cuts, bwidth=bwidth, xlow=0, xhigh=bwidth * 50.)

	hl = dlist.dlist('compare_cr_{}'.format(var))
	hl.add(h1, fname1, 'p')
	hl.add(h2, fname2, 'p')
	tc = hl.make_canvas()
	tc.Divide(2,1)
	tc.cd(1)
	hl.draw(logy=True)
	hl.self_legend()
	hl.draw_comment(var)
	r.gPad.SetLogy()
	r.gPad.Update()    

	dopt   = 'l'
	ptzoom = 100
	hlr = hl.ratio_to(opt=dopt)
	tc.cd(2)
	hlr.zoom_axis(0, 0, ptzoom)
	hlr.draw(logy=False, miny=0, maxy=2)    
	hlr.self_legend()

	r.gPad.SetGridy()
	r.gPad.Update()    

	tutils.gList.append(hl)
	tutils.gList.append(hlr)

	hl.write_to_file()
	hlr.write_to_file()

if __name__ == '__main__':
	tutils.setup_basic_root()

	#compare_cr('tree-NOcr.root', 'tree-cr.root')
	compare_cr('tree-NOcr.root', 'tree-cr.root', 'partonf.Pt()', bwidth = 1.)
	compare_cr('tree-NOcr.root', 'tree-cr.root', 'pfinal.Pt()', bwidth = 0.1)	

	tutils.iprompt()

def compare_pt(fname1, fname2, ntname1='jets_hard_EMC', ntname2='jets_hard_EMC'):
	#draw_h1d_from_ntuple(fname, nntname, var, cuts, bwidth, xlow, xhigh, title=None, modname='')
	var    = "pT"
	cuts   = "(abs(eta)<1 && nEv==-1)*(xsec)"
	bwidth = 10
	xlow   = 0
	xhigh  = 150

	hlname = '-'.join([fname1, ntname1, fname2, ntname2, var, cuts])
	hl = dlist.dlist(hlname)

	title  = '-'.join([fname1, ntname1, var, cuts])
	h1 	   = tu.draw_h1d_from_ntuple(fname1, ntname1, var, cuts, bwidth, xlow, xhigh, title)
	hl.add(h1, title, 'p')
	title  = '-'.join([fname2, ntname2, var, cuts])
	h2     = tu.draw_h1d_from_ntuple(fname2, ntname2, var, cuts, bwidth, xlow, xhigh, title)
	hl.add(h2, title, 'p')

	hl.make_canvas()
	hl.draw()

	tu.gList.append(hl)

	return hl

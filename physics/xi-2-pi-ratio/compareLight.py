#!/usr/bin/env ipython

import ROOT
import dlist
import tutils as tu

names = [
    [ 0, "MeanPt_ResultsforPionSum_stat",	"pi", "pp",   1],
    [ 1, "MeanPt_ResultsforPionSum_sys", 	"pi", "pp",   1],
    [ 2, "MeanPt_ResultsforPionSum_sys", 	"pi", "pp",   1],

    [ 3, "MeanPt_ResultsforKaonSum_stat",	"K",  "pp"  , 2],
    [ 4, "MeanPt_ResultsforKaonSum_sys", 	"K",  "pp"  , 2],
    [ 5, "MeanPt_ResultsforKaonSum_sys", 	"K",  "pp"  , 2],

    [ 6, "MeanPt_ResultsforProtonSum_stat",	"p",  "pp"  , 9],
    [ 7, "MeanPt_ResultsforProtonSum_sys", 	"p",  "pp"  , 9],
    [ 8, "MeanPt_ResultsforProtonSum_sys", 	"p",  "pp"  , 9],

    [ 9, "HepData/8420/d20x1y1",			"K",  "pPb" , 2],
    [10, "HepData/8420/d21x1y1",			"pi", "pPb",  1],
    [11, "HepData/8420/d18x1y1",			"p",  "pPb" , 9],
    [12, "HepData8463d32x1y1",				"pi", "PbPb", 1],
    [13, "HepData8463d32x1y3",				"K",  "PbPb", 2],
    [14, "HepData8463d32x1y5",				"p",  "PbPb", 9]
	]

def shift_graph(gr, system='pp'):
	spp   = [	1. 	, 	1.,		1.,		1.,		1.,		1.,		1.,		1.,		1.,		1.,		1.] 
	spPb  = [	1.15, 	1.3,  	1.4,  	1.6,  	1.65,  	1.7,  	1.8]
	sPbPb = [	7., 	13., 	21., 	28., 	35.] # this was for Xi/pi
	s     = spp
	if system=='pPb':
		s = spPb
	if system=='PbPb':
		s = spp
	npoints = gr.GetN()
	print gr.GetName(), npoints, len(s)
	for i in range(0, npoints):
		xgr = gr.GetX()[i]
		if i < len(s):
			sf = s[i]
		else:
			sf = 1.
		print gr.GetX()[i]
		gr.GetX()[i] = xgr / 2.
		print gr.GetX()[i]

def main():
	hlin = dlist.load_file('MeanPtV0MMult.root')
	print hlin
	hl = dlist.make_list('hl', 1, 3e3)
	for i,gr in enumerate(hlin.l):
		if '_sys' in names[i][1]:
			continue
		if i > 2:
			break
		hl.add(gr.obj, '{} {}'.format(names[i][2], names[i][3]), 'p +k{} +m120'.format(names[i][4]))
		shift_graph(gr.obj, names[i][3])
		#hl.add(gr.obj, '{} {} S-scaled'.format(names[i][2], names[i][3]), 'l hist noleg')
		hl.add(gr.obj, '{} {} S-scaled'.format(names[i][2], names[i][3]), 'l hist noleg')
	hl.make_canvas()
	hl.reset_axis_titles('dn/d#eta', '<p_{T}> (GeV/c)')
	hl.draw()
	hl.self_legend(1, '', 0.2)
	ROOT.gPad.SetLogx()
	hl.update()
	tu.gList.append(hl)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	tu.wait_i()
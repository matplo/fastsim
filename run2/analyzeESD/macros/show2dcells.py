#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import draw_utils as du
import dlist
import ROOT
import os
import IPython
import math
import sys

def main(fname = './Hist.root', which='0'):
	hl0 = dlist.dlist('2d_cells{}'.format(which))
	hname = 'histos/fCells{}'.format(which)
	htitle = 'iteration{}'.format(which)
	dopt = 'colz'

	hl0.add_from_file(hname, fname, htitle, dopt)

	hl0.make_canvas(600, 600)
	hl0.draw()
	hl0.adjust_maxima(1e4, 3e6)
	ROOT.gPad.SetLogz()
	hl0.update()
	tu.gList.append(hl0)
	hl0.pdf()
	hl0.png()
	return hl0

if __name__ == '__main__':
	tu.setup_basic_root()
	main('./Hist.root', '0')
	main('./Hist.root', '')	
	if not ut.is_arg_set('-b'):
		IPython.embed()	

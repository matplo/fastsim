#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math
import sys
import numpy
import png
import itertools

def main(fname):
	r=png.Reader(filename=fname)
	#img=r.read()
	#print img
	#pngdata=r.asFloat(1.0)
	pngdata=r.asDirect()
	image_2d = numpy.vstack(itertools.imap(numpy.uint8, pngdata))
	print image_2d
	##pixels = ft[2]
	##for px in pixels:
	##	print px

if __name__ == '__main__':
	tu.setup_basic_root()
	fname = 'Screen Shot 2015-11-11 at 21.25.59_DCAL.png'
	main(fname)
	if not ut.is_arg_set('-b'):
		IPython.embed()

#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import IPython

import numpy as np
from PIL import Image

#http://stackoverflow.com/questions/15612373/convert-image-png-to-matrix-and-then-to-1d-array

def main(fname):
	img = Image.open(fname).convert('RGBA')

	arr = np.array(img)

	for index, x in np.ndenumerate(arr):
		#print index, x
		ridx = (index[0], index[1], 0)
		gidx = (index[0], index[1], 1)
		bidx = (index[0], index[1], 2)
		if arr[gidx] != 255:
			for col in range(4):
				idx = (index[0], index[1], col)
				arr[idx] = 0

	# make a PIL image
	img2 = Image.fromarray(arr, 'RGBA')

	img.show()
	img2.show()

	img2.save(fname.replace('.png', '_mask.png'), 'PNG')

if __name__ == '__main__':
	tu.setup_basic_root()
	fname = 'Screen Shot 2015-11-11 at 21.25.59_DCAL.png'
	main(fname)
	if not ut.is_arg_set('-b'):
		IPython.embed()

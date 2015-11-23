#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import IPython

import numpy as np
from PIL import Image

#http://stackoverflow.com/questions/15612373/convert-image-png-to-matrix-and-then-to-1d-array

#From TriggerMappingEmcalSimple.cxx

# * Phi Limits:
# * EMCAL
# * Sector 0: min(1.40413), max(1.73746), dist(0.333328)
# * Sector 1: min(1.7532),  max(2.08653), dist(0.333328)
# * Sector 2: min(2.10226), max(2.43559), dist(0.333328)
# * Sector 3: min(2.45133), max(2.78466), dist(0.333328)
# * Sector 4: min(2.8004),  max(3.13372), dist(0.333328)
# * Sector 5: min(3.14946), max(3.26149), dist(0.112032)
# *
# * DCAL + PHOS
# * Sector 0: min(4.54573), max(4.87905), dist(0.333328)
# * Sector 1: min(4.89479), max(5.22812), dist(0.333328)
# * Sector 2: min(5.24386), max(5.57718), dist(0.333328)
# * Sector 3: min(5.59292), max(5.70495), dist(0.112032)
#	fEtaMin(-0.668305),
#	fEtaMax(0.668305),

def main(fname, det='EMC'):
	print '[i] make_maps:',fname, det
	img = Image.open(fname).convert('RGBA')

	arr = np.array(img)

	for index, x in np.ndenumerate(arr):
		#print index, x
		ridx = (index[0], index[1], 0)
		gidx = (index[0], index[1], 1)
		bidx = (index[0], index[1], 2)
		if arr[gidx] == 255 or arr[gidx] == 214:
			setcol = 0
		else:
			setcol = 255
			#if arr[gidx] > 0:
			#	print index, x
		for col in range(4):
			idx = (index[0], index[1], col)
			arr[idx] = setcol

	if det=='EMC':
		phidet = 1.40413
	else:
		phidet = 4.54573
	etadet = -0.668305

	for index, x in np.ndenumerate(arr):
		phi = index[1] + phidet
		eta = index[0] + etadet

	# make a PIL image
	img2 = Image.fromarray(arr, 'RGBA')

	img.show()
	img2.show()

	img2.save(fname.replace('.png', '_mask.png'), 'PNG')

if __name__ == '__main__':
	tu.setup_basic_root()
	fnames = [	#'dcal.png',
				'dcalphos.png'#,
				#'dcalphos_holes.png',
				#'emcal.png' 
				]
	for i, fname in enumerate(fnames):
		if i < 3:
			det = 'DMC'
		else:
			det = 'DMC'
		main(fname, det)
	if not ut.is_arg_set('-b'):
		IPython.embed()

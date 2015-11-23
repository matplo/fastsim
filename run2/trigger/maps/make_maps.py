#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import IPython
import sys

import numpy as np
from PIL import Image

#http://stackoverflow.com/questions/15612373/convert-image-png-to-matrix-and-then-to-1d-array

#From TriggerMappingEmcalSimple.cxx

# * Phi Limits:
# * EMCAL
# * Sector 0: min(1.40413), max(1.73746), dist(0.333328) 12 in phi
# * Sector 1: min(1.7532),  max(2.08653), dist(0.333328) 12 in phi
# * Sector 2: min(2.10226), max(2.43559), dist(0.333328) 12 in phi
# * Sector 3: min(2.45133), max(2.78466), dist(0.333328) 12 in phi
# * Sector 4: min(2.8004),  max(3.13372), dist(0.333328) 12 in phi
# * Sector 5: min(3.14946), max(3.26149), dist(0.112032)  4 in phi
# *
# * DCAL + PHOS
# * Sector 0: min(4.54573), max(4.87905), dist(0.333328) 12 in phi
# * Sector 1: min(4.89479), max(5.22812), dist(0.333328) 12 in phi
# * Sector 2: min(5.24386), max(5.57718), dist(0.333328) 12 in phi
# * Sector 3: min(5.59292), max(5.70495), dist(0.112032)  4 in phi
#	fEtaMin(-0.668305), 48 in eta
#	fEtaMax(0.668305),  48 in eta

class Square(object):
	def __init__(self, x, y):
		self.xy = []
		self.xy.append([x,y])
		print '[i] new square:', self.__repr__()

	def addPixel(self, x, y):
		#if self.isInside(x, y):
		#	return True

		if self.isNeighbour(x,y):
			self.xy.append([x,y])
			return True

		return False

	def isNeighbour(self, x, y):
		for p in self.xy:
			#print p[0], p[1], abs(p[0]-x), abs(p[1]-y)
			if (abs(p[0]-x) <= 1) and (abs(p[1]-y) <= 1):
				return True
		return False

	def isInside(self, x, y):
		for p in self.xy:
			if p[0] == x and p[1] == y:
				return True
		return False

	def box(self):
		xmin = 1e6
		ymin = 1e6
		xmax = 0
		ymax = 0
		for xy in self.xy:
			if xy[0] < xmin:
				xmin = xy[0]
			if xy[1] < ymin:
				ymin = xy[1]

			if xy[0] > xmax:
				xmax = xy[0]
			if xy[1] > ymax:
				ymax = xy[1]

		return [xmin, xmax, ymin, ymax]

	def __repr__(self):
		return ':'.join([str(x) for x in self.box()])

class Squares(object):
	def __init__(self):
		self.l = []

	def addPixel(self, x, y):
		if self.addToSquare(x,y) == False:
			sq = Square(x, y)
			self.l.append(sq)

	def addToSquare(self, x, y):
		for sq in self.l:
			if sq.addPixel(x, y) == True:
				return True
		return False

	def dump(self):
		for i, sq in enumerate(self.l):
			print '[i] suqare:',i,'is',sq

def make_map(fname, det='EMC'):
	print '[i] make_maps:',fname, det

	rfoutname = fname.replace('.png', '_mask.root')
	#rfout = TFile.Open(rfoutname, 'recreate')
	#hout = TH2F(hname, hname, 200)

	img = Image.open(fname).convert('RGBA')
	arr = np.array(img)
	for index, x in np.ndenumerate(arr):
		#print index, x
		ridx = (index[0], index[1], 0)
		gidx = (index[0], index[1], 1)
		bidx = (index[0], index[1], 2)
		if arr[gidx] == 255 or arr[gidx] == 247:
			setcol = 0
		else:
			setcol = 1
			#if arr[gidx] > 0:
			#	print index, x
		for col in range(4):
			idx = (index[0], index[1], col)
			arr[idx] = setcol * 255

	squares = Squares()
	for index, x, in np.ndenumerate(arr):
		if x == 0:
			squares.addPixel(index[0], index[1])

	for index, x in np.ndenumerate(arr):
		if squares.l[0].isInside(index[0], index[1]):
			arr[(index[0], index[1], 2)] = 255
			arr[(index[0], index[1], 3)] = 255

	squares.dump()

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

def dump(fname):
	print '[i] dump:',fname
	img = Image.open(fname).convert('RGBA')

	arr = np.array(img)

	tags = []

	for index, x in np.ndenumerate(arr):
		#print index, x
		ridx = (index[0], index[1], 0)
		gidx = (index[0], index[1], 1)
		bidx = (index[0], index[1], 2)
		aidx = (index[0], index[1], 3)
		tag  = ':'.join(str(x) for x in [index[0], index[1]])
		if tag in tags:
			pass
		else:
			tags.append(tag)
			print tag, arr[ridx], arr[gidx], arr[bidx], arr[aidx]

def main():
	fname = ut.get_arg_with('-f')
	if fname==None:
		fname='emcal.png'
	if '--dump' in sys.argv:
		dump(fname)
		return
	det = ut.get_arg_with('-d')
	if det==None:
		if 'dcal' in fname:
			det = 'DMC'
		else:
			det = 'EMC'
	make_map(fname, det)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

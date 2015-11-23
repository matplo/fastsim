#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import IPython
import sys

import numpy as np
from PIL import Image

import ROOT
import math

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

def make_map(fname, det='EMC'):
	print '[i] make_maps:',fname, det

	rfoutname = fname.replace('.png', '_mask.root')
	rfout = ROOT.TFile.Open(rfoutname, 'recreate')
	etadet = 0.668305
	hname = '{}_{}'.format(fname.replace('.png', ''), det)
	hout = ROOT.TH2I(hname, hname+';eta;phi', 200, -0.7, 0.7, 450, 0, math.pi * 2.)

	img = Image.open(fname).convert('RGBA')
	arr = np.array(img)

	print arr.shape

	if det == 'EMC':
		phifactor = (3.26149 - 1.40413) / arr.shape[0]
		etafactor = (etadet*2.) / arr.shape[1]
		phidet = 3.26149
	else:
		phifactor = (5.70495 - 4.54573) / arr.shape[0]
		etafactor = (etadet*2.) / arr.shape[1]
		phidet = 5.70495
	print phifactor, etafactor

	for index, x in np.ndenumerate(arr):
		#print index, x
		ridx = (index[0], index[1], 0)
		gidx = (index[0], index[1], 1)
		bidx = (index[0], index[1], 2)

		rgb   = (arr[ridx], arr[gidx], arr[bidx])
		grey  = (214, 211, 206)
		green = (0, 255, 0)
		black = (0, 0, 0)
		white = (255,255,255)
		red   = (255, 0, 0) 
		red1 = (255, 13, 28)
		red2 = (252, 42, 28)
		if rgb == red or rgb == red1 or rgb == red2:
			for col in range(4):
				idx = (index[0], index[1], col)
				arr[idx] = 255
			hout.Fill(eta, phi, 1)

		phi = phidet - index[0] * phifactor
		eta = index[1] * etafactor - etadet

		if index[1] % 100 == 0:
			print index,phi,eta,'\r',

		#if index[0] > arr.shape[0]/10.:
		#	break

	img2 = Image.fromarray(arr, 'RGBA')
	img2.save(fname.replace('.png', '_mask.png'), 'PNG')

	rfout.Write()

#	for ixb in range(1, hout.GetNbinsX() + 1):
#		for iyb in range(1, hout.GetNbinsY() + 1):
#			pass #print ixb, iyb

def main():
	fname = ut.get_arg_with('-f')
	if fname==None:
		fname='emcal.png'
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

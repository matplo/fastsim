#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import dlist
import ROOT
import os
import IPython
import math
import sys

import centrality
import hnutil
import tutils as tu

def n2w(s, w=True):
	if w==True:
		s = s[:-1] + 'w'
	else:
		s = s[:-1] + 'n'
	return s

def E2D(s, which='EMC'):
	idx = len(s) - 2
	if which=='EMC':
		s = 'hE' + s[-idx:]
	else:
		s = 'hD' + s[-idx:]
	return s

class Hr2(object):
	def __init__(self, fname, hnamew):
		self.fname  = fname
		self.hnamew = hnamew
		self.hnamen = n2w(hnamew,w=False)
		self.h3dw   = tu.get_object_from_file(self.hnamew, self.fname)
		self.h3dn   = tu.get_object_from_file(self.hnamen, self.fname)
		self.h 		= self.h3dw
		#self.h      = self.h3dw.RebinX(5) #tu.filter_single_entries_3d(self.h3dw, self.h3dn, 10)

	def get_cut_bin_range(self, axis='x', cut = [None, None]):
		ax = self.h.GetXaxis()
		icl = 1
		ich = ax.GetNbins()
		if axis == 'y':
			ax  = self.h.GetYaxis()
			ich = ax.GetNbins()
		if axis == 'z':
			ax  = self.h.GetZaxis()
			ich = ax.GetNbins()
		if cut[0] != None:
			icl = cut[0]
		if cut[1] != None:
			ich = cut[1]
		return [ax.FindBin(icl), ax.FindBin(ich)]

	def get_projection(self, raxis='z', cutx=[None, None], cuty=[None, None], cutz=[None, None]):
		cuts = '-'.join('-'.join(str(s)) for s in [cutx, cuty, cutz])
		newname = '{}-{}-{}'.format(self.h.GetName(), raxis, ut.to_file_name(str(cuts)))
		print newname
		hc = self.h.Clone(newname)
		nxcut = self.get_cut_bin_range(axis='x', cut=cutx)
		nycut = self.get_cut_bin_range(axis='y', cut=cuty)
		nzcut = self.get_cut_bin_range(axis='z', cut=cutz)
		print nxcut, nycut, nzcut
		for ibx in range(1, hc.GetNbinsX()+1):
			for iby in range(1, hc.GetNbinsY()+1):
				for ibz in range(1, hc.GetNbinsZ()+1):
					if ibx >= nxcut[0] and ibx < nxcut[1] and iby >= nycut[0] and ibz < nycut[1] and ibz >= nzcut[0] and ibz < nycut[1]:
						pass
					else:
						hc.SetBinContent(ibx, iby, ibz, 0)
						hc.SetBinError(ibx, iby, ibz, 0)
		return hc.Project3D(raxis)

def main():
	hardQCDfile = '/Users/ploskon/data/2015-10-31/mtune1/hardQCD.root';
	hr2 = Hr2(hardQCDfile, 'hEptcentmedjw')
	hl = dlist.ListStorage('2d')
	hproj = hr2.get_projection('zy')
	hl.add_to_list('none cent cut', hproj, 'yx none', '')
	hproj = hr2.get_projection('zy', cuty=[10,100])
	hl.add_to_list('0-100 cent cut', hproj, 'yx', '')
	hproj = hr2.get_projection('zy', cuty=[0,10])
	hl.add_to_list('10% cent cut', hproj, 'yx', '')
	hproj = hr2.get_projection('x') #, cuty=[0,10])
	hl.add_to_list('10% cent cut x', hproj, 'x', '')
	hl.draw_all()
	hl.set_grid_x()
	hl.set_grid_y()
	hl.set_log_axis('z')

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()

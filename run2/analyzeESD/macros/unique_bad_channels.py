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

def reformat(chlist, fout=None):
	print >> fout, 'Int_t AliAnalysisM::fgBadChannels[] = {'
	for i, ich in enumerate(sorted(chlist)):
		if i % 10 == 0 and i!=0:
			print >> fout
		sich = '{}'.format(ich).rjust(6) #zfill(5)
		if i < len(chlist) - 1:
			print >> fout,sich+',',
	print >> fout, '-1};'

def main(fname, foutname=None):
	with open(fname) as f:
		indata = f.readlines()
	output = []
	doubled = 0
	for l in indata:
		if '#' in l:
			continue
		channels = l.split(',')
		for ch in channels:
			ch = ch.strip().strip('\n')
			if len(ch) < 1:
				continue	
			ich = int(ch)		
			if ich <= 0:
				continue
			if ich in output:
				doubled += 1
			else:
				#print ich
				output.append(ich)
	print '// doubled:',doubled
	fout = sys.stdout
	if foutname != None:
		fout = open(foutname, 'w')
	reformat(output, fout)
	if foutname != None:
		fout.close()

if __name__ == '__main__':
	tu.setup_basic_root()
	fname = ut.get_arg_with('--in')
	if fname==None:
		fname = 'bad_channels.txt'
	foutname = fname.replace('.txt', '_updated.txt')
	main(fname, foutname)
#	if not ut.is_arg_set('-b'):
#		IPython.embed()	

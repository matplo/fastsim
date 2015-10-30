#!/usr/bin/env python

import ROOT
import os

def getFiles(ftxt='hardQCDfiles.txt'):
	files = []
	try:
		with open(ftxt, 'r') as f:
			files = [l.strip() for l in f.read().splitlines(True)]
	except:
		print '[w] unable to read from',ftxt
	return files

def main():
	libs = ['libR2Util', 'libAnalyze']
	sdir = os.getenv('RUN2EMCTRIGGER')
	sdir = os.path.join(sdir, 'lib')
	print sdir
	ROOT.gSystem.AddDynamicPath(sdir)
	for l in libs:
		ROOT.gSystem.Load(l)
	ROOT.gSystem.Load('libAnalyze')

	nev = 10
	infiles = './hardQCDfiles.txt'
	files   = getFiles(infiles)
	for i,fname in enumerate(files):
		if i>0:
			break
		if not os.path.isfile(fname):
			print '[w] file not found:',fname
			continue
		a = ROOT.Analysis()
		foutname = '{}-out-{}.root'.format(os.path.basename(infiles), i)
		a.AnalyzeFile(fname, foutname, nev)
if __name__ == '__main__':
	main()
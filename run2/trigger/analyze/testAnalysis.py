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

def is_out_dir_ok(outdir):
	if not os.path.isdir(outdir):
		os.makedirs(outdir)
	return os.path.isdir(outdir)

def main():
	libs = ['libR2Util', 'libAnalyze']
	sdir = os.getenv('RUN2EMCTRIGGER')
	sdir = os.path.join(sdir, 'lib')
	print sdir
	ROOT.gSystem.AddDynamicPath(sdir)
	for l in libs:
		ROOT.gSystem.Load(l)
	ROOT.gSystem.Load('libAnalyze')

	nev = 100
	infiles = './hardQCDfiles.txt'
	files   = getFiles(infiles)
	outdir  = os.path.basename(infiles).replace('.txt', '.outputs')
	if not is_out_dir_ok(outdir):
		print '[e] unable to access outdir:',outdir
		return

	threads = []
	for i,fname in enumerate(files):
		if not os.path.isfile(fname):
			print '[w] file not found:',fname
			continue
		foutname = '{}/out-{}.root'.format(outdir, i)
		a = ROOT.Analysis()
		a.AnalyzeFile(fname, foutname, nev)

if __name__ == '__main__':
	main()
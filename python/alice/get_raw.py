#!/usr/bin/env python

import pyutils as ut
import string
import os

def getfileN(fname):
	print fname
	nf = fname.split('.')
	print nf
	return nf[0].atoi()

def raw_alien_dir(rnumber):
	rslen = len('000170207')
	if len(rnumber) < rslen:
		rnumber = rnumber.zfill(rslen)
	yearperiod = '2011/LHC11h'
	if string.atoi(rnumber) > 170593:
		yearperiod = '2015/LHC15o'
	return '/alice/data/{}/{}/raw'.format(yearperiod, rnumber)

class RFile(object):
	def __init__(self, fname):
		self.fname = fname #fname.strip().strip('\n')
		try:
			splits       = fname.split('.')
			s0           = splits[0]
			s0           = s0[14-3:]
			s1           = splits[1]
			self.number  = string.atoi(s0) * 1000 + string.atoi(s1)

			splits       = fname.split('.')
			s0           = splits[0]
			self.rnumber = s0[2:14-3]
			self.dir     = raw_alien_dir(self.rnumber)
			self.path    = os.path.join(self.dir, self.fname)
		except:
			self.number  = -1
			self.rnumber = -1
			self.dir     = '[no dir]'
			self.path    = '[no path]'

	def run_number(self):
		return self.rnumber

	def key(self):
		return self.number

	def __repr__(self):
		return self.fname

	def __str__(self):
		return self.fname

def get_lines(l):
	retl = []
	s = ''
	for c in l:
		if c!='\n':
			s = s + c
		else:
			retl.append(s)
			s = ''
	return retl

def list_files(rnumber):
	cmd = 'alien_ls {}'.format(raw_alien_dir(rnumber))
	out,err = ut.call_cmnd(cmd, verbose=True)
	lout = get_lines(out)
	lfiles = []
	for l in lout:
		lfiles.append(RFile(l))
	sout = sorted(lfiles, key=RFile.key)
	print '[i] number of files:',len(sout)
	return sout

def get_files(flist, nmax):
	idone = 0
	for f in flist:
		if f.run_number() < 0:
			continue
		outdir = os.path.join('./', str(f.run_number()))
		if not os.path.isdir(outdir):
			os.makedirs(outdir)
		cmd = 'alien_cp alien://{} {}'.format(f.path, outdir)
		out,err = ut.call_cmnd(cmd, verbose=True)
		print out
		print err
		idone += 1
		if idone >= nmax:
			break

def main():
	rnumber = ut.get_arg_with('-r')
	rslen = len('000170207')
	print '[i] run number:',rnumber
	if rnumber==None:
		rnumber='170207'
	if len(rnumber) < rslen:
		rnumber = rnumber.zfill(rslen)
	nfiles = ut.get_arg_with('-n')
	if nfiles == None:
		nfiles = 1
	else:
		nfiles = string.atoi(nfiles)
	flist = list_files(rnumber)
	get_files(flist, nfiles)

if __name__ == '__main__':
	main()

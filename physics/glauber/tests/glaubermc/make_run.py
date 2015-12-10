#!/usr/bin/env python

import os
import stat

class Jobs(object):
	def __init__(self, ncollmin, ncollmax, nev=10000, nperjob=100):
		self.ncollmin = ncollmin
		self.ncollmax = ncollmax
		self.nev = nev
		self.nperjob = nperjob
		self.input_file = '{}/tests/glaubermc/glau_pbpb_ntuple.root'.format(os.getenv('GLAUBERDIR'))

	def make_executable(self, fd):
		os.fchmod(fd.fileno(), stat.S_IRWXU | stat.S_IRWXG | stat.S_IROTH | stat.S_IXOTH)
		mode = os.fstat(fd.fileno()).st_mode
		mode |= stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH
		os.fchmod(fd.fileno(), stat.S_IMODE(mode))

	def make_scripts(self):
		dname = '{}/output_ncoll_{}_{}'.format(os.getcwd(), self.ncollmin, self.ncollmax)
		if not os.path.exists(dname):
			os.makedirs(dname)
		outnames = []
		for nstart in range(0, self.nev, self.nperjob):
			foutname = os.path.join(dname, 'job_{}.sh'.format(nstart))
			outnames.append(foutname)
			wdir = dname
			with open(foutname, 'w') as fout:
				print >> fout, '#!/bin/bash -l'
				print >> fout, 'date | tee    {}.log'.format(foutname)
				print >> fout, 'module load use.own'
				print >> fout, 'module use $HOME/devel/rootutils/python/modules'
				print >> fout, 'module load pyrut'
				print >> fout, 'module load hepsoft/latest'
				print >> fout, 'module load root'
				print >> fout, 'module load glauber'
				print >> fout, 'cd {}'.format(wdir)
				print >> fout, 'GlauberMC.exe --in {} --gen --ncoll {}:{} --nev {}:{} 2>&1 | tee -a {}.log'.format(self.input_file, self.ncollmin, self.ncollmax, nstart, self.nperjob, foutname)
				print >> fout, 'date | tee -a {}.log'.format(foutname)
				print >> fout, ''
				self.make_executable(fout)
			print '[i] written:', foutname
		subms = '{}_submit.sh'.format(dname)
		with open(subms, 'w') as fout:
			print >> fout, '#!/bin/bash'
			for s in outnames:
				print >> fout, 'qsub -o {} -e {} {}'.format(dname, dname, s)
			self.make_executable(fout)
		print '[i] written:',subms

def main():
	js = Jobs(10, 20)
	js.make_scripts()
	js.input_file = '{}/tests/glaubermc/glau_pbpb_ntuple.root'.format(os.getenv('GLAUBERDIR'))

if __name__ == '__main__':
	main()
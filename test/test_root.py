#!/usr/bin/env python

import sys
import tutils
import ROOT as r
import IPython
import draw_ntuple as dn
import dlist

def test_t0(fname1):
	fin = r.TFile(fname1)
	t = fin.Get('t')
	header = []
	v = r.std.vector("TParticle")()
	b = t.GetBranch('pfinal')
	b.SetAddress(v)
	for i in range(t.GetEntries()):
		b.GetEntry(i)
		print i, v.size()
		if i > 10:
			break
	print 'done.'

def test_t(fname1):
	fin = r.TFile(fname1)
	t = fin.Get('t')
	n = t.GetEntriesFast()
	v = r.std.vector("TParticle")()

	b = t.GetBranch('pfinal')
	b.SetAddress(r.AddressOf(v))
	print b
	for i in xrange(n):
		ib = t.LoadTree(i)
		if ib < 0:
			print '[e] unable to load entry #',i
		else:
			print '[i] loaded entry #',i
		b.GetEntry(i)
		print v.size()
		if i > 10:
			break

if __name__ == '__main__':
	tutils.setup_basic_root()
	tutils.add_ld_path('$FASTSIM/lib')
	tutils.load_lib('librutil', False)

	test_t('tree-NOcr.root')

	tutils.iprompt()
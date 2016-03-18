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
	h = r.TH1F('particle', 'particle', 100, 0, 10)
	hl = dlist.dlist('hout-{}'.format(fname1))
	fin = r.TFile(fname1)
	t = fin.Get('t')
	n = t.GetEntriesFast()

	v = r.std.vector("TParticle")()
	b = t.GetBranch('pfinal')
	b.SetAddress(r.AddressOf(v))

	xsec = [0.,0.,0.,0.]
	bh = t.GetBranch('header')
	bh.SetAddress(xsec)

	print b,bh
	for i in xrange(n):
		ib = t.LoadTree(i)
		if ib < 0:
			print '[e] unable to load entry #',i
			break
		b.GetEntry(i)
		for j in xrange(v.size()):
			h.Fill(v[j].Pt())
		#print v.size()
		#if i > 10:
		#	break
	hl.add(h)
	hl.write_to_file()

if __name__ == '__main__':
	tutils.setup_basic_root()
	tutils.add_ld_path('$FASTSIM/lib')
	tutils.load_lib('librutil', False)

	test_t('tree-NOcr.root')
	test_t('tree-cr.root')

	tutils.iprompt()
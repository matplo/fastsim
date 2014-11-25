#!/usr/bin/env python

import ROOT as r
import ol
import yat
import tutils

def make_yats(hs, hn, outfname, nev_scale=1):
    finname = 'SpectrumMinBias.root'
    if nev_scale > 1:
        finname = 'SpectrumEMCJHigh.root'
    print finname
    fin     = r.TFile(finname)
    hsum    = fin.Get(hs[0])
    nevents = hn[0]
                             
    print outfname,nevents,hsum.GetBinWidth(1)
    #rebin = 10
    #hsum.Rebin(rebin)
    for i in range(1,hsum.GetNbinsX()):
        bc = hsum.GetBinContent(i)
        bcn = bc * hsum.GetBinWidth(i)
        hsum.SetBinContent(i, bcn)
    
    #hsum.Scale(1./hsum.GetBinWidth(1))
    #hsum.Scale(1./hsum.GetBinWidth(1))    
    #hsum.Scale(nevents)

    hl = ol.ol('yat')
    gr = yat.make_reach_graph_hist(hsum, 50, nev_scale)
    hl.addgr(gr, hsum.GetTitle()+'50', 'P')
    gr = yat.make_reach_graph_hist(hsum, 100, nev_scale)
    hl.addgr(gr, hsum.GetTitle()+'100', 'P')
    gr = yat.make_reach_graph_hist(hsum, 10, nev_scale)
    hl.addgr(gr, hsum.GetTitle()+'10', 'P')
    print len(hl)
    hl.write_to_file('yats-{}'.format(outfname))

hs = ['rawspectrum']
hn = [2558670]    
make_yats(hs, hn, 'mb.root', 1. * 0.1)
hn = [1159590]
make_yats(hs, hn, 'jetT.root', 824. * 0.1)

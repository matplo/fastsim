#!/usr/bin/env python

import tutils
import ol
import ROOT as r
import array as a
import draw_utils as du
import sys
import pyutils as ut
import string
import yat

def getPtWith50(fplaw, nev, ncount = 50, nbins = 0):
    par0 = fplaw.GetParameter(0)
    #print '[d] par0: ', par0
    fplaw.SetParameter(0, nev * par0)
    fplaw.SetRange(0, 300)
    fplaw.SetNpx(300)
    h = fplaw.GetHistogram()
    bw = h.GetBinWidth(1)
    #print '[i] bin width is:',bw
    retval = -1
    for ib in range(1, h.GetNbinsX() - nbins - 1):
        #bc  = h.GetBinContent(ib)
        #bc1 = h.GetBinContent(ib + nbins)
        bc  = h.Integral(ib    , ib + nbins)
        bc1 = h.Integral(ib + 1, ib + nbins + 1)
        if bc / bw > ncount and bc1 / bw < ncount:
            retval = h.GetBinCenter(ib)
            break
    fplaw.SetParameter(0, par0)        
    return retval

def getPtWith50new(fplaw, nev, ncount = 50, nbins = 0):
    par0 = fplaw.GetParameter(0)
    fplaw.SetRange(0, 300)
    fplaw.SetNpx(300)
    h = fplaw.GetHistogram()
    return yat.getPtWith50intg_hist(h, nev, ncount)

def getPtWith50intg(fplaw, nev, ncount = 50):
    par0 = fplaw.GetParameter(0)
    #print '[d] par0: ', par0
    fplaw.SetParameter(0, nev * par0)
    fplaw.SetRange(0, 300)
    fplaw.SetNpx(300)
    h = fplaw.GetHistogram()
    retval = -1
    for ib in range(1, h.GetNbinsX() - 1):
        intg0 = h.Integral(ib  , h.GetNbinsX())
        intg1 = h.Integral(ib+1, h.GetNbinsX())
        if intg0 > ncount and intg1 < ncount:
            retval = h.GetBinCenter(ib)
            break
    fplaw.SetParameter(0, par0)    
    return retval

def getScaling(h1, h2):
    hl = ol.make_ratio(h1,h2)
    hl.make_canvas()
    hl.draw()
    tutils.gList.append(hl)

def make_reach_graph(fplaw, ncount = 50, nbins = 0):
    #nevents   = [1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12]
    nevents   = [1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11]#, 1e12]
    neventsfr = []
    pTs = []
    for nev in nevents:
        for fr in [0.25, 0.5, 1.]:
            nevfr = nev * fr
            if '--int' in sys.argv:
                pT = getPtWith50intg(fplaw, nevfr, ncount)
            else:
                #pT = getPtWith50(fplaw, nevfr, ncount, nbins)
                pT = getPtWith50new(fplaw, nevfr, ncount, nbins)
            #print nevfr, pT
            pTs.append(pT)
            neventsfr.append(nevfr)                
    nevsf = a.array('d', neventsfr)
    pTsf = a.array('d', pTs)
    tgr = r.TGraph( len(neventsfr), nevsf, pTsf)
    newname = 'tgr{}'.format(ncount)    
    tgr.SetName(newname)
    newtitle = '{} counts'.format(ncount)
    tgr.SetTitle(newtitle)
    tutils.gList.append(tgr)
    return tgr

def main():

    #nMBevs = [76826138., 4182. * 1876149.] # + 2500. * 1608515. * 0.3]
    #nMBevs = [76826138., 2500. * 1876149.] # + 2500. * 1608515. * 0.3]
    nMBevs = [76826138., 864. * 1876149.] # + 2500. * 1608515. * 0.3]    
    #nMBevs = [76826138., 4182. * 1876149. + 4182. * 1608515. * 0.3]

    scaleJ= 824.016781121
    scaleS= 751.738633064
    nMBevs = [76826138., scaleJ * 1159590.] # + 2500. * 1608515. * 0.3]    
            
    tutils.setup_basic_root()
    
    fplaw = r.TF1('fplaw', '[0] * (2./0.7 * x[0] * TMath::Exp(-(2./0.7)*x[0]) + TMath::Power(x[0],-[1]))', 5., 100)
    fplaw.SetParameter(0, 1.)
    fplaw.SetParameter(1, 5.)
    #fplaw.SetTitle('fit to min. bias')
    fplaw.GetXaxis().SetTitle('pT')
    fplaw.GetYaxis().SetTitle('1/Nev dN/dpT')

    nbins = 0
    snbins = ut.get_arg_with('--nbins')
    if snbins:
        nbins = string.atoi(snbins) - 1
        if nbins < 0:
            nbins = 0
    
    hlname = 'noname'
    if '--int' in sys.argv:
        hlname = 'pTLint-intg'
    else:
        hlname = 'pTLint-fixedpT-nb-{}'.format(nbins+1)        
    hl1 = ol.ol(hlname)
    #hl1.addh_from_file('rawspectrum', 'SpectrumMinBias.root', 'minimum bias', 'p')
    mb='/Users/ploskon/Dropbox/ALICE/Run2/Markus3/SpectrumMinBias.root'
    hl1.addh_from_file('rawspectrum', mb, 'minimum bias', 'p')
    hl1.addh_from_file('rawspectrum', 'SpectrumEMCJHigh.root', 'EMCal jet trigger, high threshold', 'p')
    bw = hl1[0].GetBinWidth(1)
    #hl1[0].Scale(1./bw)
    #hl1[1].Scale(1./bw)
    getScaling(hl1[1], hl1[0])
    #hl1.last().Scale(1./850.)
    #hl1.last().Scale(1./942.) #Markus
    #hl1.last().Scale(1./864.454841255)
    hl1.last().Scale(1./scaleJ)
    tc = hl1.make_canvas()
    tc.Divide(2,1)
    tc.cd(1)
    hl1[0].Fit(fplaw, 'RMNQ')
    fplaw.SetRange(50, 100)
    hl1[1].Fit(fplaw, 'RMNQ')
    hl1.addf(fplaw, 'fit to MB and EMCal-T', 'L +l1')# (Bmann + plaw) 5-100 GeV/c')
    #fplaw.DrawCopy()
    hl1.reset_axis_titles('p_{T} (GeV/c)', '1/N^{MB}_{ev} dN/dp_{T} (GeV/c)^{-1}')    
    hl1.draw('p')
    r.gPad.Update()
    hl1.self_legend(1, 'p-Pb #sqrt{s}=5.02 TeV charged particles')
    r.gPad.SetLogy()
            
    tc.cd(2)    
    hl = ol.ol(hlname + '-2')
    hl.add_from_file('tgr50_yat',  'yats-mb.root', 'MB data',  'p +k2')
    hl.add_from_file('tgr50_yat',  'yats-jetT.root', 'T data',  'p +k1')    
    tgr50 = make_reach_graph(fplaw, 50, nbins)
    hl.addgr(tgr50, 'from p_{T} fit', 'l')
    fplaw.SetRange(0,500)
    fplaw.SetNpx(500)
    #tgr50n = yat.make_reach_graph_hist(fplaw.GetHistogram(), ncount = 50, nev_scale = 1)
    #hl.addgr(tgr50n, 'from p_{T} data', 'l')    
    #tgr100 = make_reach_graph(fplaw, 100, nbins)    
    #hl.addgr(tgr100, '', 'l')
    #tgr10 = make_reach_graph(fplaw, 10, nbins)    
    #hl.addgr(tgr10, '', 'l')
    hl.reset_axis_titles('N minimum bias events', 'p_{T} (GeV/c)')
    hl.draw('a', 0.1, 200.)
    if '--lines' in sys.argv:
        du.draw_line(nMBevs[0], hl.miny, nMBevs[0], hl.maxy, 2)
        du.draw_line(nMBevs[1], hl.miny, nMBevs[1], hl.maxy, 4)    
    if '--int' in sys.argv:
        hlname = 'yield above threshold'
    else:
        hlname = 'at fixed p_{T} / [nb] GeV/c'.replace('[nb]', '{}'.format(nbins+1))
    hl.self_legend(1, hlname)
    r.gPad.SetLogx()
    if '--logy' in sys.argv:
        r.gPad.SetLogy()        
    r.gPad.SetGridx()
    r.gPad.SetGridy()
    tc.Update()

    if '--print' in sys.argv:
        tc.Print(tc.GetName()+'.pdf', '.pdf')
    else:
        tutils.wait()

if __name__=="__main__":
    main()

#!/usr/bin/env python

import tutils
import ol
import ROOT as r
import array as a
import draw_utils as du
import sys
import pyutils as ut
import string

def getScalingOld(h1, h2, minx = 45, maxx = 90):
    hl = ol.make_ratio(h1, h2)
    flin = r.TF1('flin'+hl.name, '[0]', minx, maxx)
    hl[0].Fit(flin, 'RMN')
    hl.addf(flin)
    hl.make_canvas()
    hl.draw()
    tutils.gList.append(hl)
    return flin.GetParameter(0)

def getScaling(h, fit, minx = 45, maxx = 90):
    hl = ol.ol('hl-ratio-'+h.GetName())
    hratio = h.Clone('ratio'+h.GetName())
    hratio.Divide(fit)
    flin = r.TF1('flin'+hl.name, '[0]', minx, maxx)
    hl.addh(hratio, h.GetTitle(), 'P')
    hl[0].Fit(flin, 'RMN')
    hl.addf(flin)
    hl.make_canvas()
    hl.draw()
    tutils.gList.append(hl)
    return flin.GetParameter(0)

def getRatioToFit(h, fit):
    hratio = h.Clone('ratio'+h.GetName())
    hratio.Divide(fit)
    return hratio
    
def main():
    
    tutils.setup_basic_root()
    
    fplaw = r.TF1('fplaw', '[0] * (2./0.7 * x[0] * TMath::Exp(-(2./0.7)*x[0]) + TMath::Power(x[0],-[1]))', 15., 50.)
    fplaw.SetParameter(0, 1.)
    fplaw.SetParameter(1, 5.)
    #fplaw.SetTitle('fit to min. bias')
    fplaw.GetXaxis().SetTitle('pT')

    hlname = 'tmbratio'    
    hl1 = ol.ol(hlname)
    mb='/Users/ploskon/Dropbox/ALICE/Run2/Markus3/SpectrumMinBias.root'
    #hl1.addh_from_file('rawspectrum', 'SpectrumMinBias.root', 'minimum bias', 'p')
    hl1.addh_from_file('rawspectrum', mb, 'minimum bias', 'p')
    hl1.addh_from_file('rawspectrum', 'SpectrumEMCJHigh.root', 'EMCal jet trigger, high threshold', 'p')
    bw = hl1[0].GetBinWidth(1)
    hl1.addh_from_file('rawspectrum', 'SpectrumEMCGHigh.root', 'EMCal shower trigger, high threshold', 'p')    
    tc = hl1.make_canvas()
    hl1[0].Fit(fplaw, 'RMNQ')
    npx_range = 500
    fplaw.SetRange(0, npx_range)
    fplaw.SetNpx(npx_range)    
    hl1.addf(fplaw, 'fit to MB [15-50 GeV/c]', 'L +l1')# (Bmann + plaw) 5-100 GeV/c')
    #fplaw.DrawCopy()
    hl1.reset_axis_titles('p_{T} (GeV/c)', '1/N_{ev} dN/dp_{T} (GeV/c)^{-1}')    
    hl1.draw('p')
    r.gPad.Update()
    hl1.self_legend(1, 'p-Pb #sqrt{s}=5.02 TeV charged particles', 0.44,0.59,0.99,0.87)
    r.gPad.SetLogy()

    if '--print' in sys.argv:
        tc.Print(tc.GetName()+'.pdf', '.pdf')

    minxJ = 50
    maxxJ = 100
    scaleJ = getScaling(hl1[1], fplaw, minxJ, maxxJ)
    #hl1.last().Scale(1./942.)
    minxS = 50
    maxxS = 100
    scaleS = getScaling(hl1[2], fplaw, minxS, maxxS)    
    #hl1.last().Scale(1./846.)
    print 'scaleJ=',scaleJ
    print 'scaleS=',scaleS
    
    hl2 = ol.ol(hlname + '-ratio')
    tc = hl2.make_canvas()
    ratioJ = getRatioToFit(hl1[1], fplaw)
    ratioS = getRatioToFit(hl1[2], fplaw)
    if '--fit' in sys.argv:
        hl2.addh(ratioJ, 'jet-T (a0={0:.0f})'.format(scaleJ))
        hl2.addh(ratioS, 'shower-T (a0={0:.0f})'.format(scaleS))
    else:
        hl2.addh(ratioJ, 'jet-T')
        hl2.addh(ratioS, 'shower-T')
        
    hl2.reset_axis_titles('p_{T} (GeV/c)', 'triggered / minimum bias')
    hl2.draw('p')
    du.draw_line(minxJ, scaleJ, maxxJ, scaleJ, hl2[0].GetLineColor())
    du.draw_line(minxS, scaleS, maxxS, scaleS, hl2[1].GetLineColor())    
    r.gPad.Update()
    hl2.self_legend(1, 'p-Pb #sqrt{s}=5.02 TeV charged particles', 0.19,0.6,0.74,0.88)
    #r.gPad.SetLogy()
    
    if '--print' in sys.argv:
        tc.Print(tc.GetName()+'.pdf', '.pdf')
    else:
        tutils.wait()

if __name__=="__main__":
    main()

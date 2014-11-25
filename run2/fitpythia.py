#!/usr/bin/env python

import tutils
import ol
import ROOT as r
import array as a
import draw_utils as du
import sys
import pyutils as ut
import string

def getRatioToFit(h, fit):
    hratio = h.Clone('ratio'+h.GetName())
    hratio.Divide(fit)
    return hratio

def make_fit(h, xmin, xmax):
    fplaw = r.TF1('fplaw', '[0] * (2./0.7 * x[0] * TMath::Exp(-(2./0.7)*x[0]) + TMath::Power(x[0],-[1]))', xmin, xmax)
    fplaw.SetParameter(0, 1.)
    fplaw.SetParameter(1, 5.)
    #fplaw.SetTitle('fit to min. bias')
    fplaw.GetXaxis().SetTitle('pT')    
    h.Fit(fplaw, 'RMNQ')
    return fplaw

def main():
    
    tutils.setup_basic_root()
    
    pyfiles = [
        './pythia_files/fileset-2760-files.txt/fjrun.root',
        './pythia_files/fileset-5500-files.txt/fjrun.root',
        './pythia_files/fileset-14000-files.txt/fjrun.root',        
        ]
        
    hname = 'hjaktR04w'
        
    fits = []
    hlname = 'fitpythia'    
    hl1 = ol.ol(hlname)
    tc = hl1.make_canvas()
    for i in range(len(pyfiles)):
        hl1.addh_from_file(hname, pyfiles[i], pyfiles[i].split('/')[2], 'p')
        h = hl1.last()
        h.Rebin(5)
        bw = h.GetBinWidth(1)
        fit = make_fit(h, 15, 150)
        tutils.gList.append(fit)
        npx_range = 500
        hl1.addf(fit, 'fit py [15-50 GeV/c]', 'L +l1')# (Bmann + plaw) 5-100 GeV/c')
        
    #fplaw.DrawCopy()
    hl1.reset_axis_titles('p_{T} (GeV/c)', '1/N_{ev} dN/dp_{T} (GeV/c)^{-1}')    
    hl1.draw('p')
    r.gPad.Update()
    hl1.self_legend(1, 'p-Pb #sqrt{s}=5.02 TeV charged particles', 0.44,0.59,0.99,0.87)
    r.gPad.SetLogy()

    if '--print' in sys.argv:
        tc.Print(tc.GetName()+'.pdf', '.pdf')
    else:
        tutils.wait()

if __name__=="__main__":
    main()

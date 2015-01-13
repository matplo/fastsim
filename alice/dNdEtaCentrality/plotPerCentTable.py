#!/usr/bin/env python

import sys
import tutils
import ol
import ROOT as r

def getIntAbove(h):
    hout = h.Clone('intAbove' + h.GetName())
    newTitle = h.GetTitle() + ' Int Above'
    hout.SetTitle(newTitle)
    hout.Reset()
    maxbin = h.GetNbinsX() + 1
    for ib in range(1, maxbin):
        c = h.Integral(ib, maxbin)
        hout.SetBinContent(ib, c)
    return hout

def make_ratio_binbybin(h1, h2):
    hr = h1.Clone('{} / {}'.format(h1.GetName(), h2.GetName()))
    newTitle = '{} / {}'.format(h1.GetTitle(), h2.GetTitle())
    hr.SetTitle(newTitle)
    hr.Reset()
    maxbin = h1.GetNbinsX()  
    for ib in range(1, maxbin + 1):
        c1 = h1.GetBinContent(ib)
        c2 = h2.GetBinContent(ib)
        if c2 != 0:
            r = c1 / c2
        else:
            r = 0
        print c1, c2, r
        hr.SetBinContent(ib, r)
    return hr

def printRow(l, npad, intis = 0):
    formatting = None
    if '--twiki' in sys.argv:
        formatting = 'twiki'
    if '--latex' in sys.argv:
        formatting = 'latex'

    separator = ''
    start = ''
    end = ''
    if formatting == 'twiki':
        start = ' | '
        separator = ' | '
        end = ' | '
    if formatting == 'latex':
        start = ''
        separator = '&'
        end = '\\\\'    
    form = '{:10.4f}'
    form = form.replace('4f', str(npad) + 'f')
    print start,        
    for i in range(0, len(l)):
        nb = l[i]
        if intis == i:
            print '{:10.0f}'.format(nb),
        else:
            print form.format(nb),
        if i < len(l) - 1:
            print separator,
        else:
            print end
    
def printTable(h, hi, prec = 1):
    if '--latex' in sys.argv:
        print '\\begin{tabular}{r r r r r r r}'
    maxbin = h.GetNbinsX()
    for ib in range(1, maxbin + 1):
        lowNch = h.GetBinLowEdge(ib)
        avNch  = h.GetBinCenter(ib)
        hiNch  = h.GetBinCenter(ib) + h.GetBinWidth(ib) / 2.
        hc     = h.GetBinContent(ib)
        
        xsecThisBin    = hi.GetBinContent(ib)
        xsecThisBinLow = 0
        if ib < maxbin:
            xsecThisBinLow = hi.GetBinContent(ib + 1)        
        xsecThisBinHi  = 1
        if ib > 1:
            xsecThisBinHi  = hi.GetBinContent(ib - 1)
            
        #printRow([ib, lowNch, avNch, hiNch, xsecThisBin, xsecThisBinLow, xsecThisBinHi], 2)
        #printRow([ib, lowNch, avNch, hiNch, xsecThisBin, xsecThisBinHi],2)
        xsecThisBinHiCent = xsecThisBinLow
        printRow([ib, lowNch, avNch, hiNch,
                  xsecThisBinHiCent * 100.,
                  xsecThisBin * 100.,
                  hc * 100.], prec)        
    if '--latex' in sys.argv:
        print '\\end{tabular}'
            
def main():

    tutils.setup_basic_root()

    fname = [ 'PbPbMinBias.root', 'PbPbVeryCentral.root' ]
    
    hl = ol.ol('frac-xsection')
    hl.addh_from_file('histCFW', fname[0], 'min. bias, x-sec within bin;<N_{ch}>;fraction of the total hadr. x-section', 'HIST')
    hl.addh_from_file('histCFW', fname[1], 'central, x-sec within bin;<N_{ch}>;fraction of the total hadr. x-section', 'HIST')

    hl.addh_from_file('histCFL', fname[0], 'min. bias, integrated x-sec;<N_{ch}>;fraction of the total hadr. x-section', 'HIST')
    hl.addh_from_file('histCFL', fname[1], 'central, integrated x-sec;<N_{ch}>;fraction of the total hadr. x-section', 'HIST')

    hlt = ol.ol('frac-xsection-tmp')
    hlt.addh_from_file('histCFW', fname[0], 'min. bias, x-sec within bin;<N_{ch}>;fraction of the total hadr. x-section', 'P')
    hlt.addh_from_file('histCFW', fname[1], 'central, x-sec within bin;<N_{ch}>;fraction of the total hadr. x-section', 'P')

    hlt.addh_from_file('histCFL', fname[0], 'min. bias, integrated x-sec;<N_{ch}>;fraction of the total hadr. x-section', 'P')
    hlt.addh_from_file('histCFL', fname[1], 'central, integrated x-sec;<N_{ch}>;fraction of the total hadr. x-section', 'P')
    
    for l in hl.l:
        print l.GetTitle()
    
    #hint = getIntAbove(hl[0])
    #hl.addh(hint, hl[0].GetTitle() + ' int above', 'P')
    hl.make_canvas()

    #hl.zoom_axis(0, 0, 3499)    
    hl.draw('',logy=True)
    hlt.draw('same')
    hl.self_legend(1,'',0.18,0.25,0.86,0.53)
    r.gPad.SetLogy()
    hl[0].GetXaxis().SetRangeUser(0, 4000)
    
    if '--ratio' in sys.argv:
        hlr = ol.ol('ratios')
        hlr.make_canvas()
        hlr.addh(ol.make_ratio(hl[2], hint)[0])
        #hlr.addh(make_ratio_binbybin(hl[2], hint))
        hlr.draw(miny=-2, maxy=2, logy=True)
        hlr.self_legend()

    h  = hl[0] #perbin
    hi = hl[2] #integrated
    printTable(h, hi, 1)

    print ' '

    h  = hl[1] #perbin
    hi = hl[3] #integrated
    printTable(h, hi, 2)
        
    hl.tcanvas.Update()

    hl.write_to_file('ALICE-Nch-xsec.root', 'recreate')
    
    if '--no-stop' in sys.argv:
        return
    
    tutils.wait()
    
if __name__=="__main__":
    main()

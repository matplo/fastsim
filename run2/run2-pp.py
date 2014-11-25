#!/usr/bin/env python

import math
import tutils
import ol
import ROOT as r
import array as a
import draw_utils as du
import sys
import pyutils as ut
import string

def plaw_new(xmin = 5., xmax = 100.):
    fplaw = r.TF1('fplaw', '[0] * (x[0] * TMath::Exp(-[2]*x[0]) + TMath::Power(x[0],-[1]))', xmin, xmax)
    #fplaw = r.TF1('fplaw', '[0] * x[0] * TMath::Exp(-[3].*x[0]) *( (([1]-1.)*([1]-2.)) / ([1]*[2]*[1]*[2]) ) * TMath::Power(x[0], -[1])')
    fplaw.SetParameter(0, 1.)
    fplaw.SetParameter(1, 5.)
    fplaw.SetParameter(2, 1.01)
    fplaw.SetParLimits(2, 1.01, 1.1)
    #fplaw.SetParameter(3, 1.)        
    #fplaw.SetTitle('fit to min. bias')
    fplaw.GetXaxis().SetTitle('pT')
    #fplaw.GetYaxis().SetTitle('1/Nev dN/dpT')
    return fplaw

def plaw(xmin = 5., xmax = 100.):
    fplaw = r.TF1('fplaw', '[0] * (x[0] * TMath::Exp(-1.2*x[0]) + TMath::Power(x[0],-[1]))', xmin, xmax)
    fplaw.SetParameter(0, 1.)
    fplaw.SetParameter(1, 5.)
    #fplaw.SetTitle('fit to min. bias')
    fplaw.GetXaxis().SetTitle('pT')
    #fplaw.GetYaxis().SetTitle('1/Nev dN/dpT')
    return fplaw

def ratio_gr_to_fit(gr, f):
    xa = []
    ya = []
    for i in range(gr.GetN()):
        x = gr.GetX()[i]
        y = gr.GetY()[i]
        try:
            ynew = gr.GetY()[i] / f.Eval(x)
        except:
            ynew = 0
        #print x,ynew
        i += 1
        xa.append(x)
        ya.append(ynew)
    xaf = a.array('f', xa)
    yaf = a.array('f', ya)
    retgr = r.TGraph(gr.GetN(), xaf, yaf)
    retgr.SetName(gr.GetName() + '-rtofit-{}'.format(f.GetName()))
    return retgr

def relat_err_gr(gr, which = 0, offset = 0, sign = 1):    
    xa = []
    ya = []
    for i in range(gr.GetN()):
        x = gr.GetX()[i]
        y = gr.GetY()[i]
        try:
            if which == 0:
                ynew = sign * gr.GetEYlow()[i] / gr.GetY()[i] + offset
            else:
                ynew = sign * gr.GetEYhigh()[i] / gr.GetY()[i] + offset    
        except:
            ynew = 0
        #print x,ynew
        i += 1
        xa.append(x)
        ya.append(ynew)
    xaf = a.array('f', xa)
    yaf = a.array('f', ya)
    retgr = r.TGraph(gr.GetN(), xaf, yaf)
    retgr.SetName(gr.GetName() + '-err-{}'.format(which))
    return retgr

def get_rel_err(atx, gr):
    for i in range(gr.GetN()-1):
        x   = gr.GetX()[i]
        xp1 = gr.GetX()[i+1]
        if x <= atx and xp1 > atx:
            yelow = gr.GetEYlow()[i] / gr.GetY()[i]
            yehigh = gr.GetEYhigh()[i] / gr.GetY()[i]            
            return yehigh, yelow
    return 0,0

def make_gr_stat_uncert(f,pt = 150, shift = 0):
    #stat uncert
    sigma_inel = 65. * 1e-3 #barns
    micro = 1e-6    
    nano  = 1e-9
    pico  = 1e-12
    # acceptance = angle and eta (NLO is +- 0.5 eta)
    acc = 110. / 360. * 0.6 / 1.

    intLa = []
    Nja   = []
    eNja  = []
    one   = []
    zero  = []
    npoints = 6
    for iL in range(1, npoints + 1):
        intL = math.pow(10., iL) * 0.1
        xsec = f.Eval(pt)
        Nj    = xsec * micro * intL / nano * acc
        errNj = math.sqrt(Nj)
        errNjpcent = errNj / Nj * 100.
        #print Nj, errNj, errNjpcent,'%', xsec, intL, 'nb'
        Nja.append(Nja)
        #eNja.append(errNjpcent)
        eNja.append(errNj / Nj)
        intLa.append(intL * (1. + shift))
        one.append(1)
        zero.append(0)

    intLaf = a.array('f', intLa)
    onef   = a.array('f', one)
    zerof  = a.array('f', zero)
    eNjaf  = a.array('f', eNja)

    gr_err = r.TGraphErrors(npoints, intLaf, onef, zerof, eNjaf)
    return gr_err

def ver1():
    tutils.setup_basic_root()
    hl1 = ol.ol('v1-hl1')
    tc = hl1.make_canvas()
    tc.Divide(2,1)
    hl1.add_from_file('totalError', './files/55TeV-totalError.root', 'NLO 5.5 TeV', 'P')
    # these data are in mub per bin
    
    tc.cd(1)
    fitxmin = 20
    fitxmax = 250
    f = plaw(fitxmin, fitxmax)
    gr = hl1.last()
    gr.Fit(f, 'RM0')
    f.SetRange(fitxmin, fitxmax)
    fit_title = 'fit [{}-{}]'.format(fitxmin, fitxmax)
    hl1.addf(f, fit_title, 'L +l1')
    hl1.zoom_axis(0, fitxmin - 20, fitxmax + 20)
    hl1.draw('A', 1e-5, 1e3)
    hl1.reset_axis_titles('p_{T}', 'd#sigma/dp_{T} (#mu b / GeV/c)')
    hl1.self_legend(1, '', 0.5, 0.7)
    r.gPad.SetLogy()
    r.gPad.SetGridx()
    r.gPad.SetGridy()
    hl1.update()

    tc.cd(2)
    gr_rf = ratio_gr_to_fit(gr, f)
    hl2 = ol.ol('v1-hl2')
    hl2.addgr(gr_rf, 'ratio to fit', 'P')
    gr_el = relat_err_gr(gr, 0, 1, -1)
    hl2.addgr(gr_el, 'elow', 'P')
    gr_eh = relat_err_gr(gr, 1, 1, +1)
    hl2.addgr(gr_eh, 'ehigh', 'P')

    hl2.zoom_axis(0, 0, fitxmax - 1)    
    hl2.draw('A', 0, 2)
    hl2.self_legend(1, '', 0.5, 0.7)
    r.gPad.SetGridx()
    r.gPad.SetGridy()
    hl2.update()

    hlerr = ol.ol('hlerr')
    hlerr.make_canvas()
    gr_err = make_gr_stat_uncert(f, 100, 0.)    
    hlerr.addgr(gr_err, 'stat. uncertainty at p_{T}^{jet}=100 GeV', 'P')
    gr_err = make_gr_stat_uncert(f, 150, 0.2)    
    hlerr.addgr(gr_err, 'stat. uncertainty at p_{T}^{jet}=150 GeV', 'P')
    gr_err = make_gr_stat_uncert(f, 200, 0.4)    
    hlerr.addgr(gr_err, 'stat. uncertainty at p_{T}^{jet}=200 GeV', 'P')
    hlerr.draw('A', 0, 2)
    hlerr.reset_axis_titles('integrated luminosity (nb^{-1})',
                            'relative uncertainty')
    tl = hlerr.self_legend(1, 'pp at #sqrt{s}=5.5 TeV anti-k_{T} jets R=0.4 in EMCal',
                           0.4, 0.7)
    hlerr.legend.AddEntry('', 'uncertainty from NLO in dashed lines','')
    #NLO uncerts at 150: 0.14 0.44
    el,eh = get_rel_err(100, gr)
    du.draw_line(1e1, 1.-el, 1e2*0.9, 1.-el, hlerr[0].GetLineColor())
    du.draw_line(1e1, 1.+eh, 1e2*0.9, 1.+eh, hlerr[0].GetLineColor())
    print el,eh
    el,eh = get_rel_err(150, gr)
    du.draw_line(1e2, 1.-el, 1e3*0.9, 1.-el, hlerr[1].GetLineColor())
    du.draw_line(1e2, 1.+eh, 1e3*0.9, 1.+eh, hlerr[1].GetLineColor())
    print el,eh
    el,eh = get_rel_err(200, gr)
    du.draw_line(1e3, 1.-el, 1e4*0.9, 1.-el, hlerr[2].GetLineColor())
    du.draw_line(1e3, 1.+eh, 1e4*0.9, 1.+eh, hlerr[2].GetLineColor())
    print el,eh
            
    r.gPad.SetLogx()
    r.gPad.SetGridx()
    r.gPad.SetGridy()
    hlerr.zoom_axis(0, 0, 1e4 * 9.)
    
    hlerr.update()
    
    tutils.wait()

if __name__=="__main__":
    if '-d' in sys.argv:
        ol.gDebug = True        
    ver1()

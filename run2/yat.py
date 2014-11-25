import array as a
import ROOT as r
import tutils
import ol

def getPtWith50intg_hist(h, nev, ncount = 50):
    bw = h.GetBinWidth(1)
    retval = -1    
    for ib in range(1, h.GetNbinsX() - 1):
        intg0 = h.Integral(ib  , h.GetNbinsX()) * nev * bw
        intg1 = h.Integral(ib+1, h.GetNbinsX()) * nev * bw
        #print h.GetBinCenter(ib), intg0, intg1, bw
        if intg0 > ncount and intg1 < ncount:
            retval = h.GetBinCenter(ib)
            break
    return retval

def make_reach_graph_hist(h, ncount = 50, nev_scale = 1):
    #nevents   = [1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12]
    nevents   = [1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11]#, 1e12]
    neventsfr = []
    pTs = []
    for nev in nevents:
        for fr in [0.25, 0.5, 1.]:
            nevfr = nev * fr
            pT = getPtWith50intg_hist(h, nevfr / nev_scale, ncount)
            #print 'nevs=',nevfr, 'pT=',pT
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

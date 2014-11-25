#!/usr/bin/env python

import ROOT as r

fin = r.TFile('Jetcrosssection.root')
lin_name = 'RatioSpectra'
lin_name = '55TeV'
lin_name = '14TeV'
tls = fin.Get(lin_name)
for i in range(tls.GetEntries()):
    print '[i]',tls.At(i).GetName()

grnames = [ 'totalError', 'pdferror', 'scaleerror']

for grname in grnames:
    tgr = tls.FindObject(grname)
    if tgr:
        outf = r.TFile('{}-{}.root'.format(lin_name, grname), 'recreate')
        outf.cd()
        tgr.Write()
        outf.Close()
        print '[i] written:',tgr.GetName()
    else:
        print '[e] no graph...'

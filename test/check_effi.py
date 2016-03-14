#!/usr/bin/env python

import sys
import tutils
import ROOT as r
import IPython
import draw_ntuple as dn
import tutils as tu
import dlist

def effi(fname, var1, var2, ptzoom, bwidth = 0.1, dopt='E1'):

    tutils.setup_basic_root()

    ntname = 't'
    cuts = '(header.sigma) * (1)'
    #cuts = '(1)'
    tc   = tu.getTempCanvas()
    tc.cd()
    href = dn.h1d_from_ntuple(fname, ntname, var1, cuts, bwidth=bwidth, xlow=0, xhigh = 100)
    hali = dn.h1d_from_ntuple(fname, ntname, var2, cuts, bwidth=bwidth, xlow=0, xhigh = 100)

    stag = '{}-{}-{}'.format(fname, var1, var2)
    hl = dlist.dlist('spectra_{}'.format(stag))
    hl.add(href, var1, 'p')
    hl.add(hali, var2, 'p')
    tc = hl.make_canvas()
    tc.Divide(2,1)
    tc.cd(1)
    hl.draw(logy=True)
    hl.self_legend()
    r.gPad.SetLogy()
    r.gPad.Update()    

    hlr = hl.ratio_to(opt=dopt)
    hlr.name = hl.name + '_effi'
    if var1 == 'pcharged.Pt()':
        hlr.add_from_file('ratiocent_MB_true_effi_tmp_CombinedEfficiencies_centeta_smooth', '../params/alice/CombinedEfficiencies_centeta_smooth.root', 'effi MC', 'hist l')
    #hlr.make_canvas()
    tc.cd(2)
    hlr.zoom_axis(0, 0, ptzoom)
    hlr.draw(logy=False, miny=0, maxy=2)    
    hlr.self_legend()

    r.gPad.SetGridy()

    r.gPad.Update()    

    tutils.gList.append(hl)
    tutils.gList.append(hlr)

    hl.write_to_file()
    hlr.write_to_file()

    #tc   = tu.getTempCanvas()
    #tc.Close()

    print '[i] done with',var1,var2
    
if __name__=="__main__":

    jbin = 5.0
    vars = [
            [ 'pcharged.Pt()' ,     'pchargedali.Pt()'          , 10, 0.1,  'E1'],
            [ 'jcut.Pt()',          'jfound.Pt()'               , 50, jbin,  'hist l'],
            [ 'jcut.Pt()',          'jfound5.Pt()'              , 50, jbin,  'hist l'],
            [ 'jcut.Pt()',          'jfound10.Pt()'             , 50, jbin,  'hist l'],
            [ 'jcut.Pt()',          'jfound20.Pt()'             , 50, jbin,  'hist l'],
            [ 'jchargedcut.Pt()',   'jchargedfound.Pt()'        , 50, jbin,  'hist l'],
            #[ 'jchargedfound.Pt()', 'jchargedalicut.Pt()'       , 50, jbin,  'hist l'],
            #[ 'jparton.Pt()',        'jfoundpartonfull.Pt()'    , 50, jbin,  'hist l'],
            #[ 'jparton.Pt()',        'jfoundparton.Pt()'        , 50, jbin,  'hist l'],
            #[ 'jparton.Pt()',        'jfoundparton5.Pt()'       , 50, jbin,  'hist l'],
            #[ 'jparton.Pt()',        'jfoundparton10.Pt()'      , 50, jbin,  'hist l'],
            #[ 'jparton.Pt()',        'jfoundparton20.Pt()'      , 50, jbin,  'hist l']
        ];

    fname = 'tree-default_fastsim_out.root'
    if '--in' in sys.argv:
        fname = tutils.get_arg_with('--in')

    for i,v in enumerate(vars):
        jmax = 0
        if i > 0:
            jmaxtmp = tutils.get_arg_with('--jmax')
            if jmaxtmp:
                jmax = float(jmaxtmp)
            else:
                jmax = 0
        if jmax <= 0:
            jmax = v[2]
        effi(fname, v[0], v[1], jmax, v[3], v[4])

    if not tutils.is_arg_set('-b'):
        IPython.embed()

#!/usr/bin/env python

import tutils
import sys
import ol
import ROOT

def get_fh():
    files = [
        '/Users/ploskon/Dropbox/ALICE/Upgrade/NestorNLO/Xiaoming/1st/pyxsect/outputs/AnalysisOutputs_InclPt.root',
        '/Users/ploskon/Dropbox/ALICE/Upgrade/NestorNLO/D-meson-ratio.root',
        '/Users/ploskon/Dropbox/ALICE/Upgrade/NestorNLO/fromMarkus/NLO_ratio.root',
        ]

    hnames = [
        'hRatio',
        'Graph0',
        'grsum_NLO'
        ]
    return hnames,files

def main():
    tutils.setup_basic_root()

    fhs = get_fh()
    print fhs

    ratio = ol.ol('ratio_5.5-to-14-TeV')

    htitle = 'PYTHIA (tune 6) anti-k_{T} R=0.4 jets |#eta_{jet}|<0.5'
    ratio.addh_from_file(fhs[0][0], fhs[1][0], htitle, 'P')
    
    f = ROOT.TF1('linearfit', 'pol1', 20, 300)
    f.SetParameter(0, 3.500)
    f.SetParameter(1, 0.024)    
    ratio.last().Fit(f, 'RMN0')
    ftitle = 'linear fit: p0={:.2} (#pm{:.2}) p1={:.2} (#pm{:.2})'.format(f.GetParameter(0), 
                                                                    f.GetParError(0),
                                                                    f.GetParameter(1), 
                                                                    f.GetParError(1))    
    ftitle = ftitle.replace('p0','p_{0}').replace('p1','p_{1}')
    f.SetTitle(ftitle)
    f.SetRange(0, 450)
    ratio.addf(f, ftitle, 'L hist +l2 +k34')
    
    #ratio.add_from_file(fhs[0][3], fhs[1][3], 'Prompt D-meson by FONLL, |#eta| < 0.5 ', '+l1 +k4')
    #ratio.add_from_file(fhs[0][4], fhs[1][4], 'Prompt D-meson by FONLL, |#eta| < 0.5 ', '+l1 +k4')            

    ratio.add_from_file(fhs[0][2], fhs[1][2],
                        'Jets NLO N. Armesto Priv. Comm. w/ uncert.',
                        'L P +l1')
    
    ratio.add_from_file(fhs[0][1], fhs[1][1], 'Prompt D-meson by FONLL, |#eta| < 0.5 ', '+l1 +k32')
    
    ratio.reset_axis_titles(None, 'x-section ratio: 14 TeV / 5.5 TeV')
    #ratio.zoom_axis(0, 0, 350)
    ratio.zoom_axis(0, 0, 290)
    ratio.draw('', 0, 12.5)
    legtitle = 'Ratios:'        
    legtitle = '5.5 TeV / 14 TeV'
    #ratio.self_legend(1, legtitle, 0.15,0.62,0.73,0.84, 0.04)
    #ratio.self_legend(1, legtitle, 0.35,0.2284946,0.5805369,0.438172, 0.03)
    ratio.self_legend(1, legtitle, 0.2054598,0.6610169,0.4367816,0.8707627)
    ROOT.gPad.SetGridx()
    ROOT.gPad.SetGridy()
    ratio.update()

    
    tutils.wait()

if __name__=="__main__":
    main()

    

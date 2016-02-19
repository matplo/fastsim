#!/usr/bin/env python -i

import sys
import tutils
import ROOT as r
import IPython
import dlist
import pyutils as ut

def smoothed(hname, fname, xmin, xmax, ntimes):
    hl = dlist.dlist('effi_tmp')
    htitle = 'sm_{}_{}_{}'.format(xmin, xmax, ntimes)
    hl.add_from_file(hname, fname, htitle, 'p')
    hl.last().obj.GetXaxis().SetRange(xmin, xmax)
    hl.last().obj.Smooth(ntimes, 'R')
    tutils.gList.append(hl)
    return hl.last().obj

def main():
    tutils.setup_basic_root()
    finput = 'CombinedEfficiencies_centeta.root'
    hl = dlist.dlist(finput.replace('.root','_smooth'))
    hl.add_from_file('MB', finput, 'default', 'p')

    for n in range(1, 7, 2):
        hsm = smoothed('MB', finput, 15, 200, n)
        hl.add(hsm, 'smoothed ntimes={}'.format(n), 'p')

    tc = hl.make_canvas(500, 800)
    tc.Divide(1,2)

    tc.cd(1)
    hl.draw()
    hl.self_legend(x1=0.3, y1=0.3, y2 = 0.5)

    hl.write_to_file()

    hlr = hl.ratio_to(1, 'E1 p')
    tc.cd(2)
    hlr.draw(miny=0.8, maxy=1.2)
    hlr.self_legend(x1=0.3)

    tutils.gList.append(hl)
    tutils.gList.append(hlr)

if __name__=="__main__":
    main()
    if not ut.is_arg_set('-b'):
        IPython.embed()

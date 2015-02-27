#!/usr/bin/env python -i

import tutils
import draw_utils as du
import ROOT
import ol
import math

consthbar = 1.
constc    = 1.
k         = 2.

def fals(r):
    return 1 - 1. / r / 10.
    #return 0.2#+ math.sqrt(math.fabs(r * 10.))
    #return r * math.sqrt(math.fabs(r))
    
def Vqcd(r):
    '''
    k is the field energy per unit length == string tension
    '''
    print r, fals(r)
    ret = - 4./3. * fals(r) * consthbar * constc / r + k * r
    return ret

def my_derivative(x,y):
    for i in range(1, len(x)):
        ret = math.fabs((y[i] - y[i-1]) / (x[i] - x[i-1]))
        yield ret

from scipy.misc import derivative 
    
def main():

    tutils.setup_basic_root()

    step  = 0.01
    niter = 200
    rmin  = step * 1.
    rmax  = step * niter
    x = []
    y = []
    yd = []
    als = []
    for rc in range(1, niter):
        r = step * rc
        if r < 0.1:
            continue
        v = Vqcd(r)
        als.append( fals(r) )
        x.append(r)
        y.append(v)

        try:
            deriv = -1. * derivative(Vqcd, r)
        except ZeroDivisionError as e:
            print e
            print 'V=',v,'at r=',r
            pass
        
        #print deriv
        yd.append(deriv)

    
    hl = ol.ol('V and F')        
    tc = hl.make_canvas()
    du.make_canvas_grid(3, tc)
    tc.cd(1)
    gr = ol.make_graph_xy('v',x,y)
    hl.add(gr, 'v;r;V(r)', 'L')
    hl.draw('A')
    #ROOT.gPad.SetLogy()
    ROOT.gPad.SetGridx()
    ROOT.gPad.SetGridy()

    hlals = ol.ol('lals')
    tc.cd(2)
    grals = ol.make_graph_xy('als',x,als)
    hlals.add(grals, 'v;r;als(r)', 'L')
    hlals.draw('A')
    #ROOT.gPad.SetLogy()
    ROOT.gPad.SetGridx()
    ROOT.gPad.SetGridy()    
        
    hld = ol.ol('dV and dF')
    tc.cd(3)
    grdr = ol.make_graph_xy('dv_dr',x,yd)    
    hld.add(grdr, 'dv/dr;r;F=-dV/dr', 'L')
    hld.draw('A')
    ROOT.gPad.SetGridx()
    ROOT.gPad.SetGridy()    
    #ROOT.gPad.SetLogy()

    tc.Update()    
    tutils.gList.append(hl)
    tutils.gList.append(hlals)    
    tutils.gList.append(hld)    
    tutils.wait()
    
if __name__=="__main__":
    main()

#!/usr/bin/env ipython -i

import ROOT
ROOT.gROOT.SetStyle("Plain")
from array import array

import tutils
import dlist

class XiSum(object):
	def __init__(self, npart=False):
		self.xval = array("f", [5.0, 15.0, 30.0, 50.0, 70.0])
		self.xerrminus = array("f", [5.0, 5.0, 10.0, 10.0, 10.0])
		self.xerrplus = array("f", [5.0, 5.0, 10.0, 10.0, 10.0])

		if npart==True:
			self.xval = array("f", [356.1, 260.1, 157.2, 68.6, 22.5])
			self.xerrminus = array("f", [3.6000000000000227, 3.900000000000034, 3.0999999999999943, 2.0, 0.8000000000000007])
			self.xerrplus = array("f", [3.599999999999966, 3.8999999999999773, 3.1000000000000227, 2.0, 0.8000000000000007])

		self.yval = array("f", [6.67, 5.14, 3.03, 1.07, 0.24])
		self.yerrminus = array("f", [0.47675989764240867, 0.36496575181789315, 0.22203603311174516, 0.0806225774829855, 0.019924858845171277])
		self.yerrplus = array("f", [0.47675989764240867, 0.36496575181789315, 0.22203603311174516, 0.0806225774829855, 0.019924858845171277])
		self.numpoints = 5

	def graph(self):
		p8557_d11x1y3 = ROOT.TGraphAsymmErrors(self.numpoints, self.xval, self.yval, self.xerrminus, self.xerrplus, self.yerrminus, self.yerrplus)
		p8557_d11x1y3.SetName("/HepData/8557/d11x1y3")
		p8557_d11x1y3.SetTitle("/HepData/8557/d11x1y3")
		return p8557_d11x1y3

class Xipp(object):
	def __init__(self):
		self.nch              = [21.294   ,16.513  	 ,13.457  	,11.507  	,8.991  		,6.061  		,3.897  		,2.261		]
		self.e_stat_nch       = [0.028    ,0.010  	 ,0.010  	,0.010  		,0.003  		,0.000  		,0.000  		,0.000		]  
		self.e_syst_nch       = [0.639    ,0.495  	 ,0.404  	,0.345  		,0.270  		,0.182  		,0.117  		,0.068		] 
		self.meanpt           = [1.445    ,1.362  	 ,1.283  	,1.259  		,1.196  		,1.115  		,1.015  		,0.912		]  
		self.e_stat_mpt       = [0.023    ,0.012  	 ,0.010  	,0.010  		,0.006  		,0.005  		,0.005  		,0.005		]  
		self.e_systtot_mpt    = [0.029    ,0.027  	 ,0.026  	,0.025  		,0.024  		,0.022  		,0.020  		,0.018		]  
		self.e_systuncorr_mpt = [0.009    ,0.008  	 ,0.008  	,0.008  		,0.007  		,0.007  		,0.006  		,0.005		]  
		self.hpi              = [0.004976 ,0.004733  ,0.004705  	,0.004453  	,0.004152  	,0.003638  	,0.002945  	,0.001996	]  
		self.e_stat_hpi       = [0.000094 ,0.000058  ,0.000062  	,0.000065  	,0.000047  	,0.000048  	,0.000056  	,0.000053	]  
		self.e_systtot_hpi    = [0.000449 ,0.000435  ,0.000430  	,0.000404  	,0.000355  	,0.000308  	,0.000262  	,0.000184	]  
		self.e_systuncorr_hpi = [0.000240 ,0.000243  ,0.000236  	,0.000218  	,0.000159  	,0.000133  	,0.000135  	,0.000104	]
		self.numpoints 		  = 8

	def graph(self, which=0):
		if which == 0:
			gr = ROOT.TGraphErrors(self.numpoints, self.nch, self.meanpt, self.e_stat_nch, self.e_stat_mpt)
		if which > 0:
			gr = ROOT.TGraphErrors(self.numpoints, self.nch, self.hpi, self.e_stat_nch, self.e_stat_hpi)
		return gr

def main():
	xi = XiSum(True)
	gr = xi.graph()

	xi1 = XiSum(False)
	gr1 = xi1.graph()

	grl = dlist.dlist('XiSumAA')
	grl.add(gr, 'XiSumAA', 'p')

	grl1 = dlist.dlist('XiSumAA-Npart')
	grl1.add(gr1, 'XiSumAA - npart', 'p')

	tc = grl.make_canvas()
	tc.Divide(2,1)
	tc.cd(1)
	grl.draw()
	grl.self_legend()
	grl.update()
	tc.cd(2)
	grl1.draw()
	grl1.self_legend()
	grl1.update()

	tutils.gList.append(grl)

if __name__ == '__main__':
	main()


#from https://twiki.cern.ch/twiki/bin/view/ALICE/CentStudies
# this is for PbPb (2.76)

class Centrality(object):
	def __init__(self):
		self.table_o = [
					#Cent		bmin[fm]	bmax [fm]	Npart	RMS		Sys		Ncoll	RMS			Sys			TAA			RMS		Sys
					['0-5%'		,0.00		,3.50		,382.7	,17		,3		,1685	,1.4e+02	,1.9e+02	,26.32		,2.2	,0.85		,00.		,  5.],
					['5-10%'	,3.50		,4.94		,329.4	,18		,4.3	,1316	,1.1e+02	,1.4e+02	,20.56		,1.7	,0.67		, 5.		, 10.],
					['10-20%'	,4.94		,6.98		,260.1	,27		,3.8	,921.2	,1.4e+02	,96			,14.39		,2.2	,0.45		,10.		, 20.],
					['20-40%'	,6.98		,9.88		,157.2	,35		,3.1	,438.4	,1.5e+02	,42			,6.85		,2.3	,0.23		,20.		, 40.],
					['40-60%'	,9.81		,12.09		,68.56	,22		,2		,127.7	,59			,11			,1.996		,0.92	,0.097		,40.		, 60.],
					['60-80%'	,12.09		,13.97		,22.52	,12		,0.77	,26.71	,18			,2			,0.4174		,0.29	,0.026		,60.		, 80.],
					['80-100%'	,13.97		,20.00		,5.604	,4.2	,0.14	,4.441	,4.4		,0.21		,0.06939	,0.068	,0.0055		,80.		,100.] ]
		l0     = self.table_o[0]
		l1     = self.table_o[1]
		bmax   = l1[2]
		npart  = (l0[3] + l1[3]) / 2.
		nprms  = (l0[4] + l1[4]) / 2.
		npsys  = (l0[5] + l1[5]) / 2.
		
		ncoll  = (l0[6] + l1[6]) / 2.
		ncrms  = (l0[7] + l1[7]) / 2.
		ncsys  = (l0[8] + l1[8]) / 2.
		
		taa    = (l0[9]  + l1[9]) / 2.
		taarms = (l0[10] + l1[10]) / 2.
		taasys = (l0[11] + l1[11]) / 2.
		self.table = [
					#Cent		bmin[fm]	bmax [fm]	Npart	RMS		Sys		Ncoll	RMS			Sys			TAA			RMS		Sys
					['0-10%'	,0.00		,bmax		,npart	,nprms	,npsys	,ncoll	,ncrms		,ncsys		,taa		,taarms	,taasys		,00.		, 10.],
					['10-20%'	,4.94		,6.98		,260.1	,27		,3.8	,921.2	,1.4e+02	,96			,14.39		,2.2	,0.45		,10.		, 20.],
					['20-40%'	,6.98		,9.88		,157.2	,35		,3.1	,438.4	,1.5e+02	,42			,6.85		,2.3	,0.23		,20.		, 40.],
					['40-60%'	,9.81		,12.09		,68.56	,22		,2		,127.7	,59			,11			,1.996		,0.92	,0.097		,40.		, 60.],
					['60-80%'	,12.09		,13.97		,22.52	,12		,0.77	,26.71	,18			,2			,0.4174		,0.29	,0.026		,60.		, 80.],
					['80-100%'	,13.97		,20.00		,5.604	,4.2	,0.14	,4.441	,4.4		,0.21		,0.06939	,0.068	,0.0055		,80.		,100.] ]

		self.sigmaPbPb = 7.7 # barns

	def nbins(self):
		return len(self.table)

	def TAA(self, ibin):
		return self.table[ibin][9]

	def Ncoll(self, ibin):
		return self.table[ibin][6]

	def Npart(self, ibin):
		return self.table[ibin][3]

	def Label(self, ibin):
		return self.table[ibin][0]

	def TAAs(self):
		ret = []
		for i in range(self.nbins()):
			ret.append(self.TAA(i))
		return ret

	def Labels(self):
		ret = []
		for i in range(self.nbins()):
			ret.append(self.Label(i))
		return ret

	def BinWidth(self, ibin):
		if ibin < 2:
			return 0.10 #0.05
		if ibin == 2:
			return 0.20;
		if ibin > 2:
			return 0.20
		return 0

	def BinLow(self, ibin):
		return self.table[ibin][-2]

	def BinLowsE(self):
		retval = []
		for ibin in range(self.nbins()):
			retval.append(self.BinCenter(ibin) - self.BinLow(ibin))
		return retval

	def BinHighsE(self):
		retval = []
		for ibin in range(self.nbins()):
			retval.append(self.BinHigh(ibin) - self.BinCenter(ibin))
		return retval

	def BinHigh(self, ibin):
		return self.table[ibin][-1]

	def BinRange(self, ibin):
		return [self.BinLow(ibin), self.BinHigh(ibin)]

	def BinCenter(self, i):
		return self.BinLow(i) + (self.BinHigh(i) - self.BinLow(i))/2.

	def BinCenters(self):
		retval = []
		for i in range(self.nbins()):
			retval.append(self.BinLow(i) + (self.BinHigh(i) - self.BinLow(i))/2.)
		return retval

	def BinPbPbNEvents(self, ibin, intLumi = 220. * 1.e6):
		return intLumi * self.sigmaPbPb * self.BinWidth(ibin)


#from https://twiki.cern.ch/twiki/bin/view/ALICE/CentStudies
# this is for PbPb (2.76)

class Centrality(object):
	def __init__(self):
		self.table = [
					#Cent		bmin[fm]	bmax [fm]	Npart	RMS		Sys		Ncoll	RMS			Sys			TAA			RMS		Sys
					['0-5%'		,0.00		,3.50		,382.7	,17		,3		,1685	,1.4e+02	,1.9e+02	,26.32		,2.2	,0.85	],
					['5-10%'	,3.50		,4.94		,329.4	,18		,4.3	,1316	,1.1e+02	,1.4e+02	,20.56		,1.7	,0.67	],
					['10-20%'	,4.94		,6.98		,260.1	,27		,3.8	,921.2	,1.4e+02	,96			,14.39		,2.2	,0.45	],
					['20-40%'	,6.98		,9.88		,157.2	,35		,3.1	,438.4	,1.5e+02	,42			,6.85		,2.3	,0.23	],
					['40-60%'	,9.81		,12.09		,68.56	,22		,2		,127.7	,59			,11			,1.996		,0.92	,0.097	],
					['60-80%'	,12.09		,13.97		,22.52	,12		,0.77	,26.71	,18			,2			,0.4174		,0.29	,0.026	],
					['80-100%'	,13.97		,20.00		,5.604	,4.2	,0.14	,4.441	,4.4		,0.21		,0.06939	,0.068	,0.0055	] ]

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
			return 0.05
		if ibin == 2:
			return 0.10;
		if ibin > 2:
			return 0.20
		return 0
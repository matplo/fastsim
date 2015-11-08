#ifndef R2UTIL_HH
#define R2UTIL_HH

#include <TLorentzVector.h>
#include <TString.h>
#include <vector>

namespace R2Util
{
// the range in phi is from 0-2pi
// these methods are good for jets but for particles lack granularity
bool 		IsEMCAL02pi(double eta, double phi);
bool 		IsDCALPHOS02pi(double eta, double phi);
bool 		IsEMCAL(double eta, double phi);
bool 		IsDCALPHOS(double eta, double phi);

TString 	sEMCalPhiCut02Pi();
TString 	sDCALPHOSPhiCut02Pi();
TString 	sEMCalPhiCut();
TString 	sDCALPHOSPhiCut();

const char* EMCalPhiCut02Pi();
const char* DCALPHOSPhiCut02Pi();
const char* EMCalPhiCut();
const char* DCALPHOSPhiCut();
};

#endif // R2UTIL_HH
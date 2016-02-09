#include "r2util.h"
#include <boost/math/constants/constants.hpp>

namespace R2Util
{
	const double pi = boost::math::constants::pi<double>();

	; //std::vector<TLorentzVector> util_vector;
	bool IsEMCAL02pi(double eta, double phi)
	{
		if ( (eta > -0.668305) && (eta < 0.668305) && (phi > 1.40413) && (phi < 3.26149) ) 
			return true;
		return false;
	};
	bool IsDCALPHOS02pi(double eta, double phi)
	{
		if ( (eta > -0.668305) && (eta < 0.668305) && (phi > 4.54573) && (phi < 5.70495) ) 
			return true;
		return false;
	};

	bool IsEMCAL02piR(double eta, double phi, double r)
	{
		if ( (eta > -0.668305 + r) && (eta < 0.668305 - r) && (phi + r > 1.40413) && (phi < 3.26149 - r) ) 
			return true;
		return false;
	};
	bool IsDCALPHOS02piR(double eta, double phi, double r)
	{
		if ( (eta > -0.668305 + r) && (eta < 0.668305 - r) && (phi + r > 4.54573) && (phi < 5.70495 - r) ) 
			return true;
		return false;
	};

	bool IsEMCAL(double eta, double phi)
	{	
		// this is for -pi - pi
		if ( (eta > -0.668305) && (eta < 0.668305) && (phi > 1.40413 - pi ) && (phi < 3.26149 - pi ) ) 
			return true;
		return false;
	};
	bool IsDCALPHOS(double eta, double phi)
	{
		if ( (eta > -0.668305) && (eta < 0.668305) && (phi > 4.54573 - pi ) && (phi < 5.70495 - pi ) ) 
			return true;
		return false;
	};

	TString sEMCalPhiCut02Pi() 
	{
		return TString("((phi > 1.40413) && (phi < 3.26149))");
	}
	TString sDCALPHOSPhiCut02Pi() 
	{
		return TString("((phi > 4.54573) && (phi < 5.70495))");
	}
	TString sEMCalPhiCut() 
	{
		TString s = TString::Format("((phi > 1.40413) && (phi < %1.5f))", 3.26149-pi);
		return s;
	}
	TString sDCALPHOSPhiCut() 
	{
		TString s = TString::Format("((phi > 4.54573) && (phi < %1.5f))", 5.70495-pi);
		return s;
	}

	const char* EMCalPhiCut02Pi() 
	{
		return sEMCalPhiCut02Pi().Data();
	}
	const char* DCALPHOSPhiCut02Pi() 
	{
		return sDCALPHOSPhiCut02Pi().Data();
	}
	const char* EMCalPhiCut() 
	{
		return sEMCalPhiCut().Data();
	}
	const char* DCALPHOSPhiCut() 
	{
		return sDCALPHOSPhiCut().Data();
	}

}
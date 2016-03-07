#ifndef __PARTONGUN__HH
#define __PARTONGUN__HH

class TH1;
namespace Pythia8
{
	class Pythia;
};

namespace PyUtil
{
	class PartonGun 
	{
	public:
		PartonGun(int id = 21);
		virtual ~PartonGun();

		virtual int NextEvent(Double_t pt = -1);
		virtual void InitPythia();

		Pythia8::Pythia * GetPythia() {return fPythia;}

		void SetSpectrum(int id, TH1 *h);
		void SetSpectrum(int id, Double_t pt, Double_t ptmax = -1);

		void SetPartonID(int id)
		{
			fPartonID = id;
		}

		void SetDebug(bool dbg)
		{
			fDebug = dbg;
		}

	protected:
		bool             fDebug;
		Pythia8::Pythia *fPythia; //!
		TH1             *fSpectrum; //!
		Double_t         fWeight;
		int              fPartonID;

	private:

		PartonGun();
		// by default qKine == px (full pT in x-direction); otherwise == ex 
		void InsertPartons(double pt, bool ispt = true);
	};
}
#endif //__PARTONGUN__HH
#ifndef __RndSource__HH
#define __RndSource__HH


#include <TFolder.h>
class TH1;
class TF1;
class TRandom;

class RndSource : public TFolder
{
 public:
  RndSource(const char *name, const char *title = "RNDdefault", UInt_t seed = 65539);
  virtual ~RndSource();

  void SetSource(TH1 *);
  void SetSource(TF1 *);

  void DrawOnCanvases(Bool_t newC = kTRUE);

  Double_t RndmFromSource();

  static TH1 *Smear(TH1* hsrc, TH1 *hsmear, Double_t statmult = 1.,
		    Double_t ptCutOffMin = 0., Double_t ptCutOffMax = 1e4);
  static TH1 *Smear(TH1* hsrc, TF1 *fun, Double_t statmult = 1.,
		    Double_t ptCutOffMin = 0., Double_t ptCutOffMax = 1e4);
  static TH1 *Smear(TH1* hsrc, RndSource *rnd, Double_t statmult,
		    Double_t ptCutOffMin = 0., Double_t ptCutOffMax = 1e4);
  static TH1 *Smear(TF1* fsrc, TH1 *hsmear, Double_t statmult = 1.,
		    Double_t ptCutOffMin = 0., Double_t ptCutOffMax = 1e4);
  static TH1 *Smear(TF1* fsrc, TF1 *fun, Double_t statmult = 1.,
		    Double_t ptCutOffMin = 0., Double_t ptCutOffMax = 1e4);
  TH1* GetSrc() {return fHSrc;}

 private:  

  void DeleteHistograms();

  TH1 *fHSrc;//! copy of the source histogram
  TH1 *fHRnmd; //! pull the bin content from here to get th rnmd number
  TH1 *fHNormalized; //! normalized PDF from source
  TH1 *fHIntegrals; //! integrals for bin width

  TRandom *fRndGen;//!

  ClassDef(RndSource,0)
};

#endif

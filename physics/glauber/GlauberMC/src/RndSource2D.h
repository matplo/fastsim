#ifndef __RndSource2D__HH
#define __RndSource2D__HH


#include <TFolder.h>

class TH2;
class TF2;
class TList;
class RndSource;

class RndSource2D : public TFolder
{
 public:

  RndSource2D(const char *name, const char *title);
  virtual ~RndSource2D();

  virtual void SetSource(TH2 *);
  virtual void SetSource(TF2 *);

  virtual void DrawOnCanvases(Int_t ibinX, Bool_t newC = kTRUE);
  virtual void DrawOnCanvases(Double_t valx, Bool_t newC = kTRUE);

  virtual Double_t RndmFromSource(Double_t atvalX);

  RndSource *GetRndSource(Int_t i);

  TH2 *GetSrcHistogram() {return hSrc2D;}
 
 private:  

  TH2 *hSrc2D;
  TList *rnds;

  ClassDef(RndSource2D,0)
};

#endif

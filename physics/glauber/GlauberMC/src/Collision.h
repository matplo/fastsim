#ifndef COLLISION_HH
#define COLLISION_HH

#include <TObject.h>

class Collision : public TObject
{
public:
  Collision() 
    : TObject()
    , nA(-1)
    , nB(-1)
    , rA(0)
    , rB(0)
    , eA(-1)
    , eB(-1)
    {
      ;
    }
    
  Collision(Int_t ia, Int_t ib, Double_t ra, Double_t rb, Double_t ea, Double_t eb)
    : TObject()
    {
      nA = ia;
      nB = ib;
      rA = ra;
      rB = rb;
      eA = ea;
      eB = eb;
    }

  Int_t GetNA() {return nA;}
  Int_t GetNB() {return nB;}

  Double_t GetEA() {return eA;}
  Double_t GetEB() {return eB;}

  Double_t GetRA() {return rA;}
  Double_t GetRB() {return rB;}

  virtual ~Collision()
  { 
    ;
  }
private:
  Int_t     nA;
  Int_t     nB;
  Double_t  rA;
  Double_t  rB;
  Double_t  eA;
  Double_t  eB;
  ClassDef(Collision, 1)
};

#endif // COLLISION_HH
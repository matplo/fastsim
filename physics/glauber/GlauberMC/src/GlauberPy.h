#ifndef GLAUBERPY_H
#define GLAUBERPY_H

#include "AliGlauberMC.h"
#include <Riostream.h>
#include <TNamed.h>

class GlauberPy : public AliGlauberMC
{
public:
                                    GlauberPy(Option_t* NA = "Pb", Option_t* NB = "Pb", Double_t xsect = 64);
   virtual                          ~GlauberPy();
                                    GlauberPy(const GlauberPy& in);
   GlauberPy& operator              =(const GlauberPy& in);
   void                             Run(Int_t nevents);
   Bool_t                           CalcEvent(Double_t bgen);
   void                             Reset();

   static void                      PrintVersion()             {std::cout << "GlauberPy " << Version() << std::endl;}
   static const char *              Version()                  {return "v1.0";}

   ClassDef(GlauberPy, 1)
};

#endif

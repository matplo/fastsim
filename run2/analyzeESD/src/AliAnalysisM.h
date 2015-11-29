#ifndef ALIANALYSISM_H
#define ALIANALYSISM_H

#include "AliAnalysisTaskSE.h"

class AliEMCALGeometry;

class AliAnalysisM : public AliAnalysisTaskSE
{
 public:
    AliAnalysisM();
    AliAnalysisM(const char* name);
    virtual ~AliAnalysisM() {;}

    // To be implemented by user
    virtual void   UserCreateOutputObjects();
    virtual void   UserExec(Option_t* /*option*/);

private:

    AliAnalysisM(const AliAnalysisM& obj) {;}
    AliAnalysisM& operator=(const AliAnalysisM& other) {;}

    void *fREvent; //!

    AliEMCALGeometry *fGeom; //!

    ClassDef(AliAnalysisM, 1); // Analysis task for standard jet analysis
};
 
#endif

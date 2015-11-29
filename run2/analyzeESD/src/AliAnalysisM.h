#ifndef ALIANALYSISM_H
#define ALIANALYSISM_H

#include "AliAnalysisTaskSE.h"

class AliEMCALGeometry;
class THistManager;

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

    void *fREvent;  //!
    void *fTM_EMC;      //!
    void *fTM_DMC;      //!
    AliEMCALGeometry *fGeom; //!

    THistManager *fHManager;

    ClassDef(AliAnalysisM, 1); // Analysis task for standard jet analysis
};
 
#endif

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

    void CreateBranches();

    void *fREvent;  //!
    void *fTM;      //!
    AliEMCALGeometry *fGeom; //!

    THistManager *fHManager;

    static Int_t fgBadChannels[]; //!

    inline Bool_t IsBadChannel(Short_t absId)
    {
        int i = 0;
        while (fgBadChannels[i]!=-1)
        {
            if (absId == fgBadChannels[i])
                return kTRUE;
            i++;
        }
        return kFALSE;
    }

    ClassDef(AliAnalysisM, 1); // Analysis task for standard jet analysis
};

#endif

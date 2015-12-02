#ifndef ALIANALYSISM_H
#define ALIANALYSISM_H

#include "AliAnalysisTaskSE.h"

class AliEMCALGeometry;
class THistManager;

class AliAnalysisM : public AliAnalysisTaskSE
{
    enum {
        kOther = 0x1,
        kCINT7 = 0x1 << 1,
        kEJ1   = 0x1 << 2,
        kEG1   = 0x1 << 3,
        kDJ1   = 0x1 << 4,
        kDG1   = 0x1 << 5
    };

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

    void Jets(void *cells, double R=0.2);

    void *fREvent;  //!
    void *fTM;      //!
    void *fTM0;      //!
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

    inline Int_t GetNumberOfBadChannels()
    {
        int i = 0;
        while (fgBadChannels[i++]!=-1);
        return i;
    }

    ClassDef(AliAnalysisM, 1); // Analysis task for standard jet analysis
};

#endif

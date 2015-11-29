#include "AliAnalysisM.h"

#include <TTree.h>

#include "REvent.h"

ClassImp(AliAnalysisM)

AliAnalysisM::AliAnalysisM()
	: AliAnalysisTaskSE()
	, fREvent(new REvent)
{
	;
}

AliAnalysisM::AliAnalysisM(const char* name)
	: AliAnalysisTaskSE(name)
	, fREvent(new REvent)
{
	DefineOutput(1, TTree::Class());
}

void AliAnalysisM::UserCreateOutputObjects()
{
	OpenFile(1);
	//create the output
	REvent *revent = (REvent*)fREvent;
	revent->Init();
	TTree *t = (TTree*)revent->GetTree(); 
	PostData(1, t);
}

void AliAnalysisM::UserExec(Option_t* /*option*/)
{
	REvent *revent = (REvent*)fREvent;
	TTree *t = (TTree*)revent->GetTree();
	PostData(1, t);
}


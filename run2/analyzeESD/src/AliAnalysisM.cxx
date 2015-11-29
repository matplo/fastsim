#include "AliAnalysisM.h"

#include <TTree.h>
#include <AliEMCALGeometry.h>

#include "REvent.h"

ClassImp(AliAnalysisM)

AliAnalysisM::AliAnalysisM()
	: AliAnalysisTaskSE()
	, fREvent(new REvent)
	, fGeom(0)
{
	;
}

AliAnalysisM::AliAnalysisM(const char* name)
	: AliAnalysisTaskSE(name)
	, fREvent(new REvent)
	, fGeom(0)
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

	TString ts = InputEvent()->GetFiredTriggerClasses();

	TString tsIs = "";

	if (ts.Contains("CINT7-"))
	{
		tsIs = "CINT7";
	}

	if (ts.Contains("CINT7EJ1"))
	{
		tsIs = "EJ1";
	}

	if (ts.Contains("CINT7EG1"))
	{
		tsIs = "EG1";
	}

	if (ts.Contains("CINT7DJ1"))
	{
		tsIs = "DJ1";
	}

	if (ts.Contains("CINT7DG1"))
	{
		tsIs = "DG1";
	}

	if (fGeom == 0)
	{
		Int_t runNo = InputEvent()->GetRunNumber();
		fGeom = AliEMCALGeometry::GetInstanceFromRunNumber(runNo);
	}

	// loop over cells...
	AliVCaloCells *cells = InputEvent()->GetEMCALCells();
	for (Int_t iCell = 0; iCell < cells->GetNumberOfCells(); ++iCell) 
	{
		// get the cell info, based in index in array
		Short_t 	absId = cells->GetCellNumber(iCell);
		Double_t 	amp   = cells->GetAmplitude(iCell);
		Double_t 	phi   = -1000;
		Double_t 	eta   = 1000;
		fGeom->EtaPhiFromIndex(absId, eta, phi);
	}

	revent->FinishEvent();
	PostData(1, t);
}


void runLocal(const char *fileList = "files_000244982.txt")
{
	AliAnalysisManager *mgr = new AliAnalysisManager("EMC");

	// Adding handler
	gROOT->Macro( Form("%s/ANALYSIS/macros/train/AddESDHandler.C", gSystem->Getenv("ALICE_ROOT")) );

	gSystem->Load( Form("%s/lib/libEMCALTriggerFast", gSystem->Getenv("RUN2AESDDIR")) );
	gSystem->Load( Form("%s/lib/libAnalyzeESD", gSystem->Getenv("RUN2AESDDIR")) );

	AliAnalysisM *task = new AliAnalysisM("my task");

	gROOT->LoadMacro( Form("%s/PWG/EMCAL/macros/AddTaskEmcalSetup.C", gSystem->Getenv("ALICE_PHYSICS")) );
	AliEmcalSetupTask *t = AddTaskEmcalSetup(0,0, "local:///cvmfs/alice-ocdb.cern.ch/calibration/data/2015/OCDB");

	mgr->AddTask(task);
	mgr->ConnectInput(task, 0, mgr->GetCommonInputContainer());

	AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("containerName",
	                                     TTree::Class(), AliAnalysisManager::kOutputContainer,
	                                     Form("Tree_%s", AliAnalysisManager::GetCommonFileName()));
	mgr->ConnectOutput (task, 1, coutput1 );

	AliAnalysisDataContainer *coutput2 = mgr->CreateContainer("histos",
	                                     TList::Class(), AliAnalysisManager::kOutputContainer,
	                                     Form("Hist_%s", AliAnalysisManager::GetCommonFileName()));
	mgr->ConnectOutput (task, 2, coutput2 );

	if (!mgr->InitAnalysis()) return;
	mgr->PrintStatus();

	TChain* pChain = 0;
	gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/CreateESDChain.C");
	pChain = CreateESDChain(fileList, 1234567890, 0, kFALSE);
	//pChain = CreateESDChain(fileList, 100, 0, kFALSE);

	// start analysis
	Printf("Starting Analysis...");
	mgr->SetUseProgressBar(1, 250);
	//mgr->SetDebugLevel(2);

	mgr->StartAnalysis("local", pChain);
}
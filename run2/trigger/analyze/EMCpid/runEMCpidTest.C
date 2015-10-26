{
	//gROOT->ProcessLine(".L EMCpid.C++");
	gSystem->Load("libEMCpidPar");
	EMCpid a;
	a.Loop();
}
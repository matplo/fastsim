{
	gROOT->ProcessLine(".L EMCpid.C++");
	EMCpid a;
	a.Loop();
}
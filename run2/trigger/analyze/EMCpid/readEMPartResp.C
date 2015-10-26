{
	gSystem->Load("$RUN2EMCTRIGGER/lib/libEMCpidPar.dylib");
	EMPartResp r("EMPartResp.root");
	r.GetEop(11, 1000);
	r.GetEop(211, 0.2);
}
{
	gSystem->Load("libR2Util");
	gSystem->Load("libAnalyze");
	Analysis a;
	TString fname = "/Users/ploskon/Desktop/tree-default_emctrig_out_R_0.4_femcpar.root";
	fname = "/Volumes/SAMSUNG/data/run2/trigger/2015-10-29/hardQCD/default_emctrig_out_R_0.4_femcpar.root";
	a.AnalyzeFile(fname.Data(), "out.root");
}

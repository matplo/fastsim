{
	gSystem->Load("libR2Util");
	gSystem->Load("libAnalyze");
	Analysis_pp a;
	TString fname = "/Users/ploskon/Desktop/tree-default_emctrig_out_R_0.4_femcpar.root";
	fname = "/Volumes/SAMSUNG/data/run2/trigger/2015-10-29/hardQCD/tree-default_emctrig_out_R_0.4_femcpar.root";
	fname = "/Users/ploskon/devel/sandbox/run2/trigger/test/test_emc/tree-vacuum_R_0.4_femcpar.root";
	fname = "/Users/ploskon/devel/sandbox/run2/trigger/test/test_emc/tree-vacuum_R_0.4_femc_1.0.root";

	a.AnalyzeFile(fname.Data(), "out.root");
}

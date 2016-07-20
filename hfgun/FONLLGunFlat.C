void FONLLGunFlat(Int_t nevents = 10)
{
	//Note: QUARKS d 1 u 2 s 3 c 4 b 5 t 6 b' 7 t' 8
	//      GLUE is 21 and is is default
	TFile *fin = TFile::Open("./fonll/c-pp-2.75.txt.root");
	TGraphErrors *gr = (TGraphErrors*)fin->Get("graph___c_pp_2_75_txt");

	TFile *fin = TFile::Open("/Users/ploskon/devel/cernsandbox/e-loss/fonll/graph___c_pp_2_75_txt_deltas.root");
	TGraphErrors *gr = (TGraphErrors*)fin->Get("graph___c_pp_2_75_txt_delta__10_graph___c_pp_2_75_txt_deltas");
	TGraphErrors *gr = (TGraphErrors*)fin->Get("graph___c_pp_2_75_txt_delta_0_graph___c_pp_2_75_txt_deltas");

	HFGun p;
	p.SetOutputFileName("fonll-charm-2760.root");
	int partonID = 4; // charm is 4
	p.SetSpectrum(gr, partonID); // set the input spectrum and the fPartonID
	//p.SetPartonID(2) - alternative...
	p.Generate(nevents);
}

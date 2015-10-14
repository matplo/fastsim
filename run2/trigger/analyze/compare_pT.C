void compare_pT()
{
	TString fname1 = "./default_emctrig_out_nohard.root";
	TString fname2 = "./default_emctrig_out.root";
	TFile *fin1 = TFile::Open(fname1);
	TNtuple *jEMC1 = (TNtuple*)fin1->Get("jets_hard_EMC");
	jEMC1->Draw("pT", "(nEv==-1) * (xsec)", "");
	TFile *fin2 = TFile::Open(fname2);
	TNtuple *jEMC2 = (TNtuple*)fin2->Get("jets_hard_EMC");
	jEMC2->Draw("pT", "(nEv==-1) * (xsec)", "same");
}

